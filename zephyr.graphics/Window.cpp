#include <Windows.h>

#include <algorithm>
#include <string>

#include "zephyr\runtime_assert.h"
#include "Window.h"

#define this (*this)

using namespace std;

using action = function<void()>;

namespace zephyr
{
    namespace graphics
    {
        static Window* s_window = nullptr;

        // ウィンドウプロシージャ
        static LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            switch (msg)
            {
            //case WM_SETCURSOR:
            //    break;
            case WM_CLOSE:
                PostQuitMessage(0);
                break;
            case WM_DESTROY:
                s_window->Destroyed.call();
                break;
            default:
                return DefWindowProc(hWnd, msg, wParam, lParam);
            }
            return 0;
        };

        void Window::Create(const char* name, int width, int height)
        {
            m_hInstance = GetModuleHandle(0);

            // ウィンドウクラスの定義
            string className = "zephyr.graphics.Window ";
            className += to_string((uint64_t)&this);

            // ウィンドウクラスの登録
            WNDCLASSEX wcex = {
                sizeof(WNDCLASSEX), NULL, WndProc, 0, 0, (HINSTANCE)m_hInstance, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW), NULL, NULL, className.c_str(), NULL
            };
            if (RegisterClassEx(&wcex) == 0)
                exit(EXIT_FAILURE);

            // ウィンドウの作成
            m_hWindow = CreateWindow(className.c_str(), name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, (HINSTANCE)m_hInstance, NULL);

            // WM_PAINTが呼ばれないようにする
            ValidateRect((HWND)m_hWindow, 0);

            // サイズを修正する
            this.SetSize(width, height);

            // ウィンドウを表示する
            ShowWindow((HWND)m_hWindow, SW_SHOW);

            // 既定のアイコンを設定する
            m_hIcon = LoadImage(GetModuleHandle(NULL), IDI_APPLICATION, IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_DEFAULTCOLOR);
            m_hIconSmall = LoadImage(GetModuleHandle(NULL), IDI_APPLICATION, IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_DEFAULTCOLOR);
            SendMessage((HWND)m_hWindow, WM_SETICON, ICON_BIG, (LPARAM)m_hIcon);
            SendMessage((HWND)m_hWindow, WM_SETICON, ICON_SMALL, (LPARAM)m_hIconSmall);

            // 
            s_window = &this;
        }

        void Window::Create(const char* name, int width, int height, bool showFrame)
        {
            this.Create(name, width, height);
            if (!showFrame)
            {
                this.HideFrame();
            }
        }

        void Window::Start()
        {
            this.Activate();

            for_each(this.Started.begin(), this.Started.end(), [](action& action) { action(); });

            MSG msg;
            WINDOWPLACEMENT wndpl;
            ZeroMemory(&wndpl, sizeof(wndpl));
            wndpl.length = sizeof(wndpl);

            while (true)
            {
                if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    if (msg.message == WM_QUIT)
                        break;
                    else
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }
                else
                {
                    GetWindowPlacement((HWND)m_hWindow,&wndpl);
                    if ((wndpl.showCmd != SW_HIDE)&& (wndpl.showCmd != SW_MINIMIZE)&& (wndpl.showCmd != SW_SHOWMINIMIZED)&& (wndpl.showCmd != SW_SHOWMINNOACTIVE)&& (GetActiveWindow() == m_hWindow))
                    {
                        for_each(this.Updated.begin(), this.Updated.end(), [](action& action) { action(); });
                    }
                    else
                    {
                        Sleep(1);
                    }
                }
            }

            for_each(this.Closed.begin(), this.Closed.end(), [](action& action) { action(); });
        }

        void Window::Close()
        {
            for_each(this.Closed.begin(), this.Closed.end(), [](action& action) { action(); });
            PostQuitMessage(0);
            CloseWindow((HWND)m_hWindow);
        }

        void Window::SetPosition(int x, int y)
        {
            SetWindowPos((HWND)m_hWindow, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }

        void Window::SetSize(int width, int height)
        {
            m_width = width;
            m_height = height;
            RECT rect = { 0, 0, width, height };
            AdjustWindowRect(&rect, GetWindowLong((HWND)m_hWindow, GWL_STYLE), false);
            SetWindowPos((HWND)m_hWindow, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
        }

        void Window::SetIcon(int resourceID)
        {
            DestroyIcon((HICON)m_hIcon);
            m_hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(resourceID), IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_DEFAULTCOLOR);
            runtime_assert(m_hIcon != nullptr);
            SendMessage((HWND)m_hWindow, WM_SETICON, ICON_BIG, (LPARAM)m_hIcon);
        }

        void Window::SetSmallIcon(int resourceID)
        {
            DestroyIcon((HICON)m_hIconSmall);
            m_hIconSmall = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(resourceID), IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_DEFAULTCOLOR);
            runtime_assert(m_hIconSmall != nullptr);
            SendMessage((HWND)m_hWindow, WM_SETICON, ICON_SMALL, (LPARAM)m_hIconSmall);
        }

        void Window::SetIcon(const char* resourceName)
        {
            DestroyIcon((HICON)m_hIcon);
            m_hIcon = (HICON)LoadImage(GetModuleHandle(NULL), resourceName, IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_DEFAULTCOLOR);
            runtime_assert(m_hIcon != nullptr);
            SendMessage((HWND)m_hWindow, WM_SETICON, ICON_BIG, (LPARAM)m_hIcon);
        }

        void Window::SetSmallIcon(const char* resourceName)
        {
            DestroyIcon((HICON)m_hIconSmall);
            m_hIconSmall = (HICON)LoadImage(GetModuleHandle(NULL), resourceName, IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_DEFAULTCOLOR);
            runtime_assert(m_hIconSmall != nullptr);
            SendMessage((HWND)m_hWindow, WM_SETICON, ICON_SMALL, (LPARAM)m_hIconSmall);
        }

        void Window::ShowFrame()
        {
            auto style = GetWindowLong((HWND)m_hWindow, GWL_STYLE) | WS_CAPTION | WS_THICKFRAME;
            SetWindowLong((HWND)m_hWindow, GWL_STYLE, style);
            this.SetSize(m_width, m_height);
        }

        void Window::HideFrame()
        {
            auto style = GetWindowLong((HWND)m_hWindow, GWL_STYLE)& ~WS_CAPTION& ~WS_THICKFRAME;
            SetWindowLong((HWND)m_hWindow, GWL_STYLE, style);
            this.SetSize(m_width, m_height);
        }

        void Window::ShowCursor()
        {
            ::ShowCursor(TRUE);
        }

        void Window::HideCursor()
        {
            ::ShowCursor(FALSE);
        }

        void Window::Activate()
        {
            SetActiveWindow((HWND)m_hWindow);
        }
    }
}
