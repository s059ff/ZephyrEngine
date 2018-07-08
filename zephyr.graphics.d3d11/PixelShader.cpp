#include "zephyr\buffer.h"
#include "zephyr\runtime_assert.h"
#include "zephyr.filesystem\File.h"

#include "Blob.h"
#include "ConstantBuffer.h"
#include "GraphicsDevice.h"
#include "GraphicsDeviceContext.h"
#include "ShaderResourceView.h"
#include "SamplerState.h"
#include "PixelShader.h"

#define this (*this)
#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            void PixelShader::Create(const void* bytecode, size_t bytecodeSize)
            {
                this.Release();

                HRESULT hr = device->CreatePixelShader(bytecode, bytecodeSize, NULL,&this);
                runtime_assert(SUCCEEDED(hr));
            }

            void PixelShader::Create(const buffer& bytecode)
            {
                this.Create(bytecode.data(), bytecode.size());
            }

            void PixelShader::Create(const string& source, const string& entryPointName)
            {
                auto target = "ps_5_0";
                auto flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR | D3DCOMPILE_OPTIMIZATION_LEVEL3;
                Blob compiledCode, errorMsgs;
                D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, entryPointName.c_str(), target, flags, 0,&compiledCode,&errorMsgs);
                if (errorMsgs.available())
                {
                    runtime_assert(false, (const char*)errorMsgs->GetBufferPointer());
                }
                auto bytecode = compiledCode->GetBufferPointer();
                auto bytecodeSize = compiledCode->GetBufferSize();
                this.Create(bytecode, bytecodeSize);
            }

            void PixelShader::CreateFromCompiledFile(const string& path)
            {
                auto bytes = zephyr::filesystem::File::ReadAllBytes(path);
                this.Create(bytes);
            }

            void PixelShader::CreateFromFile(const string& path, const string& entryPointName)
            {
                auto texts = zephyr::filesystem::File::ReadAllTexts(path);
                this.Create(texts, entryPointName);
            }

            void PixelShader::Release()
            {
                this.reset();
            }

            void PixelShader::SetConstantBuffer(ConstantBuffer& resource, int slot)
            {
                ID3D11Buffer* buffers[1] = { resource.ptr };

                context->PSSetConstantBuffers(slot, 1, buffers);
            }

            void PixelShader::SetTextureResource(ShaderResourceView& resource, int slot)
            {
                ID3D11ShaderResourceView* views[1] = { resource.ptr };

                context->PSSetShaderResources(slot, 1, views);
            }

            void PixelShader::SetSamplerState(SamplerState& state, int slot)
            {
                ID3D11SamplerState* states[] = { state.ptr };
                context->PSSetSamplers(slot, 1, states);
            }
        }
    }
}
