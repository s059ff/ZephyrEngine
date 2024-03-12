#include "GraphicsDevice.h"
#include "GraphicsDeviceContext.h"
#include "enums.h"
#include "Buffer.h"

#define this (*this)
#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            void Buffer::Create(const void* source, int size, Accessibility access, BufferBindFlags flags)
            {
                Usage usage = [](Accessibility access) -> Usage
                {
                    switch (access)
                    {
                    case Accessibility::None:
                        return Usage::Immutable;
                    case Accessibility::DynamicWriteOnly:
                        return Usage::Dynamic;
                    default:
                        return Usage::Default;
                    }
                }(access);

                CpuAccessibility cpuAcess = [](Accessibility access) ->  CpuAccessibility
                {
                    switch (access)
                    {
                    case Accessibility::None:
                        return CpuAccessibility::None;
                    case Accessibility::ReadOnly:
                        return CpuAccessibility::Read;
                    case Accessibility::WriteOnly:
                        return CpuAccessibility::Write;
                    case Accessibility::ReadWrite:
                        return CpuAccessibility::ReadWrite;
                    case Accessibility::DynamicWriteOnly:
                        return CpuAccessibility::Write;
                    default:
                        runtime_assert(false);
                        return CpuAccessibility::None;
                    }
                }(access);

                this.Create(source, size, cpuAcess, flags, usage);
            }

            void Buffer::Create(const void* source, int size, CpuAccessibility cpuAccess, BufferBindFlags flags, Usage usage)
            {
                this.Release();

                D3D11_BUFFER_DESC desc = { 0 };
                desc.Usage = (D3D11_USAGE)usage;
                desc.ByteWidth = size;
                desc.BindFlags = (D3D11_BIND_FLAG)flags;
                desc.CPUAccessFlags = (D3D11_CPU_ACCESS_FLAG)cpuAccess;

                if (source != nullptr)
                {
                    D3D11_SUBRESOURCE_DATA init;
                    init.pSysMem = source;

                    HRESULT hr = device->CreateBuffer(&desc, &init, &this);
                    runtime_assert(SUCCEEDED(hr));
                }
                else
                {
                    HRESULT hr = device->CreateBuffer(&desc, nullptr, &this);
                    runtime_assert(SUCCEEDED(hr));
                }

                m_size = size;
                m_locked_ptr = nullptr;
            }

            void Buffer::Release()
            {
                m_size = 0;
                m_locked_ptr = nullptr;
                this.reset();
            }

            void Buffer::Lock(Accessibility access)
            {
                assert(m_locked_ptr == nullptr);

                D3D11_MAPPED_SUBRESOURCE info;
                context->Map(this.ptr, 0, (D3D11_MAP)access, 0, &info);

                m_locked_ptr = info.pData;
            }

            void Buffer::Unlock()
            {
                assert(m_locked_ptr != nullptr);

                context->Unmap(this.ptr, 0);

                m_locked_ptr = nullptr;
            }
        }
    }
}
