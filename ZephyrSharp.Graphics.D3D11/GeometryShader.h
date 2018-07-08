#pragma once

#include "common.h"
#include "ConstantBuffer.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "SamplerState.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �W�I���g�� �V�F�[�_�[��\���܂��B
        /// </summary>
        public ref class GeometryShader
            : public INativeWrapper<zephyr::graphics::d3d11::GeometryShader>
        {
        public:

            virtual ~GeometryShader() override
            {
                this->!GeometryShader();
            }

            !GeometryShader()
            {
                for each (auto% buffer in this->constant_buffers)
                {
                    if (buffer != nullptr)
                    {
                        delete buffer;
                        buffer = nullptr;
                    }
                }
            }

            /// <summary>
            /// �o�C�i���f�[�^����V�F�[�_���쐬���܂��B
            /// </summary>
            /// <param name="bytecode">�R���p�C���ς݂̃V�F�[�_ �o�C�i���f�[�^�B</param> 
            void Create(array<byte>^ bytecode)
            {
                pin_ptr<byte> ptr = &bytecode[0];
                Native->Create(ptr, bytecode->Length);
            }

            /// <summary>
            /// �\�[�X �X�N���v�g����V�F�[�_���쐬���܂��B
            /// </summary>
            /// <param name="source">�\�[�X �X�N���v�g�B</param> 
            /// <param name="entryPointName">�G���g���[�|�C���g���B</param> 
            void Create(String^ source, String^ entryPointName)
            {
                auto csource = to_string(source);
                auto centryPointName = to_string(entryPointName);
                try
                {
                    Native->Create(csource.c_str(), centryPointName.c_str());
                }
                catch (const std::exception& e)
                {
                    runtime_assert(false, to_string(e.what()));
                }
            }

            /// <summary>
            /// �R���p�C���ς݃V�F�[�_�t�@�C������V�F�[�_���쐬���܂��B
            /// </summary>
            /// <param name="path">�R���p�C���ς݃V�F�[�_�t�@�C���̃p�X�B</param> 
            void CreateFromCompiledFile(String^ path)
            {
                using System::IO::FileStream;
                using System::IO::FileMode;

                auto stream = gcnew FileStream(path, FileMode::Open);
                {
                    array<byte>^ buffer = gcnew array<byte>((int)stream->Length);
                    stream->Read(buffer, 0, buffer->Length);
                    this->Create(buffer);
                    stream->Close();
                }
            }

            /// <summary>
            /// "main"���G���g���[�|�C���g�Ɏ��V�F�[�_�t�@�C������V�F�[�_���쐬���܂��B
            /// </summary>
            /// <param name="path">�V�F�[�_�t�@�C���̃p�X�B</param> 
            void CreateFromFile(String^ path)
            {
                this->CreateFromFile(path, "main");
            }

            /// <summary>
            /// �V�F�[�_�t�@�C������V�F�[�_���쐬���܂��B
            /// </summary>
            /// <param name="path">�V�F�[�_�t�@�C���̃p�X�B</param> 
            /// <param name="entryPointName">�G���g���[�|�C���g���B</param> 
            void CreateFromFile(String^ path, String^ entryPointName)
            {
                using System::IO::StreamReader;

                auto stream = gcnew StreamReader(path);
                this->Create(stream->ReadToEnd(), entryPointName);
                stream->Close();
            }

            /// <summary>
            /// �e�N�X�`�� ���\�[�X���V�F�[�_�Ƀo�C���h���܂��B
            /// </summary>
            /// <param name="resource">�o�C���h����e�N�X�`���B</param> 
            /// <param name="slot">���\�[�X �X���b�g�ԍ�</param> 
            void SetTexture(Texture2D^ resource, int slot)
            {
                Native->SetTextureResource(resource->ResourceView->NativeRef, slot);
            }

            /// <summary>
            /// �e�N�X�`���z�� ���\�[�X���V�F�[�_�Ƀo�C���h���܂��B
            /// </summary>
            /// <param name="resource">�o�C���h����e�N�X�`���B</param> 
            /// <param name="slot">���\�[�X �X���b�g�ԍ�</param> 
            void SetTextureArray(Texture2DArray^ resource, int slot)
            {
                Native->SetTextureResource(resource->ResourceView->NativeRef, slot);
            }

            /// <summary>
            /// �V�F�[�_�ϐ����V�F�[�_�Ƀo�C���h���܂��B
            /// </summary>
            /// <param name="data">�V�F�[�_�ϐ����܂Ƃ߂��\���̕ϐ��B</param> 
            /// <param name="slot">���\�[�X �X���b�g�ԍ��B</param> 
            generic <typename T> where T : value struct void SetConstantBuffer(T data, int slot)
            {
                this->SetConstantBuffer(&data, slot, (int)sizeof(T));
            }

            /// <summary>
            /// �V�F�[�_�ϐ����V�F�[�_�Ƀo�C���h���܂��B
            /// </summary>
            /// <param name="data">�V�F�[�_�ϐ����܂Ƃ߂��\���̕ϐ��B</param> 
            /// <param name="slot">���\�[�X �X���b�g�ԍ��B</param> 
            generic <typename T> where T : value struct void SetConstantBuffer(array<T>^ data, int slot)
            {
                pin_ptr<T> ptr = &data[0];
                this->SetConstantBuffer(ptr, slot, (int)sizeof(T) * data->Length);
            }

            /// <summary>
            /// �V�F�[�_�ϐ����V�F�[�_�Ƀo�C���h���܂��B
            /// </summary>
            /// <param name="data">�V�F�[�_�ϐ����܂Ƃ߂��\���̕ϐ��ւ̃|�C���^�B</param> 
            /// <param name="slot">���\�[�X �X���b�g�ԍ��B</param> 
            /// <param name="size">�\���̂̃o�C�g�T�C�Y�B</param> 
            void SetConstantBuffer(const void* data, int slot, int size)
            {
                assert(slot < MaxSlot);

                auto% constant_buffer = constant_buffers[slot];

                if (constant_buffer == nullptr)
                {
                    constant_buffer = gcnew ConstantBuffer();
                    constant_buffer->Create(size);
                    constant_buffer->Update(data);
                }
                else
                {
                    constant_buffer->Update(data);
                }

                Native->SetConstantBuffer(constant_buffer->NativeRef, slot);
            }

            /// <summary>
            /// �V�F�[�_�ϐ����V�F�[�_�Ƀo�C���h���܂��B
            /// </summary>
            /// <param name="data">�V�F�[�_�ϐ����܂Ƃ߂��f�[�^�B</param> 
            /// <param name="slot">���\�[�X �X���b�g�ԍ��B</param> 
            void SetConstantBuffer(array<byte>^ data, int slot)
            {
                pin_ptr<byte> ptr = &data[0];
                this->SetConstantBuffer((const void*)ptr, slot, data->Length);
            }

            /// <summary>
            /// �e�N�X�`�� �T���v���[�̐ݒ���s���܂��B
            /// </summary>
            /// <param name="state">�T���v���[ �X�e�[�g�B</param> 
            /// <param name="slot">�T���v���[�ԍ��B</param> 
            void SetSamplerState(SamplerState^ state, int slot)
            {
                Native->SetSamplerState(state->NativeRef, slot);
            }

        private:

            const int MaxSlot = 8;

            array<ConstantBuffer^>^ constant_buffers = gcnew array<ConstantBuffer^>(MaxSlot);
        };
    }
}
