#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include "zephyr\com_assert.h"
#include "zephyr\runtime_assert.h"

#include "ButtonState.h"
#include "KeyCode.h"
#include "Keyboard.h"

#define this (*this)

using namespace std;

using base = zephyr::input::Interface < IDirectInputDevice8A >;

namespace zephyr
{
	namespace input
	{
		Keyboard::~Keyboard()
		{
			this.reset();
		}

		void Keyboard::Create()
		{
			com_ptr<IDirectInput8A> input;
			com_assert(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL));

			// IDirectInputDevice8�C���^�[�t�F�C�X�̎擾�i�L�[�{�[�h�j
			IDirectInputDevice8A* device = nullptr;
			HRESULT result = input->CreateDevice(GUID_SysKeyboard, &device, NULL);
			if (FAILED(result))
				throw runtime_error("IDirectInputDevice8�C���^�[�t�F�C�X�̎擾�Ɏ��s���܂���");
			this.reset(device);

			// �f�[�^�t�H�[�}�b�g�̐ݒ�i��`�ς݂̃L�[�{�[�h�p�t�H�[�}�b�g���g�p�j
			result = this->SetDataFormat(&c_dfDIKeyboard);
			if (FAILED(result))
				throw runtime_error("�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���");

			// �������[�h�̐ݒ�
			result = this->SetCooperativeLevel(nullptr, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
			if (FAILED(result))
				throw runtime_error("�������[�h�̐ݒ�Ɏ��s���܂���");
		}

		void Keyboard::Reset(IDirectInputDevice8A* ptr)
		{
			if (this.available())
			{
				this->Unacquire();
				base::reset(ptr);
			}

			this.keyState.fill(0);
			this.prevKeyState.fill(0);
			this.pressTimeLength.fill(0);
		}

		void Keyboard::Update()
		{
			if (this.IsConnected)
			{
				if (this.available())
				{
					this.prevKeyState = this.keyState;
					auto result = this->GetDeviceState(KeyCount, this.keyState.data());
					if (result == DIERR_NOTACQUIRED || result == DIERR_INPUTLOST)
					{
						this->Acquire();
					}
					for (int i = 0; i < KeyCount; i++)
					{
						// ���������ė�������Ԃ����m�ł���悤�ɂ��� (T < pressTime && NowReleased)
						if (0 < (this.prevKeyState[i] & 0x80))
							this.pressTimeLength[i]++;
						else
							this.pressTimeLength[i] = 0;
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

		ButtonState Keyboard::GetKeyState(KeyCode key) const
		{
			int id = (int)key;
			bool now = (this.keyState[id] & 0x80) > 0;
			bool pre = (this.prevKeyState[id] & 0x80) > 0;
			return getButtonState(now, pre);
		}

		int Keyboard::GetPressTimeLength(KeyCode key) const
		{
			int id = (int)key;
			return this.pressTimeLength[id];
		}
	}
}
