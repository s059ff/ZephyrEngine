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
        /// グラフィックス リソースの作成を行います。
        /// </summary>
        public ref class GraphicsDevice
            : public INativeSingletonWrapper<zephyr::graphics::dx11::GraphicsDevice>
        {
        public:

            /// <summary>
            /// ウィンドウモードでシステムを初期化します。
            /// </summary>
            /// <param name="window">レンダリングを行うメイン ウィンドウ。</param> 
            void Create(Window^ window)
            {
                Native->Create(*reinterpret_cast<zephyr::graphics::Window*>(window->NativePtr), false);
            }

            /// <summary>
            /// ウィンドウモードでシステムを初期化します。
            /// </summary>
            /// <param name="window">レンダリングを行うメイン ウィンドウ。</param> 
            /// <param name="fullscreen">フルスクリーンにする場合は true 。</param> 
            void Create(Window^ window, bool fullscreen)
            {
                Native->Create(*reinterpret_cast<zephyr::graphics::Window*>(window->NativePtr), fullscreen);
            }

        public:

            /// <summary>
            /// このクラスのシングルトン インスタンスを取得します。
            /// </summary>
            static GraphicsDevice^ Instance = gcnew GraphicsDevice();

        private:

            GraphicsDevice() {}
        };
    }
}
