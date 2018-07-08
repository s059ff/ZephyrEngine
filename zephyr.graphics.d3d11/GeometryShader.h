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

            class GeometryShader : public Interface<ID3D11GeometryShader>
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

                void SetConstantBuffer(ConstantBuffer& resource, int slot);

                void SetTextureResource(ShaderResourceView& resource, int slot);

                void SetSamplerState(SamplerState& state, int slot);
            };
        }
    }
}
