#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>

#include "zephyr.graphics\Font.h"
#include "zephyr.graphics\Window.h"
#include "zephyr.graphics\Color.h"
#include "zephyr.graphics\Material.h"
#include "zephyr.graphics.d3d11\enums.h"
#include "zephyr.graphics.d3d11\BlendState.h"
#include "zephyr.graphics.d3d11\ConstantBuffer.h"
#include "zephyr.graphics.d3d11\DepthStencilState.h"
#include "zephyr.graphics.d3d11\DepthStencilView.h"
#include "zephyr.graphics.d3d11\GraphicsDevice.h"
#include "zephyr.graphics.d3d11\GraphicsDeviceContext.h"
#include "zephyr.graphics.d3d11\GeometryShader.h"
#include "zephyr.graphics.d3d11\IndexBuffer.h"
#include "zephyr.graphics.d3d11\InstanceBuffer.h"
#include "zephyr.graphics.d3d11\PixelShader.h"
#include "zephyr.graphics.d3d11\RasterizerState.h"
#include "zephyr.graphics.d3d11\RenderTargetView.h"
#include "zephyr.graphics.d3d11\SamplerState.h"
#include "zephyr.graphics.d3d11\ShaderResourceView.h"
#include "zephyr.graphics.d3d11\SwapChain.h"
#include "zephyr.graphics.d3d11\Texture2D.h"
#include "zephyr.graphics.d3d11\Texture2DArray.h"
#include "zephyr.graphics.d3d11\VertexBuffer.h"
#include "zephyr.graphics.d3d11\VertexElement.h"
#include "zephyr.graphics.d3d11\VertexLayout.h"
#include "zephyr.graphics.d3d11\VertexShader.h"

#include "ZephyrSharp\common.h"
#include "ZephyrSharp\assert.h"
#include "ZephyrSharp\INativeWrapper.h"
#include "ZephyrSharp\INativeSingletonWrapper.h"
