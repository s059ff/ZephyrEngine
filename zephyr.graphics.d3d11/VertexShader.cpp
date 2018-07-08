#include "zephyr\buffer.h"
#include "zephyr\runtime_assert.h"
#include "zephyr.filesystem\File.h"

#include "Blob.h"
#include "ConstantBuffer.h"
#include "GraphicsDevice.h"
#include "GraphicsDeviceContext.h"
#include "ShaderResourceView.h"
#include "SamplerState.h"

#include "VertexShader.h"

#define this (*this)

#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            void VertexShader::Create(const void* bytecode, size_t bytecodeSize)
            {
                HRESULT hr = device->CreateVertexShader(bytecode, bytecodeSize, NULL, &this);
                runtime_assert(SUCCEEDED(hr));

                this.bytecode.copy_from(bytecode, bytecodeSize);
            }

            void VertexShader::Create(const buffer& bytecode)
            {
                this.Create(bytecode.data(), bytecode.size());
            }

            void VertexShader::Create(const string& source, const string& entryPointName)
            {
                auto target = "vs_5_0";
                auto flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR | D3DCOMPILE_OPTIMIZATION_LEVEL3;
                Blob compiledCode, errorMsgs;
                D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, entryPointName.c_str(), target, flags, 0, &compiledCode, &errorMsgs);
                if (errorMsgs.available())
                {
                    runtime_assert(false, (const char*)errorMsgs->GetBufferPointer());
                }

                auto bytecode = compiledCode->GetBufferPointer();
                auto bytecodeSize = compiledCode->GetBufferSize();
                this.Create(bytecode, bytecodeSize);
            }

            void VertexShader::CreateFromCompiledFile(const string& path)
            {
                auto bytes = zephyr::filesystem::File::ReadAllBytes(path);
                this.Create(bytes);
            }

            void VertexShader::CreateFromFile(const string& path, const string& entryPointName)
            {
                auto texts = zephyr::filesystem::File::ReadAllTexts(path);
                this.Create(texts, entryPointName);
            }

            void VertexShader::Release()
            {
                this.reset();
                this.bytecode.reset();
            }

            void VertexShader::SetTextureResource(ShaderResourceView& resource, int slot)
            {
                ID3D11ShaderResourceView* views[1] = { resource.ptr };

                context->VSSetShaderResources(slot, 1, views);
            }

            void VertexShader::SetConstantBuffer(ConstantBuffer& buffer, int slot)
            {
                ID3D11Buffer* buffers[] = { buffer.ptr };
                context->VSSetConstantBuffers(slot, 1, buffers);
            }

            void VertexShader::SetSamplerState(SamplerState& state, int slot)
            {
                ID3D11SamplerState* states[] = { state.ptr };
                context->VSSetSamplers(slot, 1, states);
            }
        }
    }
}
