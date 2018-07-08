#pragma once

#include "zephyr\property.h"
#include "zephyr\type.h"

#include "Interface.h"
#include "SoundDevice.h"

struct IDirectSoundBuffer;
struct _DSBUFFERDESC;

namespace zephyr
{
    namespace sound
    {
        /// <summary>
        /// �T�E���h ���\�[�X�̊��N���X�ł��B
        /// </summary>
        class AbstractSoundBuffer : public Interface<IDirectSoundBuffer>
        {
        public:

            /// <summary>
            /// �p�������Z�b�g���܂��B
            /// </summary>
            void ResetPan();

            /// <summary>
            /// �T���v�����O���g�������Z�b�g���܂��B
            /// </summary>
            void ResetFrequency();

            /// <summary>
            /// �{�����[�������Z�b�g���܂��B
            /// </summary>
            void ResetVolume();

            /// <summary>
            /// �T�E���h�����Đ��������ׂ܂��B
            /// </summary>
            READONLY_PROPERTY(bool, IsPlaying, const;);

            /// <summary>
            /// �T�E���h����~�������ׂ܂��B
            /// </summary>
            READONLY_PROPERTY(bool, IsStopped, const;);

            /// <summary>
            /// �T���v�����O���g���� Hz �P�ʂŎ擾�܂��͐ݒ肵�܂��B
            /// </summary>
            READWRITE_PROPERTY(unsigned long, Frequency, const;, ;);

            /// <summary>
            /// ���ʂ� 0 �` 1 �͈̔͂Ŏ擾�܂��͐ݒ肵�܂��B 0 �̂Ƃ��ŏ��A 1 �̂Ƃ��ő��\���܂��B
            /// </summary>
            READWRITE_PROPERTY(double, Volume, const; , ;);

            /// <summary>
            /// �p���� -1 �` +1 �͈̔͂Ŏ擾�܂��͐ݒ肵�܂��B -1 �̂Ƃ������̃X�s�[�J�[����̂݉�����A +1 �̂Ƃ��E���̃X�s�[�J�[����̂݉�����܂��B
            /// </summary>
            READWRITE_PROPERTY(double, Pan, const;, ;);

            /// <summary>
            /// �����̃T���v�����O���g�����擾���܂��B
            /// </summary>
            READONLY_PROPERTY(unsigned long, OriginalFrequency, const{ return this->originalFrequency; });

            // ��̃T�E���h�o�b�t�@�𐶐�����
            void Create(SoundDevice& device, _DSBUFFERDESC desc);

            // �T�E���h�o�b�t�@�𐶐�����
            void Create(SoundDevice& device, _DSBUFFERDESC desc, const byte* data);

            // �ʂ̃T�E���h�o�b�t�@�����L����
            void Create(SoundDevice& device, AbstractSoundBuffer& buffer);

            // �o�b�t�@�T�C�Y
            READONLY_PROPERTY(int, BufferSize, { return this->bufferSize; });

        private:

            // �����̎��g��
            unsigned long originalFrequency;

            // �o�b�t�@�T�C�Y
            int bufferSize;
        };
    }
}
