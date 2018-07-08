#include <DirectXTex.h>

#include "zephyr\runtime_assert.h"
#include "zephyr\smart_ptr.h"
#include "zephyr.graphics.dx11\GraphicsDevice.h"
#include "zephyr.graphics.dx11\enums.h"
#include "zephyr.graphics.dx11\_sizeof.h"

#include "Texture2DArray.h"

#define this (*this)

#define device GraphicsDevice::Instance.Device
#define context GraphicsDevice::Instance.DeviceContext

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            static std::wstring widen(const std::string& src)
            {
                std::wstring dest;
                wchar_t* wcs = new wchar_t[src.length() + 1];
                mbstowcs(wcs, src.c_str(), src.length() + 1);
                dest = wcs;
                delete[] wcs;
                return dest;
            }

            void Texture2DArray::Create(int width, int height, int count, Format format, Accessibility access, BufferBindFlags flags)
            {
                this.Create(nullptr, width, height, count, format, access, flags);
            }

            void Texture2DArray::Create(const void* source, int width, int height, int count, Format format, Accessibility access, BufferBindFlags flags)
            {
                this.Release();

                D3D11_TEXTURE2D_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                {
                    desc.Width = width;
                    desc.Height = height;
                    desc.MipLevels = 1;
                    desc.ArraySize = count;
                    desc.Format = (DXGI_FORMAT)format;
                    desc.Usage = [](Accessibility access) -> D3D11_USAGE
                    {
                        switch (access)
                        {
                        case Accessibility::None:
                            return D3D11_USAGE_IMMUTABLE;
                        case Accessibility::DynamicWriteOnly:
                            return D3D11_USAGE_DYNAMIC;
                        default:
                            return D3D11_USAGE_DEFAULT;
                        }
                    }(access);;
                    desc.BindFlags = (D3D11_BIND_FLAG)flags;
                    desc.CPUAccessFlags = [](Accessibility access) ->  UINT
                    {
                        switch (access)
                        {
                        case Accessibility::None:
                            return 0;
                        case Accessibility::ReadOnly:
                            return D3D11_CPU_ACCESS_READ;
                        case Accessibility::WriteOnly:
                            return D3D11_CPU_ACCESS_WRITE;
                        case Accessibility::ReadWrite:
                            return D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
                        case Accessibility::DynamicWriteOnly:
                            return D3D11_CPU_ACCESS_WRITE;
                        default:
                            runtime_assert(false);
                            return 0;
                        }
                    }(access);
                    desc.SampleDesc.Count = 1;
                    desc.SampleDesc.Quality = 0;
                }

                int stride = (int)_sizeof((DXGI_FORMAT)format);
                if (source != nullptr)
                {
                    D3D11_SUBRESOURCE_DATA* init = new D3D11_SUBRESOURCE_DATA[count];

                    for (int i = 0; i < count; i++)
                    {
                        D3D11_SUBRESOURCE_DATA& _init = init[i];
                        _init = D3D11_SUBRESOURCE_DATA{ 0 };
                        {
                            _init.pSysMem = (const byte*)source + i * stride * width * height;
                            _init.SysMemPitch = stride * width;
                        }
                    }
                    HRESULT hr = device->CreateTexture2D(&desc, init,&this);
                    runtime_assert(SUCCEEDED(hr));

                    delete[] init;
                }
                else
                {
                    HRESULT hr = device->CreateTexture2D(&desc, nullptr,&this);
                    runtime_assert(SUCCEEDED(hr));
                }

                m_width = width;
                m_height = height;
                m_length = count;
                m_stride = stride;
            }

            void Texture2DArray::Create(const string& path, Accessibility access)
            {
                DirectX::TexMetadata metadata;
                DirectX::ScratchImage scratchImage;

                HRESULT hr = LoadFromDDSFile(widen(path).c_str(), 0, &metadata, scratchImage);
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
                    const DirectX::Image* image = scratchImage.GetImage(0, 0, 0);
                    memcpy(temp.get() + offset, image->pixels, image->rowPitch * image->height);
                    offset += image->slicePitch;
                }

                this.Create(temp.get(), (int)metadata.width, (int)metadata.height, slices, (Format)metadata.format, access, BufferBindFlags::ShaderResource);
            }

            void Texture2DArray::Create(string paths[], int count, Accessibility access)
            {
                std::unique_ptr<uint8_t[]> temp;
                size_t size = 0;
                size_t offset = 0;
                DirectX::TexMetadata metadata;

                //for each (auto path in paths)
                for (int i = 0; i < count; i++)
                {
                    auto& path = paths[i];

                    DirectX::ScratchImage scratchImage;

                    HRESULT hr = LoadFromWICFile(widen(path).c_str(), 0, &metadata, scratchImage);
                    runtime_assert(SUCCEEDED(hr));

                    if (size == 0)
                    {
                        size = scratchImage.GetImage(0, 0, 0)->slicePitch;
                        temp.reset(new uint8_t[size * count]);
                    }

                    runtime_assert(size == scratchImage.GetImage(0, 0, 0)->slicePitch);

                    const DirectX::Image* image = scratchImage.GetImage(0, 0, 0);
                    memcpy(temp.get() + offset, image->pixels, image->rowPitch * image->height);
                    offset += size;
                }

                this.Create(temp.get(), (int)metadata.width, (int)metadata.height, count, (Format)metadata.format, access, BufferBindFlags::ShaderResource);
            }

            void Texture2DArray::CreateCubeMap(const void* source, int width, int height, Format format, Accessibility access, BufferBindFlags flags)
            {
                this.Release();

                const int count = 6;

                D3D11_TEXTURE2D_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                {
                    desc.Width = width;
                    desc.Height = height;
                    desc.MipLevels = 1;
                    desc.ArraySize = count;
                    desc.Format = (DXGI_FORMAT)format;
                    desc.Usage = [](Accessibility access) -> D3D11_USAGE
                    {
                        switch (access)
                        {
                        case Accessibility::None:
                            return D3D11_USAGE_IMMUTABLE;
                        case Accessibility::DynamicWriteOnly:
                            return D3D11_USAGE_DYNAMIC;
                        default:
                            return D3D11_USAGE_DEFAULT;
                        }
                    }(access);;
                    desc.BindFlags = (D3D11_BIND_FLAG)flags;
                    desc.CPUAccessFlags = [](Accessibility access) ->  UINT
                    {
                        switch (access)
                        {
                        case Accessibility::None:
                            return 0;
                        case Accessibility::ReadOnly:
                            return D3D11_CPU_ACCESS_READ;
                        case Accessibility::WriteOnly:
                            return D3D11_CPU_ACCESS_WRITE;
                        case Accessibility::ReadWrite:
                            return D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
                        case Accessibility::DynamicWriteOnly:
                            return D3D11_CPU_ACCESS_WRITE;
                        default:
                            runtime_assert(false);
                            return 0;
                        }
                    }(access);
                    desc.SampleDesc.Count = 1;
                    desc.SampleDesc.Quality = 0;
                    desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
                }

                int stride;
                switch (format)
                {
                case Format::Float1:
                    stride = sizeof(float);
                    break;
                case Format::Float2:
                    stride = sizeof(float) * 2;
                    break;
                case Format::Float3:
                    stride = sizeof(float) * 3;
                    break;
                case Format::Float4:
                    stride = sizeof(float) * 4;
                    break;
                case Format::UInt1:
                    stride = sizeof(uint32_t);
                    break;
                case Format::UInt2:
                    stride = sizeof(uint32_t) * 2;
                    break;
                case Format::UInt3:
                    stride = sizeof(uint32_t) * 3;
                    break;
                case Format::UInt4:
                    stride = sizeof(uint32_t) * 4;
                    break;
                case Format::SInt1:
                    stride = sizeof(int32_t);
                    break;
                case Format::SInt2:
                    stride = sizeof(int32_t) * 2;
                    break;
                case Format::SInt3:
                    stride = sizeof(int32_t) * 3;
                    break;
                case Format::SInt4:
                    stride = sizeof(int32_t) * 4;
                    break;
                case Format::UByte1:
                    stride = sizeof(byte);
                    break;
                case Format::UByte2:
                    stride = sizeof(byte) * 2;
                    break;
                case Format::UByte4:
                    stride = sizeof(byte) * 4;
                    break;
                case Format::SByte1:
                    stride = sizeof(byte);
                    break;
                case Format::SByte2:
                    stride = sizeof(byte) * 2;
                    break;
                case Format::SByte4:
                    stride = sizeof(byte) * 4;
                    break;
                case Format::UByte1Norm:
                    stride = sizeof(byte);
                    break;
                case Format::UByte2Norm:
                    stride = sizeof(byte) * 2;
                    break;
                case Format::UByte4Norm:
                    stride = sizeof(byte) * 4;
                    break;
                case Format::UByte4NormBGRA:
                    stride = sizeof(byte) * 4;
                    break;
                case Format::UShort1Norm:
                    stride = sizeof(unsigned short int);
                    break;
                case Format::UShort2Norm:
                    stride = sizeof(unsigned short int) * 2;
                    break;
                case Format::UShort4Norm:
                    stride = sizeof(unsigned short int) * 4;
                    break;
                case Format::Depth32:
                    stride = sizeof(float);
                    break;
                default:
                    runtime_assert(false);
                    break;
                }
                if (source != nullptr)
                {
                    D3D11_SUBRESOURCE_DATA init[count] = { 0 };
                    {
                        for (int i = 0; i < count; i++)
                        {
                            init[i].pSysMem = (stride * width * height * i) + (const byte*)source;
                            init[i].SysMemPitch = stride * width;
                            init[i].SysMemSlicePitch = 0;
                        }
                    }
                    HRESULT hr = device->CreateTexture2D(&desc, init,&this);
                    runtime_assert(SUCCEEDED(hr));
                }
                else
                {
                    HRESULT hr = device->CreateTexture2D(&desc, nullptr,&this);
                    runtime_assert(SUCCEEDED(hr));
                }

                m_width = width;
                m_height = height;
                m_length = count;
                m_stride = stride;
            }

            void Texture2DArray::CreateCubeMap(const string& path, Accessibility access, BufferBindFlags flags)
            {
                DirectX::TexMetadata metadata;
                DirectX::ScratchImage scratchImage;

                HRESULT hr = LoadFromDDSFile(widen(path).c_str(), 0, &metadata, scratchImage);
                runtime_assert(SUCCEEDED(hr));

                const DirectX::Image* image0 = scratchImage.GetImage(0, 0, 0);
                const DirectX::Image* image1 = scratchImage.GetImage(0, 1, 0);
                const DirectX::Image* image2 = scratchImage.GetImage(0, 2, 0);
                const DirectX::Image* image3 = scratchImage.GetImage(0, 3, 0);
                const DirectX::Image* image4 = scratchImage.GetImage(0, 4, 0);
                const DirectX::Image* image5 = scratchImage.GetImage(0, 5, 0);
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

                this.CreateCubeMap(temp.get(), (int)metadata.width, (int)metadata.height, (Format)image0->format, access, BufferBindFlags::ShaderResource);
            }

            void Texture2DArray::Release()
            {
                this.reset();

                m_width = m_height = m_length = 0;
                m_stride = 0;

                m_locked_ptr = nullptr;
                m_locked_index = 0;
                m_row_pitch = 0;
            }

            void Texture2DArray::Lock(Accessibility access, int index)
            {
                assert(m_locked_ptr == nullptr);
                assert(index < m_length);

                D3D11_MAPPED_SUBRESOURCE info;
                context->Map(this.ptr, D3D11CalcSubresource(0, index, 1), (D3D11_MAP)access, 0,&info);
                assert(info.pData != nullptr);

                m_locked_ptr = info.pData;
                m_row_pitch = info.RowPitch;
                m_locked_index = index;
            }

            void Texture2DArray::Unlock()
            {
                assert(m_locked_ptr != nullptr);

                context->Unmap(this.ptr, m_locked_index);

                m_locked_ptr = nullptr;
                m_row_pitch = 0;
                m_locked_index = 0;
            }
        }
    }
}
