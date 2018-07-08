#pragma once

#include "zephyr\property.h"
#include "zephyr\string.h"

#include "AbstractSoundBuffer.h"
#include "SoundDevice.h"

namespace zephyr
{
    namespace sound
    {
        /// <summary>
        /// �S�f�[�^���������Ɋi�[���čĐ����s���T�E���h ���\�[�X�ł��B
        /// </summary>
        class SoundBuffer : public AbstractSoundBuffer
        {
        private:
            using base = AbstractSoundBuffer;

        public:

            /// <summary>
            /// �T�E���h�o�b�t�@��������܂��B
            /// </summary>
            ~SoundBuffer();

            /// <summary>
            /// �T�E���h�t�@�C����ǂݎ���ĐV�����T�E���h�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="device">�T�E���h�f�o�C�X�B</param>
            /// <param name="path">�T�E���h�t�@�C���̃p�X�B</param>
            void Create(SoundDevice& device, const string& path);

            /// <summary>
            /// �ق��̃T�E���h�o�b�t�@�̃f�[�^�����L����T�E���h�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="device">�T�E���h�f�o�C�X�B</param>
            /// <param name="buffer">�f�[�^�̋��L��̃T�E���h�o�b�t�@�B</param>
            void Create(SoundDevice& device, SoundBuffer& buffer);

            /// <summary>
            /// �T�E���h�o�b�t�@��������܂��B
            /// </summary>
            void Release();

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

        public:

            /// <summary>
            /// �T�E���h�̒�����b�P�ʂŎ擾���܂��B
            /// </summary>
            READWRITE_PROPERTY(int, Duration, { return this->duration; }, { this->duration = value; });

        private:

            // ���[�v�Đ������ǂ���
            bool isLooping = false;

            // �T�E���h�̒���
            int duration;
        };
    }
}
