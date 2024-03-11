#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "DirectXTex.lib")

#include "zephyr.graphics\Window.h"
#include "zephyr.graphics\Font.h"
#include "zephyr.graphics\Color.h"
#include "zephyr.graphics.dx11\enums.h"
#include "zephyr.graphics.dx11\GraphicsDevice.h"
#include "zephyr.graphics.dx11\GraphicsDeviceContext.h"
#include "zephyr.graphics.dx11\VertexShader.h"
#include "zephyr.graphics.dx11\PixelShader.h"
#include "zephyr.graphics.dx11\VertexBuffer.h"
#include "zephyr.graphics.dx11\VertexLayout.h"
#include "zephyr.graphics.dx11\VertexElement.h"
#include "zephyr.graphics.dx11\Texture2D.h"
#include "zephyr.graphics.dx11\Texture2DArray.h"
#include "zephyr.graphics.dx11\SamplerState.h"
#include "zephyr.graphics.dx11\ShaderResourceView.h"
#include "zephyr.graphics.dx11\ConstantBuffer.h"
#include "zephyr.linalg\Vector2.h"
#include "zephyr.linalg\Vector3.h"
#include "zephyr.linalg\Vector4.h"
#include "zephyr.linalg\Matrix4x4.h"

using namespace zephyr;
using namespace zephyr::graphics;
using namespace zephyr::graphics::dx11;
using namespace zephyr::linalg;

float deg2rad(float degrees) { return degrees * 4.0f * atan(1.0f) / 180.0f; }

void main()
{
    Window window;
    window.Create("DirectX11 �e�X�g", 800, 600);

    GraphicsDevice& device = GraphicsDevice::Instance;
    GraphicsDeviceContext& context = GraphicsDeviceContext::Instance;
    device.Create(window, false);

    struct Vertex
    {
        Vector3 position;
        Vector2 texcoord;
    };

    VertexShader vs_shader;
    {
        vs_shader.CreateFromFile("res/VertexShader.hlsl");
        context.SetVertexShader(vs_shader);
    }

    PixelShader ps_shader;
    {
        ps_shader.CreateFromFile("res/PixelShader.hlsl");
        context.SetPixelShader(ps_shader);
    }

    Texture2DArray texture;
    texture.Create("res/explos.png", 32, 32, Accessibility::None);

    ShaderResourceView view;
    {
        view.Create(texture);
    }

    ps_shader.SetTextureResource(view, 0);

    SamplerState sampler_state;
    {
        sampler_state.Create(TextureAddressMode::Wrap, TextureAddressMode::Wrap, TextureAddressMode::Wrap);
    }
    ps_shader.SetSamplerState(sampler_state, 0);

    VertexBuffer vs_buffer;
    {
        vs_buffer.Create(
            {
                Vertex{ Vector3(-0.5f, 0.5f, 0), Vector2(0, 0) },
                Vertex{ Vector3(0.5f, 0.5f, 0), Vector2(1, 0) },
                Vertex{ Vector3(-0.5f, -0.5f, 0), Vector2(0, 1) },
                Vertex{ Vector3(0.5f, -0.5f, 0), Vector2(1, 1) },
            },
            Accessibility::None);

        context.SetVertexBuffer(vs_buffer, 0);
    }

    VertexLayout layout;
    {
        VertexElement elements[] = {
            VertexElement("POSITION", 0, Format::Float3, 0, 0, VertexElement::Classification::VertexData, 0),
            VertexElement("TEXCOORD", 0, Format::Float2, 0, sizeof(float) * 3, VertexElement::Classification::VertexData, 0)
        };
        layout.Create(elements, vs_shader);
        context.SetVertexLayout(layout);
    }

    context.SetPrimitiveTopology(PrimitiveTopology::TriangleStrip);

    int frame_count = 0;
    struct
    {
        Matrix4x4 world;
        Matrix4x4 viewing;
        Matrix4x4 projection;
    } constant_data1;

    struct
    {
        float texindex;
        float _dummy1, _dummy2, _dummy3;
    } constant_data2;

    ConstantBuffer constant_buffer1;
    constant_buffer1.Create(sizeof(constant_data1));

    ConstantBuffer constant_buffer2;
    constant_buffer2.Create(sizeof(constant_data2));

    window.Updated += [&]() {
        constant_data1.world.identity();
        constant_data1.viewing.lookAt({ -1, 1, -1 }, { 0, 0, 0 });
        constant_data1.viewing.invert();
        constant_data1.projection.perspective(deg2rad(60.0f), 4.0f / 3.0f, 0.1f, 128.0f);
        constant_data2.texindex = (float)(frame_count++ % 64);

        constant_buffer1.Update(constant_data1);
        constant_buffer2.Update(constant_data2);
        vs_shader.SetConstantBuffer(constant_buffer1, 0);
        vs_shader.SetConstantBuffer(constant_buffer2, 1);

        context.Clear(ColorCode::DarkBlue);
        context.Draw(4, 0);
        context.Present();
    };

    window.Destroyed += [&]() {
        device.Release();
    };

    window.Start();
}
