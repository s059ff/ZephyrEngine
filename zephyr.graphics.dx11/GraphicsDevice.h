#pragma once

#include "common.h"
#include "SwapChain.h"
#include "GraphicsDevice.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "DepthStencilState.h"
#include "Texture2D.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            enum class PrimitiveTopology;

            class VertexShader;
            class GeometryShader;
            class PixelShader;
            class ConstantBuffer;
            class VertexBuffer;
            class IndexBuffer;
            class VertexLayout;
            class InstanceBuffer;
            class BlendState;
            class RasterizerState;
            class Texture2D;
            class DepthStencilView;
            class DepthStencilState;
            class SamplerState;

            class GraphicsDevice
            {
            public:

                ~GraphicsDevice();

                void UnbindAllResources();

                void Create(const Window& window);

                void Create(const Window& window, bool fullscreen);

                void Clear(const Color& clearColor);

                void Release();

                void SetVertexShader(VertexShader& shader);

                void SetGeometryShader(GeometryShader& shader);

                void SetPixelShader(PixelShader& shader);

                void SetVertexBuffer(VertexBuffer& buffer, int slot);

                void SetVertexBuffers(VertexBuffer buffers[], int bufferCount, int startSlot);

                void SetIndexBuffer(IndexBuffer& buffer);

                void SetInstanceBuffer(InstanceBuffer& buffer, int slot);

                void SetInstanceBuffers(InstanceBuffer buffers[], int bufferCount, int startSlot);

                void SetVertexLayout(VertexLayout& layout);

                void SetPrimitiveTopology(PrimitiveTopology topology);

                void SetBlendState(BlendState& state);

                void SetRasterizerState(RasterizerState& state);

                void SetDepthStencilState(DepthStencilState& state);

                void SetRenderTargetAndDepthStencil(RenderTargetView& view1, DepthStencilView& view2);

                void SetRenderTargetAndDepthStencil(nullptr_t, DepthStencilView& view2);

                void SetRenderTargetAndDepthStencil(RenderTargetView& view1, nullptr_t);

                void ResetRenderTargetAndDepthStencil();

                void SetViewport(int width, int height);

                void Draw(int vertexCount, int startVertexLocation = 0);

                void DrawIndexed(int indexCount, int startIndexLocation = 0, int baseVertexLocation = 0);

                void DrawInstanced(int vertexCountPerInstance, int instanceCount, int startVertexLocation = 0, int startInstanceLocation = 0);

                void DrawIndexedInstanced(int indexCountPerInstance, int instanceCount, int startIndexLocation = 0, int baseVertexLocation = 0, int startInstanceLocation = 0);

                void Present();

            public:

                static GraphicsDevice Instance;

                Interface<ID3D11DeviceContext> DeviceContext;
                Interface<ID3D11Device> Device;

            private:

                GraphicsDevice() {}

            private:

                SwapChain m_swapChain;
                D3D_FEATURE_LEVEL m_featureLevel;
                RenderTargetView m_renderTargetView;
                Texture2D m_depthStencil;
                DepthStencilView m_depthStencilView;
                DepthStencilState m_depthStencilState;
            };
        }
    }
}
