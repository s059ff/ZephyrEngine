#define DIRECTINPUT_VERSION 0x0800

#define _USE_MATH_DEFINES

#include <cmath>

#include <dinput.h>

#include "zephyr\com_assert.h"
#include "zephyr\runtime_assert.h"

#include "ButtonState.h"
#include "JoyStick.h"

#define this (*this)

#define DEGREE2RADIAN(deg) (deg) / 180.0 * M_PI

using namespace std;

using base = zephyr::input::Interface<IDirectInputDevice8A>;

namespace zephyr
{
    namespace input
    {
        namespace
        {
            // 軸の範囲
            enum { AxisRangle = 262144 };

            // 三角関数の閾値(1 / √2)
            const double AngleThreshold = 0.707107 - 0.1;

            // DirectInput8インターフェイス
            IDirectInput8A* g_pDInput;

            // DirectInputDevice8のインターフェース
            IDirectInputDevice8A* g_pDInputDevice;

            // 
            BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, void*)
            {
                // ジョイスティックへのインターフェイスを取得する
                if (FAILED(g_pDInput->CreateDevice(pdidInstance->guidInstance,&g_pDInputDevice, NULL)))
                {
                    return DIENUM_CONTINUE;
                }

                // ジョイスティックの能力を調べる
                DIDEVCAPS diDevCaps;
                diDevCaps.dwSize = sizeof(DIDEVCAPS);

                if (FAILED(g_pDInputDevice->GetCapabilities(&diDevCaps)))
                {
                    g_pDInputDevice->Release();
                    return DIENUM_CONTINUE;
                }
                return DIENUM_STOP;
            }

            //
            BOOL CALLBACK SetAxisModeCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, void*)
            {
                // 軸の値の範囲を設定
                DIPROPRANGE diprg;
                ZeroMemory(&diprg, sizeof(diprg));
                diprg.diph.dwSize = sizeof(diprg);
                diprg.diph.dwHeaderSize = sizeof(diprg.diph);
                diprg.diph.dwObj = lpddoi->dwType;
                diprg.diph.dwHow = DIPH_BYID;
                diprg.lMin = -AxisRangle;
                diprg.lMax = AxisRangle;
                return FAILED(g_pDInputDevice->SetProperty(DIPROP_RANGE,&diprg.diph)) ? DIENUM_STOP : DIENUM_CONTINUE;
            }

            // デッドゾーンを考慮したアナログスティックの値を取得する
            double getFormatedAxisValue(unsigned long _value, double deadZone)
            {
                double value = (double)(int)_value / (double)AxisRangle;
                if (abs(value) > deadZone)
                {
                    if (value > 0)
                        return 1.0 / (1.0 - deadZone) * (value - deadZone);
                    else
                        return 1.0 / (1.0 - deadZone) * (value + deadZone);
                }
                else
                {
                    return 0;
                }
            }
        }

        JoyStick::~JoyStick()
        {
            this.reset();
        }

        void JoyStick::Create()
        {
            com_ptr<IDirectInput8A> input;
            com_assert(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL));

            g_pDInput = input.get();

            // IDirectInputDevice8インターフェイスの取得（ジョイスティック）
            HRESULT result = g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
            if (FAILED(result) || g_pDInputDevice == nullptr)
                throw runtime_error("IDirectInputDevice8インターフェイスの取得に失敗しました。");
            this.reset(g_pDInputDevice);

            // データフォーマットの設定（定義済みのジョイスティック用フォーマットを使用）
            result = this->SetDataFormat(&c_dfDIJoystick2);
            if (FAILED(result))
                throw runtime_error("データフォーマットの設定に失敗しました。");

            // 協調モードの設定
            result = this->SetCooperativeLevel(nullptr, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
            if (FAILED(result))
                throw runtime_error("協調モードの設定に失敗しました。");

            // 各軸のモードを設定する
            result = this->EnumObjects(SetAxisModeCallback, NULL, DIDFT_AXIS);
            if (FAILED(result))
                throw runtime_error("軸モードの設定に失敗しました。");

            // (グローバル変数を使用不可にする)
            g_pDInput = nullptr;
            g_pDInputDevice = nullptr;

            this.DeadZone = 0.125;
        }

        void JoyStick::Reset(IDirectInputDevice8A* ptr)
        {
            if (this.available())
            {
                this->Unacquire();
                base::reset(ptr);
            }

            this.axisX = this.axisY = this.subAxisX = this.subAxisY = 0;
            this.povDown = this.povLeft = this.povRight = this.povUp = false;
            this.prevPovDown = this.prevPovLeft = this.prevPovRight = this.prevPovUp = false;
            this.buttonState.fill(0);
            this.prevButtonState.fill(0);
        }

        void JoyStick::Update()
        {
            if (this.IsConnected)
            {
                if (this.available())
                {
                    // 前回のデータを上書きする
                    this.prevButtonState = this.buttonState;
                    this.prevPovLeft = this.povLeft;
                    this.prevPovRight = this.povRight;
                    this.prevPovUp = this.povUp;
                    this.prevPovDown = this.povDown;

                    // データを更新する
                    DIJOYSTATE2 state;
                    auto result = this->GetDeviceState(sizeof(DIJOYSTATE2),&state);
                    if (result == DIERR_NOTACQUIRED || result == DIERR_INPUTLOST)
                    {
                        this->Acquire();
                        return;
                    }
                    for (int i = 0; i < ButtonCount; i++)
                    {
                        this.buttonState[i] = state.rgbButtons[i];
                    }

                    this.axisX = getFormatedAxisValue(state.lX, this.DeadZone);
                    this.axisY = getFormatedAxisValue(-state.lY, this.DeadZone);

                    this.subAxisX = getFormatedAxisValue(state.lZ, this.DeadZone);
                    this.subAxisY = getFormatedAxisValue(-state.lRz, this.DeadZone);

                    if (state.rgdwPOV[0] != -1)
                    {
                        double povAngle = DEGREE2RADIAN((double)(state.rgdwPOV[0] / 100));
                        this.povLeft = (sin(povAngle) <= -AngleThreshold);
                        this.povRight = (sin(povAngle) >= AngleThreshold);
                        this.povUp = (cos(povAngle) >= AngleThreshold);
                        this.povDown = (cos(povAngle) <= -AngleThreshold);
                    }
                    else
                    {
                        this.povLeft = false;
                        this.povRight = false;
                        this.povUp = false;
                        this.povDown = false;
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

        ButtonState JoyStick::GetButtonState(int id)
        {
            bool now = (this.buttonState[id]& 0x80) > 0;
            bool pre = (this.prevButtonState[id]& 0x80) > 0;
            return getButtonState(now, pre);
        }

        bool JoyStick::isConnected()
        {
            JOYINFO info;
            return joyGetPos(0,&info) == JOYERR_NOERROR;
        }
    }
}
