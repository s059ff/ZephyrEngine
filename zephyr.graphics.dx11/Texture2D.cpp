#include "zephyr\buffer.h"
#include "zephyr\vector.h"
#include "zephyr\matrix.h"
#include "zephyr\runtime_assert.h"
#include "zephyr.graphics\ColorCode.h"
#include "zephyr.graphics\Font.h"
#include "zephyr.filesystem\Path.h"

#include "GraphicsDevice.h"
#include "GraphicsDeviceContext.h"
#include "enums.h"
#include "_sizeof.h"
#include "Texture2D.h"

#define this (*this)

#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

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

            void Texture2D::Create(int width, int height, Format format, Accessibility access, BufferBindFlags flags)
            {
                this.Create(nullptr, width, height, format, access, flags);
            }

            void Texture2D::Create(const void* source, int width, int height, Format format, Accessibility access, BufferBindFlags flags)
            {
                this.Release();

                D3D11_TEXTURE2D_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                {
                    desc.Width = width;
                    desc.Height = height;
                    desc.MipLevels = 1;
                    desc.ArraySize = 1;
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
                    D3D11_SUBRESOURCE_DATA init = { 0 };
                    {
                        init.pSysMem = source;
                        init.SysMemPitch = stride * width;
                    }
                    HRESULT hr = device->CreateTexture2D(&desc, &init, &this);
                    runtime_assert(SUCCEEDED(hr));
                }
                else
                {
                    HRESULT hr = device->CreateTexture2D(&desc, nullptr, &this);
                    runtime_assert(SUCCEEDED(hr));
                }

                m_width = width;
                m_height = height;
                m_stride = stride;
            }

            void Texture2D::Create(const string& path, Accessibility access)
            {
                DirectX::TexMetadata metadata;
                DirectX::ScratchImage scratchImage;

                if (zephyr::filesystem::Path::GetExtension(path) == ".dds")
                {
                    HRESULT hr = LoadFromDDSFile(widen(path).c_str(), 0, &metadata, scratchImage);
                    runtime_assert(SUCCEEDED(hr));
                }
                else
                {
                    HRESULT hr = LoadFromWICFile(widen(path).c_str(), 0, &metadata, scratchImage);
                    runtime_assert(SUCCEEDED(hr));
                }

                const DirectX::Image* image = scratchImage.GetImage(0, 0, 0);
                this.Create(image->pixels, image->width, image->height, (Format)image->format, access, BufferBindFlags::ShaderResource);
            }

            void Texture2D::CreateDepthStencil(int width, int height)
            {
                this.Release();

                D3D11_TEXTURE2D_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                {
                    desc.Width = width;
                    desc.Height = height;
                    desc.MipLevels = 1;
                    desc.ArraySize = 1;
                    desc.Format = DXGI_FORMAT_D32_FLOAT;
                    desc.Usage = D3D11_USAGE_DEFAULT;
                    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
                    desc.CPUAccessFlags = 0;
                    desc.SampleDesc.Count = 1;
                    desc.SampleDesc.Quality = 0;
                }
                HRESULT hr = device->CreateTexture2D(&desc, nullptr, &this);
                runtime_assert(SUCCEEDED(hr));

                int stride = (int)sizeof(float);

                m_width = width;
                m_height = height;
                m_stride = stride;
            }

            void Texture2D::CreateDepthMap(int width, int height)
            {
                this.Release();

                D3D11_TEXTURE2D_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                {
                    desc.Width = width;
                    desc.Height = height;
                    desc.MipLevels = 1;
                    desc.ArraySize = 1;
                    desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
                    desc.Usage = D3D11_USAGE_DEFAULT;
                    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
                    desc.CPUAccessFlags = 0;
                    desc.SampleDesc.Count = 1;
                    desc.SampleDesc.Quality = 0;
                }
                HRESULT hr = device->CreateTexture2D(&desc, nullptr, &this);
                runtime_assert(SUCCEEDED(hr));

                int stride = sizeof(float);

                m_width = width;
                m_height = height;
                m_stride = stride;
            }

            void Texture2D::Release()
            {
                this.reset();

                m_locked_ptr = nullptr;
                m_width = m_height = 0;
                m_row_pitch = 0;
                m_stride = 0;
            }

            void Texture2D::Lock(Accessibility access)
            {
                assert(m_locked_ptr == nullptr);

                D3D11_MAPPED_SUBRESOURCE info;
                context->Map(this.ptr, 0, (D3D11_MAP)access, 0, &info);
                assert(info.pData != nullptr);

                m_locked_ptr = info.pData;
                m_row_pitch = info.RowPitch;
            }

            void Texture2D::Unlock()
            {
                assert(m_locked_ptr != nullptr);

                context->Unmap(this.ptr, 0);

                m_locked_ptr = nullptr;
                m_row_pitch = 0;
            }

            void Texture2D::Print(const Font& font, wchar_t charactor)
            {
                // デバイスコンテキストハンドルを取得する
                auto hdc = GetDC(nullptr);

                try
                {
                    // 現在のデバイスコンテキストのフォントを設定する
                    SelectObject(hdc, font.handle);

                    // 必要なバッファのサイズを取得する
                    GLYPHMETRICS glyphmetrics;
                    MAT2 mat2 = { { 0, 1 },{ 0, 0 },{ 0, 0 },{ 0, 1 } };
                    auto buffer_size = GetGlyphOutlineW(hdc, charactor, GGO_GRAY8_BITMAP, &glyphmetrics, 0, nullptr, &mat2);
                    runtime_assert(buffer_size != 0, "指定された文字は、印字可能文字ではありません。");

                    // ビットマップを取得する
                    vector<byte> bitmap(buffer_size);
                    GetGlyphOutlineW(hdc, charactor, GGO_GRAY8_BITMAP, &glyphmetrics, buffer_size, bitmap.data(), &mat2);

                    TEXTMETRICW metric;
                    GetTextMetricsW(hdc, &metric);

                    // テクスチャを再構築する
                    unsigned width = (unsigned)glyphmetrics.gmCellIncX;
                    unsigned height = (unsigned)metric.tmHeight;
                    matrix<ColorCode> init(height, width);
                    memset(init.data(), 0, height * width * sizeof(ColorCode));
                    {
                        unsigned stride = glyphmetrics.gmBlackBoxX + (4 - (glyphmetrics.gmBlackBoxX % 4)) % 4;
                        const byte* data = bitmap.data();
                        for (unsigned v = 0; v < glyphmetrics.gmBlackBoxY; v++)
                        {
                            for (unsigned u = 0; u < glyphmetrics.gmBlackBoxX; u++)
                            {
                                byte a = (byte)(255 * data[u] / 64);
                                unsigned x = glyphmetrics.gmptGlyphOrigin.x + u;
                                unsigned y = metric.tmAscent - glyphmetrics.gmptGlyphOrigin.y + v;
                                if (x >= 0 && x < width&& y >= 0 && y < height)
                                {
                                    init(y, x) = ColorCode(a, a, a, a);
                                }
                            }
                            data += stride;
                        }
                    }
                    this.Create(init.data(), width, height, Format::UByte4Norm, Accessibility::None, BufferBindFlags::ShaderResource);
                }
                catch (std::exception)
                {
                }

                // オブジェクトの解放
                ReleaseDC(nullptr, hdc);
            }
        }
    }
}
