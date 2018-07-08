#pragma once

#include "zephyr\assert.h"
#include "zephyr\buffer.h"
#include "zephyr\property.h"
#include "zephyr\runtime_assert.h"
#include "zephyr\string.h"
#include "zephyr\type.h"
#include "zephyr.graphics\Interface.h"

struct ID3D10Blob;
struct ID3D11BlendState;
struct ID3D11Buffer;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11GeometryShader;
struct ID3D11InputLayout;
struct ID3D11PixelShader;
struct ID3D11RenderTargetView;
struct ID3D11RasterizerState;
struct ID3D11ShaderResourceView;
struct ID3D11Texture2D;
struct ID3D11Texture2D;
struct ID3D11VertexShader;
struct ID3D11DepthStencilView;
struct IDXGISwapChain;
struct ID3D11DepthStencilState;
struct ID3D11SamplerState;

enum D3D_FEATURE_LEVEL;

namespace zephyr
{
    class buffer;

    namespace graphics
    {
        class Font;
        class Window;
        struct Color;
    }
}
