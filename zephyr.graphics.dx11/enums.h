#pragma once

//#include <d3d11.h>

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            enum class Accessibility
            {
                None = 0,               // アクセス不可
                ReadOnly = 1,           // D3D11_MAP_READ
                WriteOnly = 2,          // D3D11_MAP_WRITE
                ReadWrite = 3,          // D3D11_MAP_READ_WRITE
                DynamicWriteOnly = 4    // D3D11_MAP_WRITE_DISCARD
            };

            enum class PrimitiveTopology
            {
                Undefined = 0,      // D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED
                PointList = 1,      // D3D11_PRIMITIVE_TOPOLOGY_POINTLIST
                LineList = 2,       // D3D11_PRIMITIVE_TOPOLOGY_LINELIST
                LineStrip = 3,      // D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP
                TriangleList = 4,   // D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
                TriangleStrip = 5   // D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
            };

            enum class BufferBindFlags
            {
                VertexBuffer = 0x1L,    // D3D11_BIND_VERTEX_BUFFER,
                IndexBuffer = 0x2L,     // D3D11_BIND_INDEX_BUFFER 
                ConstantBuffer = 0x4L,  // D3D11_BIND_CONSTANT_BUFFER 
                ShaderResource = 0x8L,  // D3D11_BIND_SHADER_RESOURCE
                StreamOutput = 0x10L,   // D3D11_BIND_STREAM_OUTPUT
                RenderTarget = 0x20L,   // D3D11_BIND_RENDER_TARGET
                DepthStencil = 0x40L,   // D3D11_BIND_DEPTH_STENCIL
                UnorderedAccess = 0x80L,// D3D11_BIND_UNORDERED_ACCESS
                Decoder = 0x200L,       // D3D11_BIND_DECODER
                VideoEncoder = 0x400L   // D3D11_BIND_VIDEO_ENCODER
            };

            enum class Format
            {
                Float1 = 41,    // DXGI_FORMAT_R32_FLOAT,
                Float2 = 16,    // DXGI_FORMAT_R32G32_FLOAT,
                Float3 = 6,     // DXGI_FORMAT_R32G32B32_FLOAT,
                Float4 = 2,     // DXGI_FORMAT_R32G32B32A32_FLOAT,

                UInt1 = 42,     // DXGI_FORMAT_R32_UINT,
                UInt2 = 17,     // DXGI_FORMAT_R32G32_UINT,
                UInt3 = 7,      // DXGI_FORMAT_R32G32B32_UINT,
                UInt4 = 3,      // DXGI_FORMAT_R32G32B32A32_UINT,

                SInt1 = 43,     // DXGI_FORMAT_R32_SINT,
                SInt2 = 18,     // DXGI_FORMAT_R32G32_SINT,
                SInt3 = 8,      // DXGI_FORMAT_R32G32B32_SINT,
                SInt4 = 4,      // DXGI_FORMAT_R32G32B32A32_SINT,

                UByte1 = 62,    // DXGI_FORMAT_R8_UINT
                UByte2 = 50,    // DXGI_FORMAT_R8G8_UINT
                UByte4 = 30,    // DXGI_FORMAT_R8G8B8A8_UINT

                SByte1 = 64,    // DXGI_FORMAT_R8_SINT
                SByte2 = 52,    // DXGI_FORMAT_R8G8_SINT
                SByte4 = 32,    // DXGI_FORMAT_R8G8B8A8_SINT

                UByte1Norm = 61,    // DXGI_FORMAT_R8_UNORM
                UByte2Norm = 49,    // DXGI_FORMAT_R8G8_UNORM
                UByte4Norm = 28,    // DXGI_FORMAT_R8G8B8A8_UNORM 

                UShort1Norm = 56,   // DXGI_FORMAT_R16_UNORM
                UShort2Norm = 35,   // DXGI_FORMAT_R16G16_UNORM
                UShort4Norm = 11,   // DXGI_FORMAT_R16G16B16A16_UNORM

                UByte4NormRGBA = 28,    // DXGI_FORMAT_R8G8B8A8_UNORM
                UByte4NormBGRA = 87,    // DXGI_FORMAT_B8G8R8A8_UNORM
                UByte4NormBGRX = 88,    // DXGI_FORMAT_B8G8R8X8_UNORM
                UByte4NormSRGB = 29,    // DXGI_FORMAT_R8G8B8A8_UNORM_SRGB

                Depth32 = 40,       // DXGI_FORMAT_D32_FLOAT
            };

            enum class Usage
            {
                Default = 0,    // D3D11_USAGE_DEFAULT
                Immutable = 1,  // D3D11_USAGE_IMMUTABLE
                Dynamic = 2,    // D3D11_USAGE_DYNAMIC
            };

            enum class CpuAccessibility
            {
                None = 0,
                Read = 0x20000L,	// D3D11_CPU_ACCESS_READ
                Write = 0x10000L,	// D3D11_CPU_ACCESS_WRITE
                ReadWrite = Read | Write
            };

            enum class BlendFactor
            {
                Zero = 1,           // D3D11_BLEND_ZERO
                One = 2,            // D3D11_BLEND_ONE
                SrcAlpha = 5,       // D3D11_BLEND_SRC_ALPHA
                DestAlpha = 7,      // D3D11_BLEND_DEST_ALPHA
                SrcColor = 3,       // D3D11_BLEND_SRC_COLOR
                DestColor = 9,      // D3D11_BLEND_DEST_COLOR
                InvSrcAlpha = 6,    // D3D11_BLEND_INV_SRC_ALPHA
                InvDestAlpha = 8,   // D3D11_BLEND_INV_DEST_ALPHA
                InvSrcColor = 4,    // D3D11_BLEND_INV_SRC_COLOR
                InvDestColor = 10   // D3D11_BLEND_INV_DEST_COLOR
            };

            enum class BlendOperation
            {
                None = 0,           // (No blend keyword)
                Add = 1,            // D3D11_BLEND_OP_ADD
                Subtract = 2,       // D3D11_BLEND_OP_SUBTRACT
                RevSubtract = 3,    // D3D11_BLEND_OP_REV_SUBTRACT
                Min = 4,            // D3D11_BLEND_OP_MIN
                Max = 5,            // D3D11_BLEND_OP_MAX
            };

            enum class FillMode
            {
                WireFrame = 2,  // D3D11_FILL_WIREFRAME
                Solid = 3,      // D3D11_FILL_SOLID
            };

            enum class CullMode
            {
                None = 1,       // D3D11_CULL_NONE
                Front = 2,      // D3D11_CULL_FRONT
                Back = 3,       // D3D11_CULL_BACK
            };

            enum class TextureAddressMode
            {
                Wrap = 1,       // D3D11_TEXTURE_ADDRESS_WRAP
                Mirror = 2,     // D3D11_TEXTURE_ADDRESS_MIRROR
                Clamp = 3,      // D3D11_TEXTURE_ADDRESS_CLAMP
                Border = 4,     // D3D11_TEXTURE_ADDRESS_BORDER
                MirrorOnce = 5  // D3D11_TEXTURE_ADDRESS_MIRROR_ONCE
            };

            inline BufferBindFlags operator | (BufferBindFlags a, BufferBindFlags b)
            {
                return (BufferBindFlags)((int)a | (int)b);
            }
        }
    }
}
