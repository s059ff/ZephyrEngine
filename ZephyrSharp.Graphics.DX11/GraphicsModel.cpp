#include <fbxsdk.h>

#include "zephyr\buffer.h"
#include "zephyr\com_ptr.h"
#include "zephyr\float2.h"
#include "zephyr\float3.h"
#include "zephyr\vector.h"
#include "zephyr\print.h"
#include "zephyr\smart_ptr.h"

#include "GraphicsModel.h"
#include "GraphicsDevice.h"
#include "ConstantBuffer.h"

using fbxsdk::FbxMesh;

using zephyr::float2;
using zephyr::float3;
using zephyr::com_ptr;
using zephyr::println;

using std::vector;

using ZephyrSharp::Linalg::Vector2;
using ZephyrSharp::Linalg::Vector3;
using ZephyrSharp::Linalg::Vector4;

namespace ZephyrSharp
{
    namespace Graphics
    {
        static bool isMesh(FbxNode* node)
        {
            if (node)
            {
                int attrCount = node->GetNodeAttributeCount();

                for (int i = 0; attrCount > i; i++)
                {
                    FbxNodeAttribute::EType attrType = node->GetNodeAttributeByIndex(i)->GetAttributeType();

                    if (attrType == FbxNodeAttribute::EType::eMesh)
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        static void probeNode(FbxNode* node, GraphicsModel^ out)
        {
            if (node)
            {
                println(node->GetName());

                if (isMesh(node))
                {
                    println(" - isMesh");

                    FbxMesh* mesh = node->GetMesh();

                    if (mesh)
                    {
                        // インデックスバッファ作成
                        {
                            const int* indices = mesh->GetPolygonVertices();
                            const int count = mesh->GetPolygonVertexCount();
                            out->VertexIndices = gcnew IndexBuffer();
                            out->VertexIndices->Create(indices, count, Accessibility::None);

                            //for (int i = 0; i < count; i++)
                            //{
                            //    printf("[%d] %d\n", i, indices[i]);
                            //}
                        }

                        // 頂点バッファ作成（位置）
                        {
                            vector<float3> positions(mesh->GetControlPointsCount());
                            for (int i = 0; i < positions.size(); i++)
                            {
                                auto position = mesh->GetControlPointAt(i);
                                float x = (float)position[0];
                                float y = (float)position[1];
                                float z = (float)position[2];
                                positions[i] = { x, y, z };
                            }

                            //for (int i = 0; i < count; i++)
                            //{
                            //    float3 p = ((float3*)positions.data())[i];
                            //    printf("[%d] %f %f %f\n", i, p.x, p.y, p.z);
                            //}

                            out->VertexPositions = gcnew VertexBuffer<Vector3>();
                            out->VertexPositions->Create(positions.data(), (int)positions.size(), Accessibility::None);
                        }

                        // 頂点バッファ作成（法線）
                        {
                            FbxLayer* layer = mesh->GetLayer(0);
                            FbxLayerElementNormal* elem = layer->GetNormals();
                            if (elem != nullptr)
                            {
                                const int normalNum = elem->GetDirectArray().GetCount();
                                const int indexNum = elem->GetIndexArray().GetCount();

                                FbxLayerElement::EMappingMode mappingMode = elem->GetMappingMode();
                                FbxLayerElement::EReferenceMode refMode = elem->GetReferenceMode();

                                if (mappingMode == FbxLayerElement::eByPolygonVertex)
                                {
                                    if (refMode == FbxLayerElement::eDirect)
                                    {
                                        vector<float3> normals(normalNum);
                                        for (int i = 0; i < normalNum; ++i)
                                        {
                                            normals[i].x = (float)elem->GetDirectArray().GetAt(i)[0];
                                            normals[i].y = (float)elem->GetDirectArray().GetAt(i)[1];
                                            normals[i].z = (float)elem->GetDirectArray().GetAt(i)[2];
                                        }
                                        out->VertexNormals = gcnew VertexBuffer<Vector3>();
                                        out->VertexNormals->Create(normals.data(), (int)normals.size(), Accessibility::None);
                                    }
                                    else
                                    {
                                        vector<float3> normals(indexNum);
                                        for (int i = 0; i < indexNum; ++i)
                                        {
                                            int j = elem->GetIndexArray().GetAt(i);
                                            normals[i].x = (float)elem->GetDirectArray().GetAt(j)[0];
                                            normals[i].y = (float)elem->GetDirectArray().GetAt(j)[1];
                                            normals[i].z = (float)elem->GetDirectArray().GetAt(j)[2];
                                        }
                                        out->VertexNormals = gcnew VertexBuffer<Vector3>();
                                        out->VertexNormals->Create(normals.data(), (int)normals.size(), Accessibility::None);
                                    }
                                }
                                else if (mappingMode == FbxLayerElement::eByControlPoint)
                                {
                                    runtime_assert(false, "マッピングモードが非対応です。");
                                }
                            }
                        }

                        // 頂点バッファ作成（UV座標）
                        {
                            FbxLayer* layer = mesh->GetLayer(0);
                            FbxLayerElementUV* elem = layer->GetUVs();
                            if (elem != nullptr)
                            {
                                int uvNum = elem->GetDirectArray().GetCount();
                                int indexNum = elem->GetIndexArray().GetCount();

                                FbxLayerElement::EMappingMode mappingMode = elem->GetMappingMode();
                                FbxLayerElement::EReferenceMode	refMode = elem->GetReferenceMode();

                                if (mappingMode == FbxLayerElement::eByPolygonVertex)
                                {
                                    if (refMode == FbxLayerElement::eDirect)
                                    {
                                        vector<float2> texcoords(uvNum);
                                        for (int i = 0; i < texcoords.size(); ++i)
                                        {
                                            texcoords[i].u = (float)elem->GetDirectArray().GetAt(i)[0];
                                            texcoords[i].v = (float)elem->GetDirectArray().GetAt(i)[1];
                                        }
                                        out->VertexTextureCoords = gcnew VertexBuffer<Vector2>();
                                        out->VertexTextureCoords->Create(texcoords.data(), (int)texcoords.size(), Accessibility::None);
                                    }
                                    else if (refMode == FbxLayerElement::eIndexToDirect)
                                    {
                                        vector<float2> texcoords(indexNum);
                                        for (int i = 0; i < texcoords.size(); ++i)
                                        {
                                            int j = elem->GetIndexArray().GetAt(i);
                                            texcoords[i].u = (float)elem->GetDirectArray().GetAt(j)[0];
                                            texcoords[i].v = (float)elem->GetDirectArray().GetAt(j)[1];
                                        }
                                        out->VertexTextureCoords = gcnew VertexBuffer<Vector2>();
                                        out->VertexTextureCoords->Create(texcoords.data(), (int)texcoords.size(), Accessibility::None);
                                    }
                                }
                            }
                        }

                        out->ChildModels = gcnew array<GraphicsModel^>(node->GetChildCount());
                        for (int i = 0; i < node->GetChildCount(); i++)
                        {
                            out->ChildModels[i] = gcnew GraphicsModel();
                            probeNode(node->GetChild(i), out->ChildModels[i]);
                        }
                    }
                }
            }
        }

        void GraphicsModel::CreateFromFBX(String^ path)
        {
            FbxManager* manager = FbxManager::Create();
            if (manager)
            {
                FbxImporter* importer = FbxImporter::Create(manager, "");

                if (importer->Initialize(to_string(path).c_str()))
                {
                    FbxScene* scene = FbxScene::Create(manager, "");
                    bool succeeded = importer->Import(scene);
                    importer->Destroy();

                    FbxGeometryConverter converter(manager);
                    converter.Triangulate(scene, true);

                    FbxAxisSystem SceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();
                    if (SceneAxisSystem != FbxAxisSystem::DirectX)
                        FbxAxisSystem::DirectX.ConvertScene(scene);

                    if (succeeded)
                    {
                        FbxNode* rootNode = scene->GetRootNode();

                        if (rootNode)
                        {
                            for (int i = 0; rootNode->GetChildCount() > i; i++)
                            {
                                probeNode(rootNode->GetChild(i), this);
                            }
                        }
                    }
                }
                manager->Destroy();
            }

            this->Topology = PrimitiveTopology::TriangleList;
        }
        
        void GraphicsModel::CreateFromCX(String^ path)
        {
            path = System::IO::Path::GetFullPath(path);
            auto stream = gcnew System::IO::FileStream(path, System::IO::FileMode::Open);
            auto dir = System::Environment::CurrentDirectory;
            System::Environment::CurrentDirectory = System::IO::Path::GetDirectoryName(path);
            this->CreateFromCX(stream);
            System::Environment::CurrentDirectory = dir;
            delete stream;
        }

        void GraphicsModel::CreateSphere(int slices, int stacks)
        {
            //this->CreateFromCX(this->GetType()->Assembly->GetManifestResourceStream("sphere.cx"));

            using namespace System::Collections::Generic;

            auto positions = gcnew List<Vector3>((stacks + 1) * (slices + 1));
            auto normals = gcnew List<Vector3>((stacks + 1) * (slices + 1));
            for (int i = 0; i < stacks + 1; i++)
            {
                float y = 1.0f - 2.0f * (float)i / stacks;
                float r = sqrt(1 - y * y);
                for (int j = 0; j < slices + 1; j++)
                {
                    float t = (float)j / slices * 3.14159f * 2;
                    float x = r * cos(t);
                    float z = r * sin(t);
                    positions->Add(Vector3(x / 2, y / 2, z / 2));
                    normals->Add(Vector3(x / 2, y / 2, z / 2).Normalize());
                }
            }

            auto indices = gcnew List<int>();
            for (int i = 0; i < stacks; i++)
            {
                for (int j = 0; j < slices; j++)
                {
                    int i0 = (slices + 1) * i + j;
                    int i1 = i0 + 1;
                    int i2 = (slices + 1) * (i + 1) + j;
                    int i3 = i2 + 1;
                    indices->Add(i0);
                    indices->Add(i2);
                    indices->Add(i1);
                    indices->Add(i1);
                    indices->Add(i2);
                    indices->Add(i3);
                }
            }

            this->VertexPositions = gcnew VertexBuffer<Vector3>();
            this->VertexPositions->Create(positions->ToArray(), Accessibility::None);
            this->VertexNormals = gcnew VertexBuffer<Vector3>();
            this->VertexNormals->Create(normals->ToArray(), Accessibility::None);
            this->VertexIndices = gcnew IndexBuffer();
            this->VertexIndices->Create(indices->ToArray(), Accessibility::None);
        }

        void GraphicsModel::CreateBox()
        {
            this->CreateFromCX(this->GetType()->Assembly->GetManifestResourceStream("box.cx"));
        }

        void GraphicsModel::CreateCylinder(int slices, int stacks)
        {
            this->CreateFromCX(this->GetType()->Assembly->GetManifestResourceStream("cylinder.cx"));
        }

        void GraphicsModel::CreateTorus()
        {
            this->CreateFromCX(this->GetType()->Assembly->GetManifestResourceStream("torus.cx"));
        }

        void GraphicsModel::CreateTeapot()
        {
            this->CreateFromCX(this->GetType()->Assembly->GetManifestResourceStream("teapot.cx"));
        }

        void GraphicsModel::CreateLineList(array<Vector3>^ positions)
        {
            this->VertexPositions = gcnew VertexBuffer<Vector3>();
            this->VertexPositions->Create(positions, Accessibility::None);
            this->Topology = PrimitiveTopology::LineList;
        }

        void GraphicsModel::CreateLineList(array<Vector3>^ positions, array<Color>^ colors)
        {
            this->VertexPositions = gcnew VertexBuffer<Vector3>();
            this->VertexPositions->Create(positions, Accessibility::None);
            this->VertexColors = gcnew VertexBuffer<Color>();
            this->VertexColors->Create(colors, Accessibility::None);
            this->Topology = PrimitiveTopology::LineList;
        }

        void GraphicsModel::CreateLineStrip(array<Vector3>^ positions)
        {
            this->VertexPositions = gcnew VertexBuffer<Vector3>();
            this->VertexPositions->Create(positions, Accessibility::None);
            this->Topology = PrimitiveTopology::LineStrip;
        }

        void GraphicsModel::CreateLineStrip(array<Vector3>^ positions, array<Color>^ colors)
        {
            this->VertexPositions = gcnew VertexBuffer<Vector3>();
            this->VertexPositions->Create(positions, Accessibility::None);
            this->VertexColors = gcnew VertexBuffer<Color>();
            this->VertexColors->Create(colors, Accessibility::None);
            this->Topology = PrimitiveTopology::LineStrip;
        }

        void GraphicsModel::CreateBillBoard()
        {
            const int VertexCount = 4;

            array<Vector3>^ positions = gcnew array<Vector3>(VertexCount);
            array<Vector3>^ normals = gcnew array<Vector3>(VertexCount);
            array<Color>^ colors = gcnew array<Color>(VertexCount);
            array<Vector2>^ texcoords = gcnew array<Vector2>(VertexCount);

            positions[0] = Vector3(-0.5f, +0.5f, 0);
            positions[1] = Vector3(+0.5f, +0.5f, 0);
            positions[2] = Vector3(-0.5f, -0.5f, 0);
            positions[3] = Vector3(+0.5f, -0.5f, 0);

            normals[0] = Vector3(0, 0, -1);
            normals[1] = Vector3(0, 0, -1);
            normals[2] = Vector3(0, 0, -1);
            normals[3] = Vector3(0, 0, -1);

            colors[0] = Color(1, 1, 1);
            colors[1] = Color(1, 1, 1);
            colors[2] = Color(1, 1, 1);
            colors[3] = Color(1, 1, 1);

            texcoords[0] = Vector2(0, 0);
            texcoords[1] = Vector2(1, 0);
            texcoords[2] = Vector2(0, 1);
            texcoords[3] = Vector2(1, 1);

            this->VertexPositions = gcnew VertexBuffer<Vector3>();
            this->VertexPositions->Create(positions, Accessibility::None);
            this->VertexNormals = gcnew VertexBuffer<Vector3>();
            this->VertexNormals->Create(normals, Accessibility::None);
            this->VertexColors = gcnew VertexBuffer<Color>();
            this->VertexColors->Create(colors, Accessibility::None);
            this->VertexTextureCoords = gcnew VertexBuffer<Vector2>();
            this->VertexTextureCoords->Create(texcoords, Accessibility::None);
            this->Topology = PrimitiveTopology::TriangleStrip;
        }

        generic <typename T> static array<T>^ toArrayDim1(array<T, 2>^ arrayDim2)
        {
            const int N = arrayDim2->GetLength(0);
            const int M = arrayDim2->GetLength(1);

            array<T>^ arrayDim1 = gcnew array<T>(N * M);
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    arrayDim1[i * M + j] = arrayDim2[i, j];
                }
            }

            return arrayDim1;
        }

        void GraphicsModel::CreateMeshMap(array<float, 2>^ heights)
        {
            runtime_assert(heights->GetLength(0) == heights->GetLength(1), "ハイトマップが正方行列になっていません");

            // 一辺の頂点数
            const int N = heights->GetLength(0);

            // ローカル座標を生成する
            array<Vector3, 2>^ positions = gcnew array<Vector3, 2>(N, N);
            for (int y = 0; y < N; y++)
            {
                for (int x = 0; x < N; x++)
                {
                    positions[y, x].X = -0.5f + (float)x / (float)(N - 1);
                    positions[y, x].Y = 0.5f - (float)y / (float)(N - 1);
                    positions[y, x].Z = -heights[y, x];
                }
            }

            // 法線を作成する
            array<Vector3, 2>^ normals = gcnew array<Vector3, 2>(N, N);
            for (int y = 1; y < N - 1; y++)
            {
                for (int x = 1; x < N - 1; x++)
                {
                    Vector3 v1 = Vector3::operator-(positions[y, x - 1], positions[y, x]);
                    Vector3 v2 = Vector3::operator-(positions[y, x + 1], positions[y, x]);
                    Vector3 v3 = Vector3::operator-(positions[y - 1, x], positions[y, x]);
                    Vector3 v4 = Vector3::operator-(positions[y + 1, x], positions[y, x]);
                    Vector3 n1 = Vector3::Outer(v1, v3).Normalize();
                    Vector3 n2 = Vector3::Outer(v3, v2).Normalize();
                    Vector3 n3 = Vector3::Outer(v2, v4).Normalize();
                    Vector3 n4 = Vector3::Outer(v4, v1).Normalize();
                    normals[y, x] = (n1 + n2 + n3 + n4).Normalize();
                }
            }
            for (int i = 0; i < N; i++)
            {
                normals[i, 0] = Vector3(0, 0, -1);
                normals[i, N - 1] = Vector3(0, 0, -1);
                normals[0, i] = Vector3(0, 0, -1);
                normals[N - 1, i] = Vector3(0, 0, -1);
            }

            // テクスチャ座標を作成する
            array<Vector2, 2>^ texcoords = gcnew array<Vector2, 2>(N, N);
            for (int y = 0; y < N; y++)
            {
                for (int x = 0; x < N; x++)
                {
                    texcoords[y, x].X = (float)x;
                    texcoords[y, x].Y = (float)y;
                }
            }

            // インデックスバッファを生成する
            array<int>^ indices = gcnew array<int>(3 * 2 * (N - 1) * (N - 1));
            int k = 0;
            for (int y = 0; y < N - 1; y++)
            {
                for (int x = 0; x < N - 1; x++)
                {
                    indices[k++] = y * N + x;
                    indices[k++] = y * N + (x + 1);
                    indices[k++] = (y + 1) * N + x;

                    indices[k++] = (y + 1) * N + (x + 1);
                    indices[k++] = (y + 1) * N + x;
                    indices[k++] = y * N + (x + 1);
                }
            }

            // 
            this->VertexPositions = gcnew VertexBuffer<Vector3>();
            this->VertexPositions->Create(toArrayDim1(positions), Accessibility::None);
            this->VertexNormals = gcnew VertexBuffer<Vector3>();
            this->VertexNormals->Create(toArrayDim1(normals), Accessibility::None);
            this->VertexTextureCoords = gcnew VertexBuffer<Vector2>();
            this->VertexTextureCoords->Create(toArrayDim1(texcoords), Accessibility::None);
            this->VertexIndices = gcnew IndexBuffer();
            this->VertexIndices->Create(indices, Accessibility::None);

            this->Topology = PrimitiveTopology::TriangleList;
        }

        void GraphicsModel::CreateFromCX(System::IO::Stream^ _stream)
        {
            System::IO::StreamReader^ stream = gcnew System::IO::StreamReader(_stream);

            do
            {
                auto semantics = stream->ReadLine()->Trim()->ToUpper();
                if (semantics == "[POSITION]")
                {
                    int count = int::Parse(stream->ReadLine());
                    array<Vector3>^ vertices = gcnew array<Vector3>(count);
                    for (int i = 0; i < count; i++)
                    {
                        vertices[i] = Vector3::Parse(stream->ReadLine());
                    }
                    this->VertexPositions = gcnew VertexBuffer<Vector3>();
                    this->VertexPositions->Create(vertices, Accessibility::None);
                }
                else if (semantics == "[NORMAL]")
                {
                    int count = int::Parse(stream->ReadLine());
                    array<Vector3>^ vertices = gcnew array<Vector3>(count);
                    for (int i = 0; i < count; i++)
                    {
                        vertices[i] = Vector3::Parse(stream->ReadLine());
                    }
                    this->VertexNormals = gcnew VertexBuffer<Vector3>();
                    this->VertexNormals->Create(vertices, Accessibility::None);
                }
                else if (semantics == "[TEXCOORD]")
                {
                    int count = int::Parse(stream->ReadLine());
                    array<Vector2>^ vertices = gcnew array<Vector2>(count);
                    for (int i = 0; i < count; i++)
                    {
                        vertices[i] = Vector2::Parse(stream->ReadLine());
                    }
                    this->VertexTextureCoords = gcnew VertexBuffer<Vector2>();
                    this->VertexTextureCoords->Create(vertices, Accessibility::None);
                }
                else if (semantics == "[COLOR]")
                {
                    int count = int::Parse(stream->ReadLine());
                    array<Color>^ vertices = gcnew array<Color>(count);
                    for (int i = 0; i < count; i++)
                    {
                        vertices[i] = Color::Parse(stream->ReadLine());
                    }
                    this->VertexColors = gcnew VertexBuffer<Color>();
                    this->VertexColors->Create(vertices, Accessibility::None);
                }
                else if (semantics == "[TANGENT]")
                {
                    int count = int::Parse(stream->ReadLine());
                    array<Vector3>^ vertices = gcnew array<Vector3>(count);
                    for (int i = 0; i < count; i++)
                    {
                        vertices[i] = Vector3::Parse(stream->ReadLine());
                    }
                    this->VertexTangents = gcnew VertexBuffer<Vector3>();
                    this->VertexTangents->Create(vertices, Accessibility::None);
                }
                else if (semantics == "[BINORMAL]")
                {
                    int count = int::Parse(stream->ReadLine());
                    array<Vector3>^ vertices = gcnew array<Vector3>(count);
                    for (int i = 0; i < count; i++)
                    {
                        vertices[i] = Vector3::Parse(stream->ReadLine());
                    }
                    this->VertexBinormals = gcnew VertexBuffer<Vector3>();
                    this->VertexBinormals->Create(vertices, Accessibility::None);
                }
                else if (semantics == "[INDEX]")
                {
                    int count = int::Parse(stream->ReadLine());
                    array<int>^ indices = gcnew array<int>(count);
                    for (int i = 0; i < count; i++)
                    {
                        indices[i] = int::Parse(stream->ReadLine());
                    }
                    this->VertexIndices = gcnew IndexBuffer();
                    this->VertexIndices->Create(indices, Accessibility::None);
                }
                else if (semantics == "[MATERIAL]")
                {
                    this->Material.Ambient = Color::Parse(stream->ReadLine());
                    this->Material.Diffuse = Color::Parse(stream->ReadLine());
                    this->Material.Specular = Color::Parse(stream->ReadLine());
                    this->Material.Power = float::Parse(stream->ReadLine());
                }
                else if (semantics == "[TEXTURE]")
                {
                    this->Texture = gcnew Texture2D();
                    this->Texture->Create(stream->ReadLine(), Accessibility::None);
                }
            } while (!stream->EndOfStream);

            delete stream;

            this->Topology = PrimitiveTopology::TriangleList;
        }
    }
}
