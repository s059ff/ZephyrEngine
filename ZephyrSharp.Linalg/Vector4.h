#pragma once

#include "zephyr\math.h"
#include "zephyr.linalg\Vector4.h"

#include "common.h"
#include "Vector3.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        /// <summary>
        /// �l���������x�N�g����\���܂��B
        /// </summary>
        public value class Vector4
        {
        public:

            /// <summary>
            /// �S�����̒l���ʂɎw�肵�ăx�N�g�����쐬���܂��B
            /// </summary>
            /// <param name="v">X, Y, Z �̏����l</param> 
            /// <param name="w">W �̏����l</param> 
            Vector4(Vector3 v, float w) : X(v.X), Y(v.Y), Z(v.Z), W(w) {}

            /// <summary>
            /// �S�����̒l���ʂɎw�肵�ăx�N�g�����쐬���܂��B
            /// </summary>
            /// <param name="x">X �̏����l</param> 
            /// <param name="y">Y �̏����l</param> 
            /// <param name="z">Z �̏����l</param> 
            /// <param name="w">W �̏����l</param> 
            Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

            Vector4(const zephyr::linalg::Vector4& v)
                : X(v.x), Y(v.y), Z(v.z), W(v.w)
            {
            }

            System::String^ ToString() override;

            /// <summary>
            /// ��������x�N�g���ɕϊ����܂��B
            /// </summary>
            /// <param name="str">�ϊ����̕�����B�e�v�f�� , �ŋ�؂邱�ƁB</param> 
            static Vector4 Parse(System::String^ str);

            /// <summary>
            /// �[���x�N�g���B
            /// </summary>
            static const Vector4 Zero = Vector4(0, 0, 0, 0);

            float X, Y, Z, W;

        public:

            property zephyr::linalg::Vector4 Native
            {
                zephyr::linalg::Vector4 get()
                {
                    return zephyr::linalg::Vector4(X, Y, Z, W);
                }

                void set(zephyr::linalg::Vector4 v)
                {
                    X = v.x;
                    Y = v.y;
                    Z = v.z;
                    W = v.w;
                }
            }
        };
    }
}
