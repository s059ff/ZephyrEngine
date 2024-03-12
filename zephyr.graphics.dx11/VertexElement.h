#pragma once

#include "enums.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            class VertexElement
            {
            public:

                enum class Classification
                {
                    VertexData = 0,     // D3D11_INPUT_PER_VERTEX_DATA
                    InstanceData = 1,   // D3D11_INPUT_PER_INSTANCE_DATA
                };

            public:

                VertexElement() { }

                VertexElement(
                    const char* SemanticName,
                    unsigned int SemanticIndex,
                    Format Format,
                    unsigned int InputSlot,
                    unsigned int AlignedByteOffset,
                    Classification InputSlotClass,
                    unsigned int InstanceDataStepRate
                ) : SemanticName(SemanticName),
                    SemanticIndex(SemanticIndex),
                    Format(Format),
                    InputSlot(InputSlot),
                    AlignedByteOffset(AlignedByteOffset),
                    InputSlotClass(InputSlotClass),
                    InstanceDataStepRate(InstanceDataStepRate)
                {
                }

            public:

                const char* SemanticName;

                unsigned int SemanticIndex = 0;

                Format Format;

                unsigned int InputSlot = 0;

                unsigned int AlignedByteOffset = 0;

                Classification InputSlotClass = Classification::VertexData;

                unsigned int InstanceDataStepRate = 0;
            };
        }
    }
}
