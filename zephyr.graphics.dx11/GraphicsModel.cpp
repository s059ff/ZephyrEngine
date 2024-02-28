#include <fbxsdk.h>

#include "zephyr\buffer.h"
#include "zephyr\com_ptr.h"
#include "zephyr\float2.h"
#include "zephyr\float3.h"
#include "zephyr\vector.h"
#include "zephyr\print.h"
#include "zephyr\smart_ptr.h"
#include "zephyr\stream.h"
#include "zephyr.linalg\linalg.h"
#include "zephyr.filesystem\Directory.h"
#include "zephyr.filesystem\Path.h"

#include "GraphicsModel.h"
#include "GraphicsDevice.h"
#include "ConstantBuffer.h"

using fbxsdk::FbxMesh;

using zephyr::float2;
using zephyr::float3;
using zephyr::com_ptr;
using zephyr::println;

using std::vector;

using zephyr::linalg::Vector2;
using zephyr::linalg::Vector3;
using zephyr::linalg::Vector4;

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
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

            static void probeNode(FbxNode* node, GraphicsModel* out)
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
                                out->VertexIndices.Create(indices, count, Accessibility::None);

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

                                out->VertexPositions.Create(positions.data(), (int)positions.size(), Accessibility::None);
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
                                            out->VertexNormals.Create(normals.data(), (int)normals.size(), Accessibility::None);
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
                                            out->VertexNormals.Create(normals.data(), (int)normals.size(), Accessibility::None);
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
                                            out->VertexTextureCoords.Create(texcoords.data(), (int)texcoords.size(), Accessibility::None);
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
                                            out->VertexTextureCoords.Create(texcoords.data(), (int)texcoords.size(), Accessibility::None);
                                        }
                                    }
                                }
                            }

                            out->ChildModels.resize(node->GetChildCount());
                            for (int i = 0; i < node->GetChildCount(); i++)
                            {
                                probeNode(node->GetChild(i), &out->ChildModels[i]);
                            }
                        }
                    }
                }
            }

            void GraphicsModel::CreateFromFBX(const string& path)
            {
                FbxManager* manager = FbxManager::Create();
                if (manager)
                {
                    FbxImporter* importer = FbxImporter::Create(manager, "");

                    if (importer->Initialize(path.c_str()))
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

            void GraphicsModel::CreateFromCX(const string& _path)
            {
                auto path = zephyr::filesystem::Path::GetFullPath(_path);
                auto dir = zephyr::filesystem::Path::GetDirectoryName(path);
                auto old_dir = zephyr::filesystem::Directory::GetCurrentDirectory();
                zephyr::filesystem::Directory::SetCurrentDirectory(dir);

                std::ifstream stream(path);

                auto readline = [](std::ifstream& stream) {
                    string text;
                    std::getline(stream, text);
                    return text;
                };

                do
                {
                    auto semantics = readline(stream);
                    if (semantics == "[POSITION]")
                    {
                        int count = std::stoi(readline(stream));
                        vector<Vector3> vertices(count);
                        for (int i = 0; i < count; i++)
                        {
                            vertices[i] = Vector3::Parse(readline(stream));
                        }
                        this->VertexPositions.Create(vertices.data(), count, Accessibility::None);
                    }
                    else if (semantics == "[NORMAL]")
                    {
                        int count = stoi(readline(stream));
                        vector<Vector3> vertices(count);
                        for (int i = 0; i < count; i++)
                        {
                            vertices[i] = Vector3::Parse(readline(stream));
                        }
                        this->VertexNormals.Create(vertices.data(), count, Accessibility::None);
                    }
                    else if (semantics == "[TEXCOORD]")
                    {
                        int count = stoi(readline(stream));
                        vector<Vector2> vertices(count);
                        for (int i = 0; i < count; i++)
                        {
                            vertices[i] = Vector2::Parse(readline(stream));
                        }
                        this->VertexTextureCoords.Create(vertices.data(), count, Accessibility::None);
                    }
                    else if (semantics == "[COLOR]")
                    {
                        int count = stoi(readline(stream));
                        vector<Color> vertices(count);
                        for (int i = 0; i < count; i++)
                        {
                            vertices[i] = Color::Parse(readline(stream));
                        }
                        this->VertexColors.Create(vertices.data(), count, Accessibility::None);
                    }
                    else if (semantics == "[TANGENT]")
                    {
                        int count = stoi(readline(stream));
                        vector<Vector3> vertices(count);
                        for (int i = 0; i < count; i++)
                        {
                            vertices[i] = Vector3::Parse(readline(stream));
                        }
                        this->VertexTangents.Create(vertices.data(), count, Accessibility::None);
                    }
                    else if (semantics == "[BINORMAL]")
                    {
                        int count = stoi(readline(stream));
                        vector<Vector3> vertices(count);
                        for (int i = 0; i < count; i++)
                        {
                            vertices[i] = Vector3::Parse(readline(stream));
                        }
                        this->VertexBinormals.Create(vertices.data(), count, Accessibility::None);
                    }
                    else if (semantics == "[INDEX]")
                    {
                        int count = stoi(readline(stream));
                        vector<int> indices(count);
                        for (int i = 0; i < count; i++)
                        {
                            indices[i] = stoi(readline(stream));
                        }
                        this->VertexIndices.Create(indices.data(), count, Accessibility::None);
                    }
                    else if (semantics == "[MATERIAL]")
                    {
                        this->Material.ambient = Color::Parse(readline(stream));
                        this->Material.diffuse = Color::Parse(readline(stream));
                        this->Material.specular = Color::Parse(readline(stream));
                        this->Material.power = stof(readline(stream));
                    }
                    else if (semantics == "[TEXTURE]")
                    {
                        this->Texture.Create(readline(stream), Accessibility::None);
                    }
                } while (!stream.eof());

                this->Topology = PrimitiveTopology::TriangleList;

                zephyr::filesystem::Directory::SetCurrentDirectory(old_dir);
            }

            void GraphicsModel::CreateSphere(int slices, int stacks)
            {
                auto positions = vector<Vector3>();
                positions.reserve((stacks + 1) * (slices + 1));
                auto normals = vector<Vector3>();
                normals.reserve((stacks + 1) * (slices + 1));
                for (int i = 0; i < stacks + 1; i++)
                {
                    float y = 1.0f - 2.0f * (float)i / stacks;
                    float r = sqrt(1 - y * y);
                    for (int j = 0; j < slices + 1; j++)
                    {
                        float t = (float)j / slices * 3.14159f * 2;
                        float x = r * cos(t);
                        float z = r * sin(t);
                        positions.push_back(Vector3(x / 2, y / 2, z / 2));
                        normals.push_back(Vector3(x / 2, y / 2, z / 2).normalize());
                    }
                }

                auto indices = vector<int>();
                for (int i = 0; i < stacks; i++)
                {
                    for (int j = 0; j < slices; j++)
                    {
                        int i0 = (slices + 1) * i + j;
                        int i1 = i0 + 1;
                        int i2 = (slices + 1) * (i + 1) + j;
                        int i3 = i2 + 1;
                        indices.push_back(i0);
                        indices.push_back(i2);
                        indices.push_back(i1);
                        indices.push_back(i1);
                        indices.push_back(i2);
                        indices.push_back(i3);
                    }
                }

                this->VertexPositions.Create(positions.data(), positions.size(), Accessibility::None);
                this->VertexNormals.Create(normals.data(), normals.size(), Accessibility::None);
                this->VertexIndices.Create(indices.data(), indices.size(), Accessibility::None);
            }

            void GraphicsModel::CreateLineList(const vector<Vector3>& positions)
            {
                this->VertexPositions.Create(positions.data(), positions.size(), Accessibility::None);
                this->Topology = PrimitiveTopology::LineList;
            }

            void GraphicsModel::CreateLineList(const vector<Vector3>& positions, const vector<Color>& colors)
            {
                this->VertexPositions.Create(positions.data(), positions.size(), Accessibility::None);
                this->VertexColors.Create(colors.data(), colors.size(), Accessibility::None);
                this->Topology = PrimitiveTopology::LineList;
            }

            void GraphicsModel::CreateLineStrip(const vector<Vector3>& positions)
            {
                this->VertexPositions.Create(positions.data(), positions.size(), Accessibility::None);
                this->Topology = PrimitiveTopology::LineStrip;
            }

            void GraphicsModel::CreateLineStrip(const vector<Vector3>& positions, const vector<Color>& colors)
            {
                this->VertexPositions.Create(positions.data(), positions.size(), Accessibility::None);
                this->VertexColors.Create(colors.data(), colors.size(), Accessibility::None);
                this->Topology = PrimitiveTopology::LineStrip;
            }

            void GraphicsModel::CreateBillBoard()
            {
                const int VertexCount = 4;

                vector<Vector3> positions(VertexCount);
                vector<Vector3> normals(VertexCount);
                vector<Color> colors(VertexCount);
                vector<Vector2> texcoords(VertexCount);

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

                this->VertexPositions.Create(positions.data(), positions.size(), Accessibility::None);
                this->VertexNormals.Create(normals.data(), normals.size(), Accessibility::None);
                this->VertexColors.Create(colors.data(), colors.size(), Accessibility::None);
                this->VertexTextureCoords.Create(texcoords.data(), texcoords.size(), Accessibility::None);
                this->Topology = PrimitiveTopology::TriangleStrip;
            }

            void GraphicsModel::CreateMeshMap(const matrix<float>& heights)
            {
                // 一辺の頂点数
                const int N = (int)sqrt(heights.rows);

                // ローカル座標を生成する
                matrix<Vector3> positions(N, N);
                for (int y = 0; y < N; y++)
                {
                    for (int x = 0; x < N; x++)
                    {
                        positions(y, x).x = -0.5f + (float)x / (float)(N - 1);
                        positions(y, x).y = 0.5f - (float)y / (float)(N - 1);
                        positions(y, x).z = -heights(y, x);
                    }
                }

                // 法線を作成する
                matrix<Vector3> normals(N, N);
                for (int y = 1; y < N - 1; y++)
                {
                    for (int x = 1; x < N - 1; x++)
                    {
                        Vector3 v1 = positions(y, x - 1) - positions(y, x);
                        Vector3 v2 = positions(y, x + 1) - positions(y, x);
                        Vector3 v3 = positions(y - 1, x) - positions(y, x);
                        Vector3 v4 = positions(y + 1, x) - positions(y, x);
                        Vector3 n1 = outer(v1, v3).normalize();
                        Vector3 n2 = outer(v3, v2).normalize();
                        Vector3 n3 = outer(v2, v4).normalize();
                        Vector3 n4 = outer(v4, v1).normalize();
                        normals(y, x) = (n1 + n2 + n3 + n4).normalize();
                    }
                }
                for (int i = 0; i < N; i++)
                {
                    normals(i, 0) = Vector3(0, 0, -1);
                    normals(i, N - 1) = Vector3(0, 0, -1);
                    normals(0, i) = Vector3(0, 0, -1);
                    normals(N - 1, i) = Vector3(0, 0, -1);
                }

                // テクスチャ座標を作成する
                matrix<Vector2> texcoords(N, N);
                for (int y = 0; y < N; y++)
                {
                    for (int x = 0; x < N; x++)
                    {
                        texcoords(y, x).x = (float)x;
                        texcoords(y, x).y = (float)y;
                    }
                }

                // インデックスバッファを生成する
                vector<int> indices(3 * 2 * (N - 1) * (N - 1));
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
                this->VertexPositions.Create(positions.data(), positions.rows * positions.cols, Accessibility::None);
                this->VertexNormals.Create(normals.data(), normals.rows * normals.cols, Accessibility::None);
                this->VertexTextureCoords.Create(texcoords.data(), texcoords.rows * texcoords.cols, Accessibility::None);
                this->VertexIndices.Create(indices.data(), indices.size(), Accessibility::None);

                this->Topology = PrimitiveTopology::TriangleList;
            }
        }
    }
}
