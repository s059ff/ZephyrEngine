#include "Texture2D.h"

using namespace DirectX;

namespace ZephyrSharp
{
    namespace Graphics
    {
        void Texture2D::Create(String^ path, Accessibility access)
        {
            TexMetadata metadata;
            ScratchImage scratchImage;

            if (System::IO::Path::GetExtension(path) == ".dds")
            {
                HRESULT hr = LoadFromDDSFile(to_wstring(path).c_str(), 0, &metadata, scratchImage);
                runtime_assert(SUCCEEDED(hr));
            }
            else
            {
                HRESULT hr = LoadFromWICFile(to_wstring(path).c_str(), 0, &metadata, scratchImage);
                runtime_assert(SUCCEEDED(hr));
            }

            const Image* image = scratchImage.GetImage(0, 0, 0);
            this->Create(image->pixels, image->width, image->height, (Format)image->format, access);
        }
    }
}
