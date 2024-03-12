#include "zephyr\buffer.h"
#include "zephyr\runtime_assert.h"
#include "zephyr.filesystem\File.h"

#include "Blob.h"
#include "ConstantBuffer.h"
#include "GraphicsDevice.h"
#include "GraphicsDeviceContext.h"
#include "ShaderResourceView.h"
#include "SamplerState.h"
#include "GeometryShader.h"

#define this (*this)

#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            void GeometryShader::Create(const void* bytecode, size_t bytecodeSize)
            {
                this.Release();

                HRESULT hr = device->CreateGeometryShader(bytecode, bytecodeSize, NULL, &this);
                runtime_assert(SUCCEEDED(hr));
            }

            void GeometryShader::Create(const buffer& bytecode)
            {
                this.Create(bytecode.data(), bytecode.size());
            }

            void GeometryShader::Create(const string& source, const string& entryPointName)
            {
                auto target = "gs_5_0";
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

            void GeometryShader::CreateFromCompiledFile(const string& path)
            {
                auto bytes = zephyr::filesystem::File::ReadAllBytes(path);
                this.Create(bytes);
            }

            void GeometryShader::CreateFromFile(const string& path, const string& entryPointName)
            {
                auto texts = zephyr::filesystem::File::ReadAllTexts(path);
                this.Create(texts, entryPointName);
            }

            void GeometryShader::Release()
            {
                this.reset();
            }

            void GeometryShader::SetConstantBuffer(ConstantBuffer& resource, int slot)
            {
                ID3D11Buffer* buffers[1] = { resource.ptr };

                context->GSSetConstantBuffers(slot, 1, buffers);
            }

            void GeometryShader::SetTextureResource(ShaderResourceView& resource, int slot)
            {
                ID3D11ShaderResourceView* views[1] = { resource.ptr };

                context->GSSetShaderResources(slot, 1, views);
            }

            void GeometryShader::SetSamplerState(SamplerState& state, int slot)
            {
                ID3D11SamplerState* states[] = { state.ptr };
                context->GSSetSamplers(slot, 1, states);
            }
        }
    }
}
