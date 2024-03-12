#pragma once

#include "common.h"
#include "SwapChain.h"
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
            class VertexShader;
            class GeometryShader;
            class PixelShader;
            class VertexBuffer;
            class IndexBuffer;
            class InstanceBuffer;
            class VertexLayout;
            class BlendState;
            class RasterizerState;

            class GraphicsDeviceContext : public Interface<ID3D11DeviceContext>
            {
            public:

                void Create(IDXGISwapChain* swapChain, ID3D11DeviceContext* deviceContext, const Window& window, bool fullScreen);

                void Release();

                void Clear(const Color& clearColor);

                void UnbindAllResources();

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

                void Present(int syncInterval = 1);

            public:

                static GraphicsDeviceContext Instance;

            private:

                SwapChain m_swapChain;
                RenderTargetView m_renderTargetView;
                DepthStencilView m_depthStencilView;
                Texture2D m_depthStencil;
                DepthStencilState m_depthStencilState;
            };
        }
    }
}
