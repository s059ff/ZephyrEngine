#pragma once

#include <Unknwn.h>

#include "assert.h"

namespace zephyr
{
    /// <summary>
    /// COM �I�u�W�F�N�g���Ǘ�����X�}�[�g�|�C���^�ł��B
    /// </summary>
    template <typename I> class com_ptr
    {
        using interface_t = IUnknown;

    public:

        /// <summary>
        /// �f�t�H���g�̃R���X�g���N�^�ł��B
        /// </summary>
        com_ptr() = default;

        /// <summary>
        /// ���\�[�X���I�u�W�F�N�g�Ɋi�[���܂��B
        /// </summary>
        explicit com_ptr(interface_t* p)
            : p(p)
        {
        }

        /// <summary>
        /// ���\�[�X��������A�I�u�W�F�N�g��j�����܂��B
        /// </summary>
        ~com_ptr()
        {
            this->reset();
        }

        /// <summary>
        /// ���̃I�u�W�F�N�g�̓R�s�[�ł��܂���B
        /// </summary>
        com_ptr(com_ptr&) = delete;

        /// <summary>
        /// ���\�[�X�̏��L�����ړ����܂��B
        /// </summary>
        /// <param name="src">���\�[�X�̏��L���I�u�W�F�N�g�B</param>
        com_ptr(com_ptr&& src)
            : p(src.p)
        {
            src.p = nullptr;
        }

        /// <summary>
        /// ���\�[�X��������܂��B
        /// </summary>
        void operator =(nullptr_t)
        {
            this->reset();
        }

        /// <summary>
        /// ���̃I�u�W�F�N�g�̓R�s�[�ł��܂���B
        /// </summary>
        void operator =(com_ptr&) = delete;

        /// <summary>
        /// ���\�[�X�̏��L�����ړ����܂��B
        /// </summary>
        /// <param name="src">���\�[�X�̏��L���I�u�W�F�N�g�B</param>
        void operator =(com_ptr&& src)
        {
            this->reset(src.p);
            src.p = nullptr;
        }

        /// <summary>
        /// ���\�[�X�ւ̐��̃|�C���^���擾���܂��B
        /// </summary>
        I* const get() const
        {
            return reinterpret_cast<I*>(this->p);
        }

        /// <summary>
        /// ���݂̃��\�[�X��������A�V���Ƀ��\�[�X��ݒ肵�܂��B
        /// </summary>
        /// <param name="p">�V�������L���郊�\�[�X�B</param>
        void reset(interface_t* p)
        {
            if (this->p != p)
            {
                if (this->p != nullptr)
                {
                    this->p->Release();
                    this->p = nullptr;
                }
                this->p = p;
            }
        }

        /// <summary>
        /// ���\�[�X��������܂��B
        /// </summary>
        void reset()
        {
            if (this->p != nullptr)
            {
                this->p->Release();
            }
            this->p = nullptr;
        }

        /// <summary>
        /// ���\�[�X�����L���Ă��邩���ׂ܂��B
        /// </summary>
        bool available() const { return this->p != nullptr; }

        /// <summary>
        /// ���\�[�X�����L���Ă��Ȃ������ׂ܂��B
        /// </summary>
        bool expired() const { return this->p == nullptr; }

        /// <summary>
        /// ���\�[�X����L����|�C���^�̃A�h���X���擾���܂��B
        /// </summary>
        I** operator& ()
        {
            assert(this->p == nullptr);
            return&reinterpret_cast<I*&>(this->p);
        }

        /// <summary>
        /// ���\�[�X�̃��\�b�h���Ăяo���܂��B
        /// </summary>
        I* operator-> () const
        {
            assert(this->available());
            return get();
        }

        /// <summary>
        /// ���\�[�X�ւ̎Q�Ƃ��擾���܂��B
        /// </summary>
        I& operator* () const
        {
            assert(this->p != nullptr);
            return *reinterpret_cast<I*>(this->p);
        }
        
        /// <summary>
        /// ���\�[�X�ւ̐��̃|�C���^���擾���܂��B
        /// </summary>
        __declspec(property(get = get, put = reset)) I* ptr;

    private:

        interface_t* p = nullptr;
    };
}
