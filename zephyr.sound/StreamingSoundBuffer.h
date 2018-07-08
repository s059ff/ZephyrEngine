#pragma once

#include "zephyr\string.h"

#include "AbstractSoundBuffer.h"
#include "SoundDevice.h"

struct OggVorbis_File;

namespace zephyr
{
    namespace sound
    {
        /// <summary>
        /// �Đ��Ɠǂݏo���𓯎��ɍs���T�E���h ���\�[�X�ł��B
        /// </summary>
        class StreamingSoundBuffer : public AbstractSoundBuffer
        {
        private:
            using base = AbstractSoundBuffer;

        public:

            /// <summary>
            /// ���̃N���X�̐V�����C���X�^���X�����������܂��B
            /// </summary>
            StreamingSoundBuffer();

            /// <summary>
            /// �C���X�^���X��j�����܂��B
            /// </summary>
            ~StreamingSoundBuffer();

            /// <summary>
            /// �T�E���h�t�@�C�����J���āA�T�E���h���Đ��\�ȏ�Ԃɂ��܂��B
            /// </summary>
            /// <param name="device">�T�E���h�f�o�C�X�B</param>
            /// <param name="path">�T�E���h�t�@�C���̃p�X�B</param>
            void Create(SoundDevice& device, const string& path);

            /// <summary>
            /// �T�E���h�f�[�^��j�����A�T�E���h�t�@�C������܂��B
            /// </summary>
            void Close();

            /// <summary>
            /// �b�P�ʂōĐ��ʒu��ύX���܂��B
            /// </summary>
            /// <param name="time">�Đ��ʒu�B</param>
            void Seek(int time);

            /// <summary>
            /// �T�E���h��擪����Đ����܂��B
            /// </summary>
            void Play();

            /// <summary>
            /// �T�E���h��擪���烋�[�v�Đ����܂��B
            /// </summary>
            void LoopPlay();

            /// <summary>
            /// �T�E���h���~���A�Đ��ʒu��擪�ɖ߂��܂��B
            /// </summary>
            void Stop();

            /// <summary>
            /// �T�E���h���ꎞ��~�������͍ĊJ���܂��B
            /// </summary>
            void Pause();

            /// <summary>
            /// �Đ��󋵂ɉ����āA�T�E���h���������ɓǂݍ��݂܂��B���̃��\�b�h�͖��t���[���Ăяo���K�v������܂��B
            /// </summary>
            void Update();

        private:

            // ogg�t�@�C��
            OggVorbis_File* oggFile;

            // �t�@�C�����J���Ă��邩
            bool isOpened;

            // ���[�v�Đ����s���Ă��邩
            bool isLooping;

            // �������ݐ�u���b�N
            enum class Block { First, Second } next;
        };
    }
}
