#pragma once

#include "common.h"
#include "VertexElement.h"
#include "VertexShader.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// ���_�f�[�^�̃f�[�^�\����\���܂��B
        /// </summary>
        public ref class VertexLayout 
            : public INativeWrapper<zephyr::graphics::d3d11::VertexLayout>
        {
        public:

            /// <summary>
            /// ���_���C�A�E�g���쐬���܂��B
            /// </summary>
            /// <param name="elements">���_�v�f�̔z��B</param> 
            /// <param name="shader">���C�A�E�g��K�p���钸�_�V�F�[�_�B</param> 
            void Create(array<VertexElement^>^ elements, VertexShader^ shader)
            {
                auto count = elements->Length;
                auto _elements = new zephyr::graphics::d3d11::VertexElement[count];
                auto semanticNames = new string[count];
                {
                    for (int i = 0; i < count; i++)
                    {
                        auto% src = *elements[i];
                        auto& dest = _elements[i];

                        semanticNames[i] = to_string(src.SemanticName);

                        dest.SemanticName = semanticNames[i].c_str();
                        dest.SemanticIndex = src.SemanticIndex;
                        dest.Format = (zephyr::graphics::d3d11::Format)src.Format;
                        dest.InputSlot = src.InputSlot;
                        dest.AlignedByteOffset = src.AlignedByteOffset;
                        dest.InputSlotClass = (zephyr::graphics::d3d11::VertexElement::Classification)src.InputSlotClass;
                        dest.InstanceDataStepRate = src.InstanceDataStepRate;
                    }
                }
                Native->Create(_elements, count, shader->NativeRef);
                delete[] _elements;
                delete[] semanticNames;
            }
        };
    }
}
