#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include <stdexcept>

#include "zephyr\com_assert.h"
#include "zephyr\runtime_assert.h"

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

			// IDirectInputDevice8インターフェイスの取得（キーボード）
			IDirectInputDevice8A* device = nullptr;
			HRESULT result = input->CreateDevice(GUID_SysKeyboard, &device, NULL);
			if (FAILED(result))
				throw runtime_error("IDirectInputDevice8インターフェイスの取得に失敗しました");
			this.reset(device);

			// データフォーマットの設定（定義済みのキーボード用フォーマットを使用）
			result = this->SetDataFormat(&c_dfDIKeyboard);
			if (FAILED(result))
				throw runtime_error("データフォーマットの設定に失敗しました");

			// 協調モードの設定
			result = this->SetCooperativeLevel(nullptr, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
			if (FAILED(result))
				throw runtime_error("協調モードの設定に失敗しました");
		}

		void Keyboard::Reset(IDirectInputDevice8A* ptr)
		{
			if (this.available())
			{
				this->Unacquire();
				base::reset(ptr);
			}

			this.raw_key_state.fill(0);
			this.raw_key_state_prev.fill(0);
		}

		void Keyboard::Update()
		{
			if (this.IsConnected())
			{
				if (this.available())
				{
					this.raw_key_state_prev = this.raw_key_state;
					auto result = this->GetDeviceState(KeyCount, this.raw_key_state.data());
					if (result == DIERR_NOTACQUIRED || result == DIERR_INPUTLOST)
					{
						this->Acquire();
					}
					for (int i = 0; i < KeyCount; i++)
					{
                        bool now = (this.raw_key_state[i] & 0x80) > 0;
                        bool pre = (this.raw_key_state_prev[i] & 0x80) > 0;
                        this.key_state[i] = [=]()
                        {
                            if (now)
                            {
                                return pre ? this.key_state[i] + 1 : 1;
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

		int Keyboard::GetKeyState(KeyCode code) const
		{
            return this.key_state[static_cast<size_t>(code)];
		}

        bool Keyboard::IsConnected() const
        {
            return true;
        }
	}
}
