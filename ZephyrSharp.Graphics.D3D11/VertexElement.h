#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// 頂点を構成する要素を表します。
        /// </summary>
        public ref class VertexElement
        {
        public:

            enum class Classification
            {
                VertexData = 0,     // D3D11_INPUT_PER_VERTEX_DATA
                InstanceData = 1,   // D3D11_INPUT_PER_INSTANCE_DATA
            };

        public:

            /// <summary>
            /// 頂点要素を定義します。
            /// </summary>
            /// <param name="semanticName">シェーダにおけるセマンティクス名。</param> 
            /// <param name="semanticIndex">シェーダにおけるセマンティクス番号。</param> 
            /// <param name="format">データ型。</param> 
            /// <param name="inputSlot">シェーダのスロット番号。</param> 
            /// <param name="alignedByteOffset">この頂点要素の、スロットに設定されるデータの先頭からのオフセット。</param> 
            /// <param name="inputSlotClass">頂点データか、インスタンスデータか。</param> 
            /// <param name="instanceDataStepRate">何個ずつのインスタンスに対してこの要素を適用するか。</param> 
            VertexElement(
                String^ semanticName,
                unsigned int semanticIndex,
                Format format,
                unsigned int inputSlot,
                unsigned int alignedByteOffset,
                Classification inputSlotClass,
                unsigned int instanceDataStepRate
            ) : SemanticName(semanticName),
                SemanticIndex(semanticIndex),
                Format(format),
                InputSlot(inputSlot),
                AlignedByteOffset(alignedByteOffset),
                InputSlotClass(inputSlotClass),
                InstanceDataStepRate(instanceDataStepRate)
            {
            }

            /// <summary>
            /// 頂点データとして、頂点要素を定義します。InputSlotClass = VertexData, InstanceDataStepRate = 0 が適用されます。
            /// </summary>
            /// <param name="semanticName">シェーダにおけるセマンティクス名。</param> 
            /// <param name="semanticIndex">シェーダにおけるセマンティクス番号。</param> 
            /// <param name="format">データ型。</param> 
            /// <param name="inputSlot">シェーダのスロット番号。</param> 
            /// <param name="alignedByteOffset">この頂点要素の、スロットに設定されるデータの先頭からのオフセット。</param> 
            VertexElement(
                String^ semanticName,
                unsigned int semanticIndex,
                Format format,
                unsigned int inputSlot,
                unsigned int alignedByteOffset
            ) : SemanticName(semanticName),
                SemanticIndex(semanticIndex),
                Format(format),
                InputSlot(inputSlot),
                AlignedByteOffset(alignedByteOffset)
            {
            }

        public:

            String^ SemanticName = nullptr;

            unsigned int SemanticIndex = 0;

            Format Format;

            unsigned int InputSlot = 0;

            unsigned int AlignedByteOffset = 0;

            Classification InputSlotClass = Classification::VertexData;

            unsigned int InstanceDataStepRate = 0;
        };
    }
}
