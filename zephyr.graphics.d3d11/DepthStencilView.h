#pragma once

#include "common.h"
#include "Texture2D.h"

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            class DepthStencilView : public Interface<ID3D11DepthStencilView>
            {
            public:

                void Create(Texture2D& depthStencil);

                void CreateDepthMapView(Texture2D& texture);

                void Release();
            };
        }
    }
}
