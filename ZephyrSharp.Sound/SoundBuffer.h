#pragma once

#include "common.h"
#include "SoundDevice.h"

namespace ZephyrSharp
{
    namespace Sound
    {
        /// <summary>
        /// �S�f�[�^���������Ɋi�[���čĐ����s���T�E���h ���\�[�X�ł��B
        /// </summary>
        public ref class SoundBuffer
            : public INativeWrapper<zephyr::sound::SoundBuffer>
        {
        public:

            /// <summary>
            /// �T�E���h�t�@�C����ǂݎ���ĐV�����T�E���h�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="path">�T�E���h�t�@�C���̃p�X�B</param>
            void Create(String^ path)
            {
                Native->Create(SoundDevice::Instance->NativeRef, to_string(path).c_str());
            }

            /// <summary>
            /// �ق��̃T�E���h�o�b�t�@�̃f�[�^�����L����T�E���h�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="buffer">�f�[�^�̋��L��̃T�E���h�o�b�t�@�B</param>
            void Create(SoundBuffer^ buffer)
            {
                Native->Create(SoundDevice::Instance->NativeRef, buffer->NativeRef);
            }

            /// <summary>
            /// �T�E���h�o�b�t�@��������܂��B
            /// </summary>
            void Release()
            {
                Native->Release();
            }

            /// <summary>
            /// �T�E���h��擪����Đ����܂��B
            /// </summary>
            void Play()
            {
                Native->Play();
            }

            /// <summary>
            /// �T�E���h��擪���烋�[�v�Đ����܂��B
            /// </summary>
            void LoopPlay()
            {
                Native->LoopPlay();
            }

            /// <summary>
            /// �T�E���h���~���A�Đ��ʒu��擪�ɖ߂��܂��B
            /// </summary>
            void Stop()
            {
                Native->Stop();
            }

            /// <summary>
            /// �T�E���h���ꎞ��~�������͍ĊJ���܂��B
            /// </summary>
            void Pause()
            {
                Native->Pause();
            }

            /// <summary>
            /// �p�������Z�b�g���܂��B
            /// </summary>
            void ResetPan()
            {
                Native->ResetPan();
            }

            /// <summary>
            /// �T���v�����O���g�������Z�b�g���܂��B
            /// </summary>
            void ResetFrequency()
            {
                Native->ResetFrequency();
            }

            /// <summary>
            /// �{�����[�������Z�b�g���܂��B
            /// </summary>
            void ResetVolume()
            {
                Native->ResetVolume();
            }

            /// <summary>
            /// �T�E���h�����Đ��������ׂ܂��B
            /// </summary>
            property bool Playing { bool get() { return Native->IsPlaying; } }

            /// <summary>
            /// �T�E���h����~�������ׂ܂��B
            /// </summary>
            property bool Stopped { bool get() { return Native->IsStopped; }}

            /// <summary>
            /// �T���v�����O���g���� Hz �P�ʂŎ擾�܂��͐ݒ肵�܂��B
            /// </summary>
            property unsigned long Frequency
            {
                unsigned long get() { return Native->Frequency; }

                void set(unsigned long value) { Native->Frequency = value; }
            }

            /// <summary>
            /// ���ʂ� 0 �` 1 �͈̔͂Ŏ擾�܂��͐ݒ肵�܂��B 0 �̂Ƃ��ŏ��A 1 �̂Ƃ��ő��\���܂��B
            /// </summary>
            property double Volume 
            {
                double get() { return Native->Volume; }
            
                void set(double value) { Native->Volume = value; }
            }

            /// <summary>
            /// �p���� -1 �` +1 �͈̔͂Ŏ擾�܂��͐ݒ肵�܂��B -1 �̂Ƃ������̃X�s�[�J�[����̂݉�����A +1 �̂Ƃ��E���̃X�s�[�J�[����̂݉�����܂��B
            /// </summary>
            property double Pan 
            {
                double get() { return Native->Pan; }

                void set(double value) { Native->Pan = value; }
            }

            /// <summary>
            /// �����̃T���v�����O���g�����擾���܂��B
            /// </summary>
            property unsigned long OriginalFrequency
            {
                unsigned long get() { return Native->OriginalFrequency; }
            }

        public:

            /// <summary>
            /// �T�E���h�̒�����b�P�ʂŎ擾���܂��B
            /// </summary>
            property int Duration
            {
                int get() { return Native->Duration; }
                void set(int value) { Native->Duration = value; }
            }
        };
    }
}
