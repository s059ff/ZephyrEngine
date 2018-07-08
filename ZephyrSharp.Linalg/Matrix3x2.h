#pragma once

#include "common.h"
#include "Vector2.h"
#include "Vector3.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        /// <summary>
        /// 3 ��ڂ̐����� 0, 0, 1 �Ƃ��� 3x3 �s���\���܂��B�e�v�f�͍s�D��Ŋi�[����܂��B
        /// </summary>
        public value class Matrix3x2
        {
        public:

            /// <summary>
            /// �S�����̒l���ʂɎw�肵�čs����쐬���܂��B
            /// </summary>
            /// <param name="m11">(1,1) �����̏����l�B</param> 
            /// <param name="m12">(1,2) �����̏����l�B</param> 
            /// <param name="m21">(2,1) �����̏����l�B</param> 
            /// <param name="m22">(2,2) �����̏����l�B</param> 
            /// <param name="m31">(3,1) �����̏����l�B</param> 
            /// <param name="m32">(3,2) �����̏����l�B</param> 
            Matrix3x2(
                float m11, float m12,
                float m21, float m22,
                float m31, float m32)
                : M11(m11), M12(m12),
                M21(m21), M22(m22),
                M31(m31), M32(m32)
            {
            }
            
            /// <summary>
            /// �z��Ɋi�[���ꂽ�l����s����쐬���܂��B
            /// </summary>
            /// <param name="m">�e�����̏����l���s�D�揇�Ɋi�[�����z��B</param> 
            Matrix3x2(array<float>^ m)
                : Matrix3x2(
                    m[0], m[1],
                    m[2], m[3],
                    m[4], m[5])
            {
                assert(m->Length == 6);
            }

            Matrix3x2(const zephyr::linalg::Matrix3x2& m)
            {
                this->M11 = m.m11;
                this->M12 = m.m12;
                this->M21 = m.m21;
                this->M22 = m.m22;
                this->M31 = m.m31;
                this->M32 = m.m32;
            }

            /// <summary>
            /// ���̍s����P���s��ɂ��ĕԂ��܂��B
            /// </summary>
            Matrix3x2 Identity()
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).identity();
                return *this;
            }

            /// <summary>
            /// ���̍s����t�s��ɂ��ĕԂ��܂��B
            /// </summary>
            Matrix3x2 Invert()
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).invert();
                return *this;
            }

            /// <summary>
            /// �ړ��ϊ����s���܂��B
            /// </summary>
            /// <param name="x">X �����̈ړ��ʁB</param> 
            /// <param name="y">Y �����̈ړ��ʁB</param> 
            Matrix3x2 Translate(float x, float y)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).translate(x, y);
                return *this;
            }

            /// <summary>
            /// �ړ��ϊ����s���܂��B
            /// </summary>
            /// <param name="v">�ړ��ʁB</param> 
            Matrix3x2 Translate(Vector2 v)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).translate(reinterpret_cast<zephyr::linalg::Vector2&>(v));
                return *this;
            }

            /// <summary>
            /// �g��ϊ����s���܂��B
            /// </summary>
            /// <param name="sx">X �����g�嗦�B</param> 
            /// <param name="sy">Y �����g�嗦�B</param> 
            Matrix3x2 Scale(float sx, float sy)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).scale(sx, sy);
                return *this;
            }

            /// <summary>
            /// �g��ϊ����s���܂��B
            /// </summary>
            /// <param name="s">X, Y �����g�嗦�B</param> 
            Matrix3x2 Scale(float s)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).scale(s);
                return *this;
            }

            /// <summary>
            /// ��]�ϊ����s���܂��B
            /// </summary>
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix3x2 Rotate(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).rotate(r);
                return *this;
            }

            /// <summary>
            /// �C�ӂ̕ϊ����s���܂��B
            /// </summary>
            /// <param name="m">�ϊ��s��B</param> 
            Matrix3x2 Transform(Matrix3x2 m)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).transform(reinterpret_cast<zephyr::linalg::Matrix3x2&>(m));
                return *this;
            }

            System::String^ ToString() override;

        public:

            /// <summary>
            /// �s�񎮂��擾���܂��B
            /// </summary>
            property float Determinant
            {
                float get()
                {
                    return reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).determinant;
                }
            }

            /// <summary>
            /// �t�s����擾���܂��B
            /// </summary>
            property Matrix3x2 Inverse
            {
                Matrix3x2 get()
                {
                    auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).inverse;
                    return reinterpret_cast<Matrix3x2&>(_m);
                }
            }

            /// <summary>
            /// �ړ��ʂ��擾���܂��B
            /// </summary>
            property Vector2 Position
            {
                Vector2 get()
                {
                    return Vector2(reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).position);
                }

                void set(Vector2 v)
                {
                    reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).position = reinterpret_cast<zephyr::linalg::Vector2&>(v);
                }
            }

        public:

            float M11, M12;

            float M21, M22;

            float M31, M32;

        internal:

            static Matrix3x2 Mul(Matrix3x2 a, Matrix3x2 b)
            {
                auto& _a = reinterpret_cast<zephyr::linalg::Matrix3x2&>(a);
                auto& _b = reinterpret_cast<zephyr::linalg::Matrix3x2&>(a);
                return reinterpret_cast<Matrix3x2&>(zephyr::linalg::mul(_a, _b));
            }

            static Vector2 Mul(Vector2 v, Matrix3x2 m)
            {
                auto& _v = reinterpret_cast<zephyr::linalg::Vector2&>(v);
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x2&>(m);
                return reinterpret_cast<Vector2&>(zephyr::linalg::mul(_v, _m));
            }

            static Vector3 Mul(Vector3 v, Matrix3x2 m)
            {
                auto& _v = reinterpret_cast<zephyr::linalg::Vector3&>(v);
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x2&>(m);
                return reinterpret_cast<Vector3&>(zephyr::linalg::mul(_v, _m));
            }

        public:

            /// <summary>
            /// �t�s����擾���܂��B
            /// </summary>
            /// <param name="m">�t�s����v�Z����s��B</param> 
            static Matrix3x2 Invert(Matrix3x2 m)
            {
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x2&>(m);
                return reinterpret_cast<Matrix3x2&>(zephyr::linalg::invert(_m));
            }

            /// <summary>
            /// �s��̏�Z���s���܂��B
            /// </summary>
            /// <param name="a">�������炩������s��B</param> 
            /// <param name="b">�E�����炩������s��B</param> 
            static Matrix3x2 operator *(Matrix3x2 a, Matrix3x2 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �x�N�g���ƍs��̏�Z���s���܂��B�x�N�g���� w ������ 1 �Ƃ��Čv�Z���܂��B
            /// </summary>
            /// <param name="a">�x�N�g���B</param> 
            /// <param name="b">�s��B</param> 
            static Vector3 operator *(Vector3 a, Matrix3x2 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �����񂩂�s��ɕϊ����܂��B
            /// </summary>
            /// <param name="str">�e�v�f�� , �ŋ�؂�ꂽ������B</param> 
            static Matrix3x2 Parse(System::String^ str);

        public:

            property zephyr::linalg::Matrix3x2 Native
            {
                zephyr::linalg::Matrix3x2 get()
                {
                    return zephyr::linalg::Matrix3x2(M11, M12, M21, M22, M31, M32);
                }

                void set(zephyr::linalg::Matrix3x2 m)
                {
                    M11 = m.m11;
                    M12 = m.m12;
                    M21 = m.m21;
                    M22 = m.m22;
                    M31 = m.m31;
                    M32 = m.m32;
                }
            }
        };
    }
}
