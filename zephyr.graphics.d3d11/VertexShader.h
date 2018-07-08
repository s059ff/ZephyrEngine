#pragma once

#include "common.h"

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            class ConstantBuffer;
            class ShaderResourceView;
            class SamplerState;

            class VertexShader : public Interface<ID3D11VertexShader>
            {
            public:

                void Create(const void* bytecode, size_t bytecodeSize);

                void Create(const buffer& bytecode);

                void Create(const string& source, const string& entryPointName);

                void CreateFromCompiledFile(const string& path);

                void CreateFromFile(const string& path)
                {
                    this->CreateFromFile(path, "main");
                }

                void CreateFromFile(const string& path, const string& entryPointName);

                void Release();

                void SetTextureResource(ShaderResourceView& resource, int slot);

                void SetConstantBuffer(ConstantBuffer& buffer, int slot);

                void SetSamplerState(SamplerState& state, int slot);

            public:

                buffer bytecode;
            };
        }
    }
}
