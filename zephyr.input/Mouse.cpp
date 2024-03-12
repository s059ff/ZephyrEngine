#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include <stdexcept>

#include "zephyr\com_assert.h"
#include "zephyr\runtime_assert.h"

#include "Mouse.h"

#define this (*this)

using namespace std;

using base = zephyr::input::Interface < IDirectInputDevice8A >;

namespace zephyr
{
    namespace input
    {
        Mouse::~Mouse()
        {
            this.Reset();
        }

        void Mouse::Create()
        {
            com_ptr<IDirectInput8A> input;
            com_assert(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL));

            // IDirectInputDevice8インターフェイスの取得（マウス）
            HRESULT result = input->CreateDevice(GUID_SysMouse, &this, NULL);
            if (FAILED(result))
                throw runtime_error("IDirectInputDevice8インターフェイスの取得に失敗しました");

            // データフォーマットの設定（定義済みのマウス用フォーマットを使用）
            result = this->SetDataFormat(&c_dfDIMouse2);
            if (FAILED(result))
                throw runtime_error("データフォーマットの設定に失敗しました");

            // 協調モードの設定
            result = this->SetCooperativeLevel(nullptr, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
            if (FAILED(result))
                throw runtime_error("協調モードの設定に失敗しました");

            // 軸モードを設定（相対値モードに設定）
            DIPROPDWORD diprop;
            diprop.diph.dwSize = sizeof(diprop);
            diprop.diph.dwHeaderSize = sizeof(diprop.diph);
            diprop.diph.dwObj = 0;
            diprop.diph.dwHow = DIPH_DEVICE;
            diprop.dwData = DIPROPAXISMODE_REL;
            result = this->SetProperty(DIPROP_AXISMODE, &diprop.diph);
            if (FAILED(result))
                throw runtime_error("軸モードの設定に失敗しました");
        }

        void Mouse::Reset(IDirectInputDevice8A* ptr)
        {
            if (this.available())
            {
                this->Unacquire();
                base::reset(ptr);
            }

            this.mouseX = this.mouseY = 0;
            this.moveX = this.moveY = this.moveZ = 0;
            this.raw_button_state.fill(0);
            this.raw_button_state_prev.fill(0);
        }

        void Mouse::Update()
        {
            if (this.IsConnected())
            {
                if (this.available())
                {
                    DIMOUSESTATE2 dims;
                    auto result = this->GetDeviceState(sizeof(DIMOUSESTATE2), &dims);
                    if (result == DIERR_NOTACQUIRED || result == DIERR_INPUTLOST)
                    {
                        this->Acquire();
                        return;
                    }

                    POINT positionScreen;
                    GetCursorPos(&positionScreen);

                    HWND hWnd = GetActiveWindow();
                    POINT positionClient = positionScreen;
                    ScreenToClient(hWnd, &positionClient);

                    this.mouseX = positionClient.x;
                    this.mouseY = positionClient.y;
                    this.moveX = dims.lX;
                    this.moveY = dims.lY;
                    this.moveZ = dims.lZ;

                    this.raw_button_state_prev = this.raw_button_state;
                    memcpy(this.raw_button_state.data(), dims.rgbButtons, sizeof(this.raw_button_state));

                    for (int i = 0; i < ButtonCount; i++)
                    {
                        bool now = (this.raw_button_state[i] & 0x80) > 0;
                        bool pre = (this.raw_button_state_prev[i] & 0x80) > 0;
                        this.button_state[i] = [=]() {
                            if (now)
                            {
                                return pre ? this.button_state[i] + 1 : 1;
                            }
                            else
                            {
                                return pre ? -1 : 0;
                            }
                        }();
                    }
                }
                else
                {
                    this.Create();
                }
            }
            else
            {
                this.Reset();
            }
        }

        bool Mouse::IsConnected() const
        {
            return GetSystemMetrics(SM_MOUSEPRESENT) != 0;
        }
    }
}
