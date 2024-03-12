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
        /// 頂点シェーダーを表します。
        /// </summary>
        public ref class VertexShader
            : public INativeWrapper<zephyr::graphics::dx11::VertexShader>
        {
        public:

            virtual ~VertexShader() override
            {
                this->!VertexShader();
            }

            !VertexShader()
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
            /// バイナリデータからシェーダを作成します。
            /// </summary>
            /// <param name="bytecode">コンパイル済みのシェーダ バイナリデータ。</param> 
            void Create(array<byte>^ bytecode)
            {
                pin_ptr<byte> ptr = &bytecode[0];
                Native->Create(ptr, bytecode->Length);
            }

            /// <summary>
            /// ソースコードからシェーダを作成します。
            /// </summary>
            /// <param name="source">シェーダのソースコード。</param> 
            /// <param name="entryPointName">エントリーポイント名。</param> 
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
            /// コンパイル済みシェーダファイルからシェーダを作成します。
            /// </summary>
            /// <param name="path">コンパイル済みシェーダファイルのパス。</param> 
            void CreateFromCompiledFile(String^ path)
            {
                using System::IO::FileStream;
                using System::IO::FileMode;

                auto stream = gcnew FileStream(path, FileMode::Open);
                {
                    array<byte>^ buffer = gcnew array<byte>((int)stream->Length);
                    stream->Read(buffer, 0, buffer->Length);
                    stream->Close();
                    this->Create(buffer);
                }
            }

            /// <summary>
            /// "main"をエントリーポイントに持つシェーダファイルからシェーダを作成します。
            /// </summary>
            /// <param name="path">シェーダファイルのパス。</param> 
            void CreateFromFile(String^ path)
            {
                this->CreateFromFile(path, "main");
            }

            /// <summary>
            /// シェーダファイルからシェーダを作成します。
            /// </summary>
            /// <param name="path">シェーダファイルのパス。</param> 
            /// <param name="entryPointName">エントリーポイント名。</param> 
            void CreateFromFile(String^ path, String^ entryPointName)
            {
                using System::IO::StreamReader;

                auto stream = gcnew StreamReader(path);
                auto text = stream->ReadToEnd();
                stream->Close();
                this->Create(text, entryPointName);
            }

            /// <summary>
            /// テクスチャ リソースをシェーダにバインドします。
            /// </summary>
            /// <param name="resource">バインドするテクスチャ。</param> 
            /// <param name="slot">リソース スロット番号。</param> 
            void SetTexture(Texture2D^ resource, int slot)
            {
                Native->SetTextureResource(resource->ResourceView->NativeRef, slot);
            }

            /// <summary>
            /// テクスチャ配列 リソースをシェーダにバインドします。
            /// </summary>
            /// <param name="resource">バインドするテクスチャ。</param> 
            /// <param name="slot">リソース スロット番号。</param> 
            void SetTextureArray(Texture2DArray^ resource, int slot)
            {
                Native->SetTextureResource(resource->ResourceView->NativeRef, slot);
            }

            /// <summary>
            /// シェーダ変数をシェーダにバインドします。
            /// </summary>
            /// <param name="data">シェーダ変数をまとめた構造体変数。</param> 
            /// <param name="slot">リソース スロット番号。</param> 
            generic <typename T> where T : value struct void SetConstantBuffer(T data, int slot)
            {
                this->SetConstantBuffer(&data, slot, (int)sizeof(T));
            }

            /// <summary>
            /// シェーダ変数をシェーダにバインドします。
            /// </summary>
            /// <param name="data">シェーダ変数をまとめた構造体変数。</param> 
            /// <param name="slot">リソース スロット番号。</param> 
            generic <typename T> where T : value struct void SetConstantBuffer(array<T>^ data, int slot)
            {
                pin_ptr<T> ptr = &data[0];
                this->SetConstantBuffer(ptr, slot, (int)sizeof(T) * data->Length);
            }

            /// <summary>
            /// シェーダ変数をシェーダにバインドします。
            /// </summary>
            /// <param name="data">シェーダ変数をまとめた構造体変数へのポインタ。</param> 
            /// <param name="slot">リソース スロット番号。</param> 
            /// <param name="size">構造体のバイトサイズ。</param> 
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
            /// シェーダ変数をシェーダにバインドします。
            /// </summary>
            /// <param name="data">シェーダ変数をまとめたデータ。</param> 
            /// <param name="slot">リソース スロット番号。</param> 
            void SetConstantBuffer(array<byte>^ data, int slot)
            {
                pin_ptr<byte> ptr = &data[0];
                this->SetConstantBuffer((const void*)ptr, slot, data->Length);
            }

            /// <summary>
            /// 定数バッファを設定します。
            /// </summary>
            void SetConstantBuffer(ConstantBuffer^ buffer, int slot)
            {
                Native->SetConstantBuffer(buffer->NativeRef, slot);
            }

            /// <summary>
            /// テクスチャ サンプラーの設定を行います。
            /// </summary>
            /// <param name="state">サンプラー ステート。</param> 
            /// <param name="slot">サンプラー番号。</param> 
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
