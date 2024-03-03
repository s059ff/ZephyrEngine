#define DIRECTINPUT_VERSION 0x0800

#include <stdexcept>

#include <dinput.h>

#include "zephyr\com_assert.h"
#include "zephyr\runtime_assert.h"

#include "ButtonState.h"
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

            // IDirectInputDevice8�C���^�[�t�F�C�X�̎擾�i�}�E�X�j
            HRESULT result = input->CreateDevice(GUID_SysMouse, &this, NULL);
            if (FAILED(result))
                throw runtime_error("IDirectInputDevice8�C���^�[�t�F�C�X�̎擾�Ɏ��s���܂���");

            // �f�[�^�t�H�[�}�b�g�̐ݒ�i��`�ς݂̃}�E�X�p�t�H�[�}�b�g���g�p�j
            result = this->SetDataFormat(&c_dfDIMouse2);
            if (FAILED(result))
                throw runtime_error("�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���");

            // �������[�h�̐ݒ�
            result = this->SetCooperativeLevel(nullptr, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
            if (FAILED(result))
                throw runtime_error("�������[�h�̐ݒ�Ɏ��s���܂���");

            // �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
            DIPROPDWORD diprop;
            diprop.diph.dwSize = sizeof(diprop);
            diprop.diph.dwHeaderSize = sizeof(diprop.diph);
            diprop.diph.dwObj = 0;
            diprop.diph.dwHow = DIPH_DEVICE;
            diprop.dwData = DIPROPAXISMODE_REL;
            result = this->SetProperty(DIPROP_AXISMODE, &diprop.diph);
            if (FAILED(result))
                throw runtime_error("�����[�h�̐ݒ�Ɏ��s���܂���");
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
            this.left = this.right = this.center = this.prevLeft = this.prevRight = this.prevCenter = false;
        }

        void Mouse::Update()
        {
            if (this.IsConnected)
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

                    this.prevLeft = this.left;
                    this.prevRight = this.right;
                    this.prevCenter = this.center;
                    this.left = (dims.rgbButtons[0] & 0x80) > 0;
                    this.right = (dims.rgbButtons[1] & 0x80) > 0;
                    this.center = (dims.rgbButtons[2] & 0x80) > 0;
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

        ButtonState Mouse::_get_Left()
        {
            return getButtonState(this.left, this.prevLeft);
        }

        ButtonState Mouse::_get_Right()
        {
            return getButtonState(this.right, this.prevRight);
        }

        ButtonState Mouse::_get_Center()
        {
            return getButtonState(this.center, this.prevCenter);
        }

        bool Mouse::isConnected() const
        {
            return GetSystemMetrics(SM_MOUSEPRESENT) != 0;
        }
    }
}
