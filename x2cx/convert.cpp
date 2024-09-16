#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <fstream>
#include <vector>

#include <zephyr/assert.h>
#include <zephyr/com_ptr.h>
#include <zephyr/print.h>
#include <zephyr/runtime_assert.h>

#include "convert.h"

using zephyr::assert;
using zephyr::com_ptr;
using zephyr::println;
using zephyr::runtime_assert;

struct float2
{
    float x, y;
};

struct float3
{
    float x, y, z;
};

struct float4
{
    float x, y, z, w;
};

static std::vector<float3> getPositionBuffer(ID3DXMesh* mesh)
{
    if ((mesh->GetFVF() & D3DFVF_XYZ) == 0)
    {
        return std::vector<float3>();
    }

    com_ptr<IDirect3DVertexBuffer9> buffer;
    mesh->GetVertexBuffer(&buffer);

    auto count = mesh->GetNumVertices();
    auto size = mesh->GetNumBytesPerVertex();
    byte* ptr = nullptr;

    auto vertices = std::vector<float3>(count);
    {
        buffer->Lock(0, 0, (void**)&ptr, D3DLOCK_READONLY);
        for (unsigned long i = 0; i < count; i++)
        {
            vertices[i] = *reinterpret_cast<float3*>(ptr);
            ptr += size;
        }
        buffer->Unlock();
    }

    return vertices;
}

static std::vector<float3> getNormalBuffer(ID3DXMesh* mesh)
{
    if ((mesh->GetFVF() & D3DFVF_NORMAL) == 0)
    {
        return std::vector<float3>();
    }

    int offset = 0;
    if ((mesh->GetFVF() & D3DFVF_XYZ))
    {
        offset += sizeof(float) * 3;
    }

    com_ptr<IDirect3DVertexBuffer9> buffer;
    mesh->GetVertexBuffer(&buffer);

    auto count = mesh->GetNumVertices();
    auto size = mesh->GetNumBytesPerVertex();

    auto vertices = std::vector<float3>(count);
    {
        byte* ptr = nullptr;
        buffer->Lock(0, 0, (void**)&ptr, D3DLOCK_READONLY);
        for (unsigned long i = 0; i < count; i++)
        {
            vertices[i] = *reinterpret_cast<float3*>(ptr + offset);
            ptr += size;
        }
        buffer->Unlock();
    }

    return vertices;
}

static std::vector<float2> getTexCoordBuffer(ID3DXMesh* mesh)
{
    if ((mesh->GetFVF() & D3DFVF_TEX1) == 0)
    {
        return std::vector<float2>();
    }

    int offset = 0;
    if (mesh->GetFVF() & D3DFVF_XYZ)
    {
        offset += sizeof(float) * 3;
    }
    if (mesh->GetFVF() & D3DFVF_NORMAL)
    {
        offset += sizeof(float) * 3;
    }
    if (mesh->GetFVF() & D3DFVF_DIFFUSE)
    {
        offset += sizeof(DWORD);
    }
    if (mesh->GetFVF() & D3DFVF_SPECULAR)
    {
        offset += sizeof(DWORD);
    }

    com_ptr<IDirect3DVertexBuffer9> buffer;
    mesh->GetVertexBuffer(&buffer);

    auto count = mesh->GetNumVertices();
    auto size = mesh->GetNumBytesPerVertex();
    byte* ptr = nullptr;

    auto vertices = std::vector<float2>(count);
    {
        buffer->Lock(0, 0, (void**)&ptr, D3DLOCK_READONLY);
        for (unsigned long i = 0; i < count; i++)
        {
            vertices[i] = *reinterpret_cast<float2*>(ptr + offset);
            vertices[i].x = fmod(vertices[i].x, 1.0f);
            vertices[i].y = fmod(vertices[i].y, 1.0f);
            ptr += size;
        }
        buffer->Unlock();
    }

    return vertices;
}

static std::vector<float4> getColorBuffer(ID3DXMesh* mesh)
{
    return std::vector<float4>();
}

static void getTangentBinormalBuffer(ID3DXMesh* mesh, std::vector<float3>& tangents, std::vector<float3>& binormals)
{
    ID3DXMesh* pNewMesh;
    D3DVERTEXELEMENT9 elems[] =
    {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
        { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
        { 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
        { 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
        D3DDECL_END()
    };
    com_ptr<IDirect3DDevice9> device9;
    mesh->GetDevice(&device9);
    HRESULT hr = mesh->CloneMesh(mesh->GetOptions(), elems, device9.ptr, &pNewMesh);
    runtime_assert(SUCCEEDED(hr));
    hr = D3DXComputeTangent(pNewMesh, 0, 0, 0, true, nullptr);
    runtime_assert(SUCCEEDED(hr));

    com_ptr<IDirect3DVertexBuffer9> buffer;
    pNewMesh->GetVertexBuffer(&buffer);

    auto count = pNewMesh->GetNumVertices();
    auto size = pNewMesh->GetNumBytesPerVertex();

    tangents = std::vector<float3>(count);
    binormals = std::vector<float3>(count);
    {
        byte* ptr = nullptr;
        buffer->Lock(0, 0, (void**)&ptr, D3DLOCK_READONLY);
        for (unsigned long i = 0; i < count; i++)
        {
            tangents[i] = *reinterpret_cast<float3*>(ptr + 32);
            binormals[i] = *reinterpret_cast<float3*>(ptr + 44);
            ptr += size;
        }
        buffer->Unlock();
    }
}

static std::vector<int> getIndexBuffer(ID3DXMesh* mesh)
{
    IDirect3DIndexBuffer9* buffer = nullptr;
    mesh->GetIndexBuffer(&buffer);

    if (buffer != nullptr)
    {
        D3DINDEXBUFFER_DESC desc;
        buffer->GetDesc(&desc);
        auto size = desc.Size;
        auto isLongIndex = (desc.Format == D3DFMT_INDEX32);
        auto count = static_cast<int>(isLongIndex ? (size / sizeof(UINT32)) : (size / sizeof(UINT16)));

        auto data = std::vector<int>(count);
        if (isLongIndex)
        {
            uint32_t* ptr = nullptr;
            buffer->Lock(0, 0, (void**)&ptr, 0);
            {
                for (int i = 0; i < count; i++)
                    data[i] = (int)*ptr++;
            }
            buffer->Unlock();
        }
        else
        {
            uint16_t* ptr = nullptr;
            buffer->Lock(0, 0, (void**)&ptr, 0);
            {
                for (int i = 0; i < count; i++)
                    data[i] = (int)*ptr++;
            }
            buffer->Unlock();
        }

        return data;
    }
    else
    {
        return std::vector<int>();
    }
}

struct Mesh
{
    std::vector<float3> positions;
    std::vector<float3> normals;
    std::vector<float2> texcoords;
    std::vector<float4> colors;
    std::vector<float3> tangents;
    std::vector<float3> binormals;
    std::vector<int> indices;

    float4 ambient = { 0, 0, 0, 0 };
    float4 diffuse = { 0, 0, 0, 0 };
    float4 specular = { 0, 0, 0, 0 };
    float power = 0;

    std::string texturePath;
};

static void compress(Mesh& mesh)
{
    // ...
}

static void write(std::ofstream& stream, std::string semantics, const std::vector<float2>& buffer)
{
    if (0 < buffer.size())
    {
        println(stream, "[{0}]", semantics);
        println(stream, "{0}", buffer.size());
        for (auto v : buffer)
        {
            println(stream, "{0}, {1}", v.x, v.y);
        }
    }
}

static void write(std::ofstream& stream, std::string semantics, const std::vector<float3>& buffer)
{
    if (0 < buffer.size())
    {
        println(stream, "[{0}]", semantics);
        println(stream, "{0}", buffer.size());
        for (auto v : buffer)
        {
            println(stream, "{0}, {1}, {2}", v.x, v.y, v.z);
        }
    }
}

static void write(std::ofstream& stream, std::string semantics, const std::vector<float4>& buffer)
{
    if (0 < buffer.size())
    {
        println(stream, "[{0}]", semantics);
        println(stream, "{0}", buffer.size());
        for (auto v : buffer)
        {
            println(stream, "{0}, {1}, {2}, {3}", v.x, v.y, v.z, v.w);
        }
    }
}

static void write(std::ofstream& stream, std::string semantics, const std::vector<int>& buffer)
{
    if (0 < buffer.size())
    {
        println(stream, "[{0}]", semantics);
        println(stream, "{0}", buffer.size());
        for (auto i : buffer)
        {
            println(stream, "{0}", i);
        }
    }
}

static void write(std::ofstream& stream, std::string semantics, float4 ambient, float4 diffuse, float4 specular, float power)
{
    println(stream, "[{0}]", semantics);
    println(stream, "{0}, {1}, {2}, {3}", ambient.x, ambient.y, ambient.z, ambient.w);
    println(stream, "{0}, {1}, {2}, {3}", diffuse.x, diffuse.y, diffuse.z, diffuse.w);
    println(stream, "{0}, {1}, {2}, {3}", specular.x, specular.y, specular.z, specular.w);
    println(stream, "{0}", power);
}

static void write(std::ofstream& stream, std::string semantics, std::string path)
{
    if (0 < path.size())
    {
        println(stream, "[{0}]", semantics);
        println(stream, "{0}", path);
    }
}

static void write(std::ofstream& stream, const Mesh& mesh)
{
    write(stream, "POSITION", mesh.positions);
    write(stream, "NORMAL", mesh.normals);
    write(stream, "COLOR", mesh.colors);
    write(stream, "TEXCOORD", mesh.texcoords);
    write(stream, "TANGENT", mesh.tangents);
    write(stream, "BINORMAL", mesh.binormals);
    write(stream, "INDEX", mesh.indices);
    write(stream, "MATERIAL", mesh.ambient, mesh.diffuse, mesh.specular, mesh.power);
    write(stream, "TEXTURE", mesh.texturePath);
}

static LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
};

static com_ptr<IDirect3DDevice9> device;

void create_d3d9_device()
{
    const auto className = "x2cx";

    HINSTANCE hInstance = GetModuleHandle(0);
    WNDCLASSEX wcex = {
        sizeof(WNDCLASSEX), NULL, WndProc, 0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW), NULL, NULL, className, NULL
    };
    if (RegisterClassEx(&wcex) == 0)
        exit(EXIT_FAILURE);
    HWND hWindow = CreateWindow(className, "", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    D3DPRESENT_PARAMETERS params;
    ZeroMemory(&params, sizeof(params));
    params.BackBufferCount = 0;
    params.BackBufferFormat = D3DFMT_UNKNOWN;
    params.Windowed = true;
    params.SwapEffect = D3DSWAPEFFECT_DISCARD;
    params.EnableAutoDepthStencil = false;
    params.hDeviceWindow = nullptr;
    params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

    com_ptr<IDirect3D9> direct3D(Direct3DCreate9(D3D_SDK_VERSION));
    {
        HRESULT result = E_FAIL;
        if (FAILED(result))
            result = direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &device);
        if (FAILED(result))
            result = direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &params, &device);
        if (FAILED(result))
            result = direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &params, &device);
        assert(SUCCEEDED(result) && device.available(), "Failed to create Direct3D9 device.");
    }
}

void finalize()
{
    device.reset();
}

void convert(std::string src_path, std::string dest_path)
{
    com_ptr<ID3DXMesh> mesh9;
    com_ptr<ID3DXBuffer> materials;
    D3DXLoadMeshFromX(src_path.c_str(), D3DXMESH_SYSTEMMEM, device.ptr, nullptr, &materials, nullptr, nullptr, &mesh9);

    Mesh mesh;
    mesh.positions = getPositionBuffer(mesh9.ptr);
    mesh.normals = getNormalBuffer(mesh9.ptr);
    mesh.colors = getColorBuffer(mesh9.ptr);
    mesh.texcoords = getTexCoordBuffer(mesh9.ptr);
    if (0 < mesh.texcoords.size())
    {
        getTangentBinormalBuffer(mesh9.ptr, mesh.tangents, mesh.binormals);
    }
    mesh.indices = getIndexBuffer(mesh9.ptr);

    auto material = ((D3DXMATERIAL*)materials->GetBufferPointer())[0].MatD3D;
    mesh.ambient = reinterpret_cast<const float4&>(material.Ambient);
    mesh.diffuse = reinterpret_cast<const float4&>(material.Diffuse);
    mesh.specular = reinterpret_cast<const float4&>(material.Specular);
    mesh.power = material.Power;

    {
        auto c_filename = ((D3DXMATERIAL*)materials->GetBufferPointer())[0].pTextureFilename;
        if (c_filename != nullptr && c_filename[0] != '\0')
        {
            auto filename = std::string(c_filename);
            mesh.texturePath = filename;
        }
    }

    compress(mesh);

    std::ofstream stream(dest_path);
    write(stream, mesh);
}

void convert(TemplateShape shape, std::string dest_path)
{
    com_ptr<ID3DXMesh> mesh9;

    switch (shape)
    {
    case Box:
        D3DXCreateBox(device.ptr, 1, 1, 1, &mesh9, nullptr);
        break;
    case Cylinder:
        D3DXCreateCylinder(device.ptr, 1, 1, 1, 32, 32, &mesh9, nullptr);
        break;
    case Torus:
        D3DXCreateTorus(device.ptr, 0.25f, 0.5f, 32, 32, &mesh9, nullptr);
        break;
    case Sphere:
        D3DXCreateSphere(device.ptr, 1, 32, 32, &mesh9, nullptr);
        break;
    case Teapot:
        D3DXCreateTeapot(device.ptr, &mesh9, nullptr);
        break;
    default:
        break;
    }

    Mesh mesh;
    mesh.positions = getPositionBuffer(mesh9.ptr);
    mesh.normals = getNormalBuffer(mesh9.ptr);
    mesh.indices = getIndexBuffer(mesh9.ptr);

    std::ofstream stream(dest_path);
    write(stream, mesh);
}
