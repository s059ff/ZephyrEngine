#pragma once

#include "common.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            class Texture2D;
            class Texture2DArray;

            class ShaderResourceView : public Interface<ID3D11ShaderResourceView>
            {
            public:

                void Create(Texture2D& texture);

                void Create(Texture2DArray& textureArray);

                void CreateDepthMapView(Texture2D& texture);

                void Release();
            };
        }
    }
}
