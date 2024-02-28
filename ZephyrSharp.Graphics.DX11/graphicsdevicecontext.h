#pragma once

#include "common.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "VertexLayout.h"
#include "BlendState.h"
#include "RatserizerState.h"
#include "DepthStencilState.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// レンダリングを行います。
        /// </summary>
        public ref class GraphicsDeviceContext
            : public INativeSingletonWrapper<zephyr::graphics::dx11::GraphicsDeviceContext>
        {
        public:

            /// <summary>
            /// パイプラインに関連付けられているすべてのリソースをアンバインドします。
            /// </summary>
            void UnbindAllResources()
            {
                Native->UnbindAllResources();
            }

            /// <summary>
            /// バックバッファをクリアします。
            /// </summary>
            /// <param name="color">クリアする色。</param> 
            void Clear(Color color)
            {
                Native->Clear(reinterpret_cast<zephyr::graphics::Color&>(color));
            }

            /// <summary>
            /// バックバッファをクリアします。
            /// </summary>
            /// <param name="color">クリアする色。</param> 
            void Clear(ColorCode color)
            {
                Native->Clear(reinterpret_cast<zephyr::graphics::ColorCode&>(color));
            }

            /// <summary>
            /// レンダリングに使用するバーテックス シェーダを設定します。
            /// </summary>
            /// <param name="shader">バーテックス シェーダ。</param> 
            void SetVertexShader(VertexShader^ shader)
            {
                Native->SetVertexShader(shader->NativeRef);
            }

            /// <summary>
            /// レンダリングに使用するジオメトリ シェーダを設定します。
            /// </summary>
            /// <param name="shader">ジオメトリ シェーダ。</param> 
            void SetGeometryShader(GeometryShader^ shader)
            {
                Native->SetGeometryShader(shader->NativeRef);
            }

            /// <summary>
            /// レンダリングに使用するピクセル シェーダを設定します。
            /// </summary>
            /// <param name="shader">ピクセル シェーダ。</param> 
            void SetPixelShader(PixelShader^ shader)
            {
                Native->SetPixelShader(shader->NativeRef);
            }

            /// <summary>
            /// レンダリングに使用するバーテックス バッファを設定します。
            /// </summary>
            /// <param name="buffer">頂点バッファ。</param> 
            /// <param name="slot">スロット番号。</param> 
            generic <typename V> where V : value class void SetVertexBuffer(VertexBuffer<V>^ buffer, int slot)
            {
                Native->SetVertexBuffer(buffer->NativeRef, slot);
            }

            /// <summary>
            /// レンダリングに使用するインデックス バッファを設定します。
            /// </summary>
            /// <param name="buffer">頂点バッファ。</param> 
            void SetIndexBuffer(IndexBuffer^ buffer)
            {
                Native->SetIndexBuffer(buffer->NativeRef);
            }

            /// <summary>
            /// レンダリングに使用するインスタンス バッファを設定します。
            /// </summary>
            /// <param name="buffer">インスタンス バッファ。</param> 
            /// <param name="slot">スロット番号。</param> 
            generic <typename I> where I : value class void SetInstanceBuffer(InstanceBuffer<I>^ buffer, int slot)
            {
                Native->SetInstanceBuffer(buffer->NativeRef, slot);
            }

            /// <summary>
            /// 頂点バッファのレイアウトを設定します。
            /// </summary>
            /// <param name="layout">頂点レイアウト。</param> 
            void SetVertexLayout(VertexLayout^ layout)
            {
                Native->SetVertexLayout(layout->NativeRef);
            }

            /// <summary>
            /// 頂点バッファに格納されている頂点の順番の規則性を設定します。
            /// </summary>
            /// <param name="topology">頂点データ トポロジー。</param> 
            void SetPrimitiveTopology(PrimitiveTopology topology)
            {
                Native->SetPrimitiveTopology((zephyr::graphics::dx11::PrimitiveTopology)topology);
            }

            /// <summary>
            /// ブレンディング ステートをレンダリング パイプラインに適用します。
            /// </summary>
            /// <param name="state">ブレンディング ステート。</param> 
            void SetBlendState(BlendState^ state)
            {
                Native->SetBlendState(state->NativeRef);
            }

            /// <summary>
            /// ラスタライザ ステートをレンダリング パイプラインに適用します。
            /// </summary>
            /// <param name="state">ラスタライザ ステート。</param> 
            void SetRasterizerState(RasterizerState^ state)
            {
                Native->SetRasterizerState(state->NativeRef);
            }

            /// <summary>
            /// 深度・ステンシル ステートをレンダリング パイプラインに適用します。
            /// </summary>
            /// <param name="state">深度・ステンシル ステート。</param> 
            void SetDepthStencilState(DepthStencilState^ state)
            {
                Native->SetDepthStencilState(state->NativeRef);
            }

            /// <summary>
            /// レンダリングターゲットと深度バッファを設定します。
            /// </summary>
            /// <param name="target">レンダリングターゲット テクスチャ。</param> 
            /// <param name="depth">深度バッファ テクスチャ。</param> 
            void SetRenderTargetAndDepthStencil(Texture2D^ target, Texture2D^ depth)
            {
                if ((target != nullptr) && (depth != nullptr))
                {
                    Native->SetRenderTargetAndDepthStencil(target->TargetView->NativeRef, depth->DepthView->NativeRef);
                }
                else
                {
                    if (target != nullptr)
                    {
                        Native->SetRenderTargetAndDepthStencil(target->TargetView->NativeRef, nullptr);
                    }
                    else if (depth != nullptr)
                    {
                        Native->SetRenderTargetAndDepthStencil(nullptr, depth->DepthView->NativeRef);
                    }
                }
            }

            /// <summary>
            /// レンダリングターゲットと深度バッファをデフォルトに設定します。
            /// </summary>
            void ResetRenderTargetAndDepthStencil()
            {
                Native->ResetRenderTargetAndDepthStencil();
            }

            /// <summary>
            /// ビューポート変換行列を設定します。
            /// </summary>
            /// <param name="width">ビューポート幅。</param> 
            /// <param name="height">ビューポート高さ。</param> 
            void SetViewport(int width, int height)
            {
                Native->SetViewport(width, height);
            }

            /// <summary>
            /// インデックスバッファを使用せずに、レンダリングを実行します。
            /// </summary>
            /// <param name="vertexCount">レンダリングに使用される頂点の数。</param> 
            void Draw(int vertexCount)
            {
                Native->Draw(vertexCount);
            }

            /// <summary>
            /// インデックスバッファを使用せずに、レンダリングを実行します。
            /// </summary>
            /// <param name="vertexCount">レンダリングに使用される頂点の数。</param> 
            /// <param name="startVertexLocation">レンダリングに使用される頂点の開始位置。</param> 
            void Draw(int vertexCount, int startVertexLocation)
            {
                Native->Draw(vertexCount, startVertexLocation);
            }

            /// <summary>
            /// インデックスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="indexCount">レンダリングに使用されるインデックスの数。</param> 
            void DrawIndexed(int indexCount)
            {
                Native->DrawIndexed(indexCount);
            }

            /// <summary>
            /// インデックスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="indexCount">レンダリングに使用されるインデックスの数。</param> 
            /// <param name="startIndexLocation">レンダリングに使用されるインデックスの開始位置。</param> 
            void DrawIndexed(int indexCount, int startIndexLocation)
            {
                Native->DrawIndexed(indexCount, startIndexLocation);
            }

            /// <summary>
            /// インデックスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="indexCount">レンダリングに使用されるインデックスの数。</param> 
            /// <param name="startIndexLocation">レンダリングに使用されるインデックスの開始位置。</param> 
            /// <param name="baseVertexLocation">インデックスの値と、実際の頂点データ番号とのオフセット。</param> 
            void DrawIndexed(int indexCount, int startIndexLocation, int baseVertexLocation)
            {
                Native->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
            }

            /// <summary>
            /// インスタンスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="vertexCountPerInstance">レンダリングに使用される 1 インスタンスあたりの頂点の数。</param> 
            /// <param name="instanceCount">レンダリングに使用されるインスタンスの数。</param> 
            void DrawInstanced(int vertexCountPerInstance, int instanceCount)
            {
                Native->DrawInstanced(vertexCountPerInstance, instanceCount);
            }

            /// <summary>
            /// インスタンスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="vertexCountPerInstance">レンダリングに使用される 1 インスタンスあたりの頂点の数。</param> 
            /// <param name="instanceCount">レンダリングに使用されるインスタンスの数。</param> 
            /// <param name="startVertexLocation">レンダリングに使用される頂点の開始位置。</param> 
            void DrawInstanced(int vertexCountPerInstance, int instanceCount, int startVertexLocation)
            {
                Native->DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation);
            }

            /// <summary>
            /// インスタンスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="vertexCountPerInstance">レンダリングに使用される 1 インスタンスあたりの頂点の数。</param> 
            /// <param name="instanceCount">レンダリングに使用されるインスタンスの数。</param> 
            /// <param name="startVertexLocation">レンダリングに使用される頂点の開始位置。</param> 
            /// <param name="startInstanceLocation">レンダリングに使用されるインスタンスの開始位置。</param> 
            void DrawInstanced(int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation)
            {
                Native->DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation);
            }

            /// <summary>
            /// インデックスバッファとインスタンスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="indexCountPerInstance">レンダリングに使用される 1 インスタンスあたりのインデックスの数。</param> 
            /// <param name="instanceCount">レンダリングに使用されるインスタンスの数。</param> 
            void DrawIndexedInstanced(int indexCountPerInstance, int instanceCount)
            {
                Native->DrawIndexedInstanced(indexCountPerInstance, instanceCount);
            }

            /// <summary>
            /// インデックスバッファとインスタンスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="indexCountPerInstance">レンダリングに使用される 1 インスタンスあたりのインデックスの数。</param> 
            /// <param name="instanceCount">レンダリングに使用されるインスタンスの数。</param> 
            /// <param name="startIndexLocation">レンダリングに使用されるインデックスの開始位置。</param> 
            void DrawIndexedInstanced(int indexCountPerInstance, int instanceCount, int startIndexLocation)
            {
                Native->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation);
            }

            /// <summary>
            /// インデックスバッファとインスタンスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="indexCountPerInstance">レンダリングに使用される 1 インスタンスあたりのインデックスの数。</param> 
            /// <param name="instanceCount">レンダリングに使用されるインスタンスの数。</param> 
            /// <param name="startIndexLocation">レンダリングに使用されるインデックスの開始位置。</param> 
            /// <param name="baseVertexLocation">インデックスの値と、実際の頂点データ番号とのオフセット。</param> 
            void DrawIndexedInstanced(int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation)
            {
                Native->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation);
            }

            /// <summary>
            /// インデックスバッファとインスタンスバッファを使用して、レンダリングを実行します。
            /// </summary>
            /// <param name="indexCountPerInstance">レンダリングに使用される 1 インスタンスあたりのインデックスの数。</param> 
            /// <param name="instanceCount">レンダリングに使用されるインスタンスの数。</param> 
            /// <param name="startIndexLocation">レンダリングに使用されるインデックスの開始位置。</param> 
            /// <param name="baseVertexLocation">インデックスの値と、実際の頂点データ番号とのオフセット。</param> 
            /// <param name="startInstanceLocation">レンダリングに使用されるインスタンスの開始位置。</param> 
            void DrawIndexedInstanced(int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation)
            {
                Native->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
            }

            /// <summary>
            /// スワップチェインを交換して、バッファを画面に表示します。
            /// </summary>
            void Present()
            {
                Native->Present();
            }

        public:

            /// <summary>
            /// このクラスのシングルトン インスタンスを取得します。
            /// </summary>
            static GraphicsDeviceContext^ Instance = gcnew GraphicsDeviceContext();

        private:

            GraphicsDeviceContext() {}
        };
    }
}
