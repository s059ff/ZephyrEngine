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
#include "zephyr.graphics.dx11\GeometryShader.h"
#include "zephyr.graphics.dx11\PixelShader.h"
#include "zephyr.graphics.dx11\VertexBuffer.h"
#include "zephyr.graphics.dx11\VertexLayout.h"
#include "zephyr.graphics.dx11\VertexElement.h"
#include "zephyr.graphics.dx11\Texture2D.h"
#include "zephyr.graphics.dx11\Texture2DArray.h"
#include "zephyr.graphics.dx11\ShaderResourceView.h"
#include "zephyr.graphics.dx11\ConstantBuffer.h"
#include "zephyr.graphics.dx11\InstanceBuffer.h"
#include "zephyr.linalg\Vector2.h"
#include "zephyr.linalg\Vector3.h"
#include "zephyr.linalg\Matrix4x4.h"

using namespace zephyr;
using namespace zephyr::graphics;
using namespace zephyr::graphics::dx11;
using namespace zephyr::linalg;

float deg2rad(float degrees) { return degrees * 4.0f * atan(1.0f) / 180.0f; }

void main()
{
    Window window;
    window.Create("DirectX11 インスタンシング テスト", 800, 600);

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
    ColorCode init[32 * 32 * 2];
    for (size_t i = 0; i < 32; i++)
    {
        for (size_t j = 0; j < 32; j++)
        {
            init[i * 32 + j] = ColorCode(i * 8, j * 8, 0, 255);
            init[i * 32 + j + 32 * 32] = ColorCode(0, i * 8, j * 8, 255);
        }
    }
    texture.Create(init, 32, 32, 2, Format::UByte4Norm, Accessibility::None, BufferBindFlags::ShaderResource);

    ShaderResourceView view;
    {
        view.Create(texture);
    }

    ps_shader.SetTextureResource(view, 0);

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

    InstanceBuffer is_buffer;
    {
        is_buffer.Create(
        {
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(1.0f, 0.0f, 0.0f),
            Vector3(0.0f, 1.0f, 1.0f),
            Vector3(1.0f, 1.0f, 1.0f),
        },
        Accessibility::None);

		context.SetInstanceBuffer(is_buffer, 1);
    }

    VertexLayout layout;
    {
        VertexElement elements[] = {
            VertexElement("POSITION", 0, Format::Float3, 0, 0, VertexElement::Classification::VertexData, 0),
            VertexElement("TEXCOORD", 0, Format::Float2, 0, sizeof(float) * 3, VertexElement::Classification::VertexData, 0),
            VertexElement("OFFSET", 0, Format::Float2, 1, 0, VertexElement::Classification::InstanceData, 1),
            VertexElement("TEXINDEX", 0, Format::Float1, 1, sizeof(float) * 2, VertexElement::Classification::InstanceData, 1),
        };
        layout.Create(elements, vs_shader);
		context.SetVertexLayout(layout);
    }

	context.SetPrimitiveTopology(PrimitiveTopology::TriangleStrip);

    ConstantBuffer constant_buffer;
    {
        struct
        {
            Matrix4x4 world, viewing, projection;
        } data;
        data.world.identity();
        data.viewing.lookAt({ -1, 1, -1 }, { 0, 0, 0 });
        data.viewing.invert();
        data.projection.perspective(deg2rad(60.0f), 4.0f / 3.0f, 0.1f, 128.0f);

        constant_buffer.Create(sizeof(data));
        constant_buffer.Update(data);
    }

    vs_shader.SetConstantBuffer(constant_buffer, 0);

    window.Updated += [&]()
    {
		context.Clear(ColorCode::DarkBlue);

		context.DrawInstanced(4, 4);
		context.Present();
    };

    window.Start();
}
