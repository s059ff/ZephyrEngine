#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// ウィンドウを表します。
        /// </summary>
        public ref class Window
            : public INativeWrapper<zephyr::graphics::Window>
        {
        public:

            Window()
            {
                Native->Started += s_start;
                Native->Updated += s_update;
                Native->Closed += s_close;
                Native->Destroyed += s_destroy;
            }

            /// <summary>
            /// ウィンドウを作成します。
            /// </summary>
            /// <param name="name">キャプションの名前。</param>
            /// <param name="width">クライアント領域の幅。</param>
            /// <param name="height">クライアント領域の高さ。</param>
            void Create(String^ name, int width, int height)
            {
                Native->Create(to_string(name).c_str(), width, height);
            }

            /// <summary>
            /// ウィンドウを作成します。
            /// </summary>
            /// <param name="name">キャプションの名前。</param>
            /// <param name="width">クライアント領域の幅。</param>
            /// <param name="height">クライアント領域の高さ。</param>
            /// <param name="showFrame">フレームを表示する場合は true, 表示しない場合は false。</param>
            void Create(String^ name, int width, int height, bool showFrame)
            {
                Native->Create(to_string(name).c_str(), width, height, showFrame);
            }

            /// <summary>
            /// メッセージループを開始します。ウィンドウが閉じられるまで、この関数は終了しません。
            /// </summary>
            void Start()
            {
                s_instance = this;

                Native->Start();
            }

            /// <summary>
            /// メッセージループを終了し、ウィンドウを閉じます。
            /// </summary>
            void Close()
            {
                Native->Close();
            }

            /// <summary>
            /// ウィンドウの位置を変更します。
            /// </summary>
            /// <param name="x">ウィンドウの左上端の X 座標。</param>
            /// <param name="y">ウィンドウの左上端の Y 座標。</param>
            void SetPosition(int x, int y)
            {
                Native->SetPosition(x, y);
            }

            /// <summary>
            /// クライアント領域の大きさを変更します。
            /// </summary>
            /// <param name="sx">クライアント領域の幅。</param>
            /// <param name="sy">クライアント領域の高さ。</param>
            void SetSize(int sx, int sy)
            {
                Native->SetSize(sx, sy);
            }

            /// <summary>
            /// フレームを表示します。
            /// </summary>
            void ShowFrame()
            {
                Native->ShowFrame();
            }

            /// <summary>
            /// フレームを隠します。
            /// </summary>
            void HideFrame()
            {
                Native->HideFrame();
            }

            /// <summary>
            /// カーソルを表示します。
            /// </summary>
            void ShowCursor()
            {
                Native->ShowCursor();
            }

            /// <summary>
            /// カーソルを非表示にします。
            /// </summary>
            void HideCursor()
            {
                Native->HideCursor();
            }

            /// <summary>
            /// ウィンドウをアクティブにします。
            /// </summary>
            void Activate()
            {
                Native->Activate();
            }

            /// <summary>
            /// インスタンスハンドルを取得します。
            /// </summary>
            property unsigned long long InstanceHandle
            {
                unsigned long long get()
                {
                    return (unsigned long long)Native->instanceHandle;
                }
            }

            /// <summary>
            /// ウィンドウハンドルを取得します。
            /// </summary>
            property unsigned long long Handle
            {
                unsigned long long get()
                {
                    return (unsigned long long)Native->handle;
                }
            }

            /// <summary>
            /// クライアント領域の幅を取得します。
            /// </summary>
            property int Width
            {
                int get()
                {
                    return Native->width;
                }
            }

            /// <summary>
            /// クライアント領域の高さを取得します。
            /// </summary>
            property int Height
            {
                int get()
                {
                    return Native->height;
                }
            }

        public:

            /// <summary>
            /// メッセージループの開始時に実行されます。
            /// </summary>
            event System::Action^ Started;

            /// <summary>
            /// メッセージループの度に実行されます。
            /// </summary>
            event System::Action^ Updated;

            /// <summary>
            /// メッセージループの終了時に実行されます。
            /// </summary>
            event System::Action^ Closed;

            /// <summary>
            /// ウィンドウハンドルが失効する直前に実行されます。
            /// </summary>
            event System::Action^ Destroyed;

        private:

            static void s_start() { s_instance->Started(); }

            static void s_update() { s_instance->Updated(); }

            static void s_close() { s_instance->Closed(); }

            static void s_destroy() { s_instance->Destroyed(); }

            static Window^ s_instance;
        };
    }
}
