#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// ���_���\������v�f��\���܂��B
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
            /// ���_�v�f���`���܂��B
            /// </summary>
            /// <param name="semanticName">�V�F�[�_�ɂ�����Z�}���e�B�N�X���B</param> 
            /// <param name="semanticIndex">�V�F�[�_�ɂ�����Z�}���e�B�N�X�ԍ��B</param> 
            /// <param name="format">�f�[�^�^�B</param> 
            /// <param name="inputSlot">�V�F�[�_�̃X���b�g�ԍ��B</param> 
            /// <param name="alignedByteOffset">���̒��_�v�f�́A�X���b�g�ɐݒ肳���f�[�^�̐擪����̃I�t�Z�b�g�B</param> 
            /// <param name="inputSlotClass">���_�f�[�^���A�C���X�^���X�f�[�^���B</param> 
            /// <param name="instanceDataStepRate">�����̃C���X�^���X�ɑ΂��Ă��̗v�f��K�p���邩�B</param> 
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
            /// ���_�f�[�^�Ƃ��āA���_�v�f���`���܂��BInputSlotClass = VertexData, InstanceDataStepRate = 0 ���K�p����܂��B
            /// </summary>
            /// <param name="semanticName">�V�F�[�_�ɂ�����Z�}���e�B�N�X���B</param> 
            /// <param name="semanticIndex">�V�F�[�_�ɂ�����Z�}���e�B�N�X�ԍ��B</param> 
            /// <param name="format">�f�[�^�^�B</param> 
            /// <param name="inputSlot">�V�F�[�_�̃X���b�g�ԍ��B</param> 
            /// <param name="alignedByteOffset">���̒��_�v�f�́A�X���b�g�ɐݒ肳���f�[�^�̐擪����̃I�t�Z�b�g�B</param> 
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
