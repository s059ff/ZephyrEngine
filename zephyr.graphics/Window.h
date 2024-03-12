#pragma once

#include "zephyr\event.h"

namespace zephyr
{
    namespace graphics
    {
        /// <summary>
        /// ウィンドウを表します。
        /// </summary>
        class Window
        {
        public:

            /// <summary>
            /// ウィンドウを作成します。
            /// </summary>
            /// <param name="name">キャプションの名前。</param>
            /// <param name="width">クライアント領域の幅。</param>
            /// <param name="height">クライアント領域の高さ。</param>
            void Create(const char* name, int width, int height);

            /// <summary>
            /// ウィンドウを作成します。
            /// </summary>
            /// <param name="name">キャプションの名前。</param>
            /// <param name="width">クライアント領域の幅。</param>
            /// <param name="height">クライアント領域の高さ。</param>
            /// <param name="showFrame">フレームを表示する場合は true, 表示しない場合は false。</param>
            void Create(const char* name, int width, int height, bool showFrame);

            /// <summary>
            /// メッセージループを開始します。ウィンドウが閉じられるまで、この関数は終了しません。
            /// </summary>
            void Start();

            /// <summary>
            /// メッセージループを終了し、ウィンドウを閉じます。
            /// </summary>
            void Close();

            /// <summary>
            /// ウィンドウの位置を変更します。
            /// </summary>
            /// <param name="x">ウィンドウの左上端の X 座標。</param>
            /// <param name="y">ウィンドウの左上端の Y 座標。</param>
            void SetPosition(int x, int y);

            /// <summary>
            /// クライアント領域の大きさを変更します。
            /// </summary>
            /// <param name="sx">クライアント領域の幅。</param>
            /// <param name="sy">クライアント領域の高さ。</param>
            void SetSize(int sx, int sy);

            /// <summary>
            /// ウィンドウのアイコンを設定します。
            /// </summary>
            /// <param name="resourceID">アイコンのリソース ID 。</param> 
            void SetIcon(int resourceID);

            /// <summary>
            /// ウィンドウのアイコンを設定します。
            /// </summary>
            /// <param name="resourceID">アイコンのリソース ID 。</param> 
            void SetSmallIcon(int resourceID);

            /// <summary>
            /// ウィンドウのアイコンを設定します。
            /// </summary>
            /// <param name="resourceName">アイコンのリソース名。</param> 
            void SetIcon(const char* resourceName);

            /// <summary>
            /// ウィンドウのアイコンを設定します。
            /// </summary>
            /// <param name="resourceName">アイコンのリソース名。</param> 
            void SetSmallIcon(const char* resourceName);

            /// <summary>
            /// フレームを表示します。
            /// </summary>
            void ShowFrame();

            /// <summary>
            /// フレームを隠します。
            /// </summary>
            void HideFrame();

            /// <summary>
            /// カーソルを表示します。
            /// </summary>
            void ShowCursor();

            /// <summary>
            /// カーソルを非表示にします。
            /// </summary>
            void HideCursor();

            /// <summary>
            /// ウィンドウをアクティブにします。
            /// </summary>
            void Activate();

            __declspec(property(get = get_instnace_handle)) void* instanceHandle;

            __declspec(property(get = get_window_handle)) void* handle;

            __declspec(property(get = get_width)) int width;

            __declspec(property(get = get_height)) int height;

            void* get_instnace_handle() const { return m_hInstance; }

            void* get_window_handle() const { return m_hWindow; }

            int get_width() const { return m_width; }

            int get_height() const { return m_height; }

        public:

            /// <summary>
            /// メッセージループの開始時に実行されます。
            /// </summary>
            event<> Started;

            /// <summary>
            /// メッセージループの度に実行されます。
            /// </summary>
            event<> Updated;

            /// <summary>
            /// メッセージループの終了時に実行されます。
            /// </summary>
            event<> Closed;

            /// <summary>
            /// ウィンドウハンドルが失効する直前に実行されます。
            /// </summary>
            event<> Destroyed;

        private:

            void* m_hWindow;

            void* m_hInstance;

            int m_width, m_height;

            void *m_hIcon, *m_hIconSmall;
        };
    }
}
