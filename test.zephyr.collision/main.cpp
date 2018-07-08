#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "DirectXTex.lib")

#include "zephyr.linalg\Matrix4x3.h"
#include "zephyr.linalg\Vector3.h"
#include "zephyr.linalg\Vector4.h"
#include "zephyr.graphics\Color.h"
#include "zephyr.graphics\Window.h"
#include "zephyr.graphics.dx11\GraphicsDevice.h"
#include "zephyr.graphics.dx11\VertexShader.h"
#include "zephyr.graphics.dx11\PixelShader.h"
#include "zephyr.graphics.dx11\VertexLayout.h"
#include "zephyr.graphics.dx11\VertexElement.h"
#include "zephyr.graphics.dx11\GraphicsModel.h"
#include "zephyr.graphics.dx11\ConstantBuffer.h"
#include "zephyr.filesystem\Directory.h"
#include "zephyr.collision\shapes.h"
#include "zephyr.collision\CollisionObject.h"

using namespace zephyr;
using namespace zephyr::collision;
using namespace zephyr::linalg;
using namespace zephyr::graphics;
using namespace zephyr::graphics::dx11;
using namespace zephyr::filesystem;

static float r = -1.0f;

static Matrix4x3 world1 = Matrix4x3().lookAt(Vector3(-0.9f, 0.8f, 0.7f), Vector3());

static Matrix4x3 world2 = Matrix4x3().identity().rotateX(3.14159f / 2);

void main()
{
    Window window;
    window.Create("C# Collision ƒeƒXƒg", 800, 600);

    auto& device = GraphicsDevice::Instance;
    device.Create(window);

    VertexShader vs_shader;
    vs_shader.CreateFromFile("res/VertexShader.hlsl");

    PixelShader ps_shader;
    ps_shader.CreateFromFile("res/PixelShader.hlsl");

    VertexLayout layout;
    {
        VertexElement elements[] =
        {
            VertexElement("POSITION", 0, Format::Float3, 0, 0, VertexElement::Classification::VertexData, 0),
            VertexElement("NORMAL", 0, Format::Float3, 1, 0, VertexElement::Classification::VertexData, 0),
        };
        layout.Create(elements, vs_shader);
    }

    device.SetVertexShader(vs_shader);
    device.SetPixelShader(ps_shader);
    device.SetVertexLayout(layout);

    GraphicsModel sphere;
    sphere.CreateSphere(16, 16);

    GraphicsModel model1;
    model1.CreateLineList({ Vector3(0, 0, 0), Vector3(0, 0, 1) });

    CollisionObject<Point> model1_c;
    model1_c.velocity = Vector3(world1.m31, world1.m32, world1.m33);
    model1_c.matrix = world1;

    GraphicsModel model2;
    model2.CreateFromCX("res/box.cx");

    CollisionObject<Box> model2_c;
    model2_c.matrix = world2;

    ConstantBuffer vs_c0;
    ConstantBuffer ps_c0, ps_c1, ps_c2;
    vs_c0.Create(sizeof(Matrix4x4));
    ps_c0.Create(sizeof(Matrix4x4));
    ps_c1.Create(sizeof(Vector4));
    ps_c2.Create(sizeof(Vector4));

    window.Updated += [&]()
    {
        device.Clear(Color(ColorCode::Black));

        auto point = model1_c.collide_point(&model2_c);

        auto viewing = Matrix4x4().identity().lookAt(Vector3(cos(r), 0.5f, sin(r)) * 4, Vector3::Zero).inverse;
        auto projection = Matrix4x4().identity().perspective(3.14f / 3, 4.0f / 3.0f, 0.1f, 128.0f);

        {
            device.SetVertexBuffer(model1.VertexPositions, 0);
            device.SetPrimitiveTopology(model1.Topology);

            vs_c0.Update(Matrix4x4(world1 * viewing * projection));
            ps_c0.Update(Matrix4x4(world1));
            ps_c1.Update(Color(0, 1, 0));
            ps_c2.Update(Vector4(1, 1, 1, 1));

            vs_shader.SetConstantBuffer(vs_c0, 0);
            ps_shader.SetConstantBuffer(ps_c0, 0);
            ps_shader.SetConstantBuffer(ps_c1, 1);
            ps_shader.SetConstantBuffer(ps_c2, 2);

            device.Draw(model1.VertexPositions.count, 0);
        }

        {
            device.SetVertexBuffer(model2.VertexPositions, 0);
            device.SetVertexBuffer(model2.VertexNormals, 1);
            device.SetPrimitiveTopology(model2.Topology);
            device.SetIndexBuffer(model2.VertexIndices);

            vs_c0.Update(Matrix4x4(world2 * viewing * projection));
            ps_c0.Update(Matrix4x4(world2));
            ps_c1.Update(Color(1, 0, 0));
            ps_c2.Update(Vector4(1, 1, 1, 1));

            vs_shader.SetConstantBuffer(vs_c0, 0);
            ps_shader.SetConstantBuffer(ps_c0, 0);
            ps_shader.SetConstantBuffer(ps_c1, 1);
            ps_shader.SetConstantBuffer(ps_c2, 2);

            device.DrawIndexed(model2.VertexIndices.count, 0);
        }

        {
            auto world = Matrix4x3().identity().translate(point).scale(0.25f);
            device.SetPrimitiveTopology(sphere.Topology);

            device.SetVertexBuffer(sphere.VertexPositions, 0);
            device.SetVertexBuffer(sphere.VertexNormals, 1);
            device.SetIndexBuffer(sphere.VertexIndices);

            vs_c0.Update(Matrix4x4(world * viewing * projection));
            ps_c0.Update(Matrix4x4(world));
            ps_c1.Update(Color(0, 0, 1));
            ps_c2.Update(Vector4(1, 1, 1, 1));

            vs_shader.SetConstantBuffer(vs_c0, 0);
            ps_shader.SetConstantBuffer(ps_c0, 0);
            ps_shader.SetConstantBuffer(ps_c1, 1);
            ps_shader.SetConstantBuffer(ps_c2, 2);

            device.DrawIndexed(sphere.VertexIndices.count, 0);
        }

        device.Present();

        r += 0.01f;
    };

    window.Start();
}
