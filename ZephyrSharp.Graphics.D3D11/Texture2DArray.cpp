#include <memory>
#include <vector>

#include "Texture2DArray.h"

using namespace DirectX;

namespace ZephyrSharp
{
    namespace Graphics
    {
        void Texture2DArray::Create(String^ path, Accessibility access)
        {
            TexMetadata metadata;
            ScratchImage scratchImage;

            HRESULT hr = LoadFromDDSFile(to_wstring(path).c_str(), 0, &metadata, scratchImage);
            runtime_assert(SUCCEEDED(hr));

            const size_t slices = scratchImage.GetImageCount();
            size_t size = 0;
            for (size_t i = 0; i < slices; i++)
            {
                size += scratchImage.GetImage(0, 0, i)->slicePitch;
            }

            std::unique_ptr<uint8_t[]> temp(new uint8_t[size]);
            size_t offset = 0;

            for (size_t i = 0; i < slices; i++)
            {
                const Image* image = scratchImage.GetImage(0, 0, 0);
                memcpy(temp.get() + offset, image->pixels, image->rowPitch * image->height);
                offset += image->slicePitch;
            }

            this->Create(temp.get(), (int)metadata.width, (int)metadata.height, slices, (Format)metadata.format, access);
        }

        void Texture2DArray::Create(array<String^>^ paths, Accessibility access)
        {
            std::unique_ptr<uint8_t[]> temp;
            size_t size = 0;
            size_t offset = 0;
            TexMetadata metadata;
            size_t count = paths->Length;

            for each (auto path in paths)
            {
                ScratchImage scratchImage;

                HRESULT hr = LoadFromWICFile(to_wstring(path).c_str(), 0, &metadata, scratchImage);
                runtime_assert(SUCCEEDED(hr));

                if (size == 0)
                {
                    size = scratchImage.GetImage(0, 0, 0)->slicePitch;
                    temp.reset(new uint8_t[size * count]);
                }

                runtime_assert(size == scratchImage.GetImage(0, 0, 0)->slicePitch);

                const Image* image = scratchImage.GetImage(0, 0, 0);
                memcpy(temp.get() + offset, image->pixels, image->rowPitch * image->height);
                offset += size;
            }

            this->Create(temp.get(), (int)metadata.width, (int)metadata.height, count, (Format)metadata.format, access);
        }

        void Texture2DArray::CreateCubeMap(String^ path, Accessibility access)
        {
            TexMetadata metadata;
            ScratchImage scratchImage;

            HRESULT hr = LoadFromDDSFile(to_wstring(path).c_str(), 0, &metadata, scratchImage);
            runtime_assert(SUCCEEDED(hr));

            const Image* image0 = scratchImage.GetImage(0, 0, 0);
            const Image* image1 = scratchImage.GetImage(0, 1, 0);
            const Image* image2 = scratchImage.GetImage(0, 2, 0);
            const Image* image3 = scratchImage.GetImage(0, 3, 0);
            const Image* image4 = scratchImage.GetImage(0, 4, 0);
            const Image* image5 = scratchImage.GetImage(0, 5, 0);
            auto n = scratchImage.GetImageCount();

            size_t size =
                image0->rowPitch * image0->height
                + image1->rowPitch * image1->height
                + image2->rowPitch * image2->height
                + image3->rowPitch * image3->height
                + image4->rowPitch * image4->height
                + image5->rowPitch * image5->height;

            std::unique_ptr<uint8_t[]> temp(new uint8_t[size]);
            size_t offset = 0;
            memcpy(temp.get() + offset, image0->pixels, image0->rowPitch * image0->height);
            offset += image0->rowPitch * image0->height;

            memcpy(temp.get() + offset, image1->pixels, image1->rowPitch * image1->height);
            offset += image1->rowPitch * image1->height;

            memcpy(temp.get() + offset, image2->pixels, image2->rowPitch * image2->height);
            offset += image2->rowPitch * image2->height;

            memcpy(temp.get() + offset, image3->pixels, image3->rowPitch * image3->height);
            offset += image3->rowPitch * image3->height;

            memcpy(temp.get() + offset, image4->pixels, image4->rowPitch * image4->height);
            offset += image4->rowPitch * image4->height;

            memcpy(temp.get() + offset, image5->pixels, image5->rowPitch * image5->height);
            offset += image5->rowPitch * image5->height;

            this->CreateCubeMap(temp.get(), (int)metadata.width, (int)metadata.height, (Format)image0->format, access);
        }
    }
}
