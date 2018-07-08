#pragma once

#include "common.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix3x2.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        /// <summary>
        /// 3x3 �s���\���܂��B�e�v�f�͍s�D��Ŋi�[����܂��B
        /// </summary>
        public value class Matrix3x3
        {
        public:

            /// <summary>
            /// �S�����̒l���ʂɎw�肵�čs����쐬���܂��B
            /// </summary>
            /// <param name="m11">(1,1) �����̏����l�B</param> 
            /// <param name="m12">(1,2) �����̏����l�B</param> 
            /// <param name="m13">(1,3) �����̏����l�B</param> 
            /// <param name="m21">(2,1) �����̏����l�B</param> 
            /// <param name="m22">(2,2) �����̏����l�B</param> 
            /// <param name="m23">(2,3) �����̏����l�B</param> 
            /// <param name="m31">(3,1) �����̏����l�B</param> 
            /// <param name="m32">(3,2) �����̏����l�B</param> 
            /// <param name="m33">(3,3) �����̏����l�B</param> 
            Matrix3x3(
                float m11, float m12, float m13,
                float m21, float m22, float m23,
                float m31, float m32, float m33)
                : M11(m11), M12(m12), M13(m13),
                M21(m21), M22(m22), M23(m23),
                M31(m31), M32(m32), M33(m33)
            {
            }

            /// <summary>
            /// �z��Ɋi�[���ꂽ�l����s����쐬���܂��B
            /// </summary>
            /// <param name="m">�e�����̏����l���s�D�揇�Ɋi�[�����z��B</param> 
            Matrix3x3(array<float>^ m)
                : Matrix3x3(
                    m[0], m[1], m[2],
                    m[3], m[4], m[5],
                    m[6], m[7], m[8])
            {
                assert(m->Length == 9);
            }

            /// <summary>
            /// �N�H�[�^�j�I���Ɠ����ϊ���\���s����쐬���܂��B
            /// </summary>
            /// <param name="q">�N�H�[�^�j�I���B</param> 
            Matrix3x3(Quaternion q)
            {
                zephyr::linalg::Matrix3x3 _m(reinterpret_cast<zephyr::linalg::Quaternion&>(q));
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this) = _m;
            }

            Matrix3x3(const zephyr::linalg::Matrix3x3& m)
            {
                this->M11 = m.m11;
                this->M12 = m.m12;
                this->M13 = m.m13;
                this->M21 = m.m21;
                this->M22 = m.m22;
                this->M23 = m.m23;
                this->M31 = m.m31;
                this->M32 = m.m32;
                this->M33 = m.m33;
            }

            /// <summary>
            /// ���̍s����P���s��ɂ��ĕԂ��܂��B
            /// </summary>
            Matrix3x3 Identity()
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).identity();
                return *this;
            }

            /// <summary>
            /// ���̍s����t�s��ɂ��ĕԂ��܂��B
            /// </summary>
            Matrix3x3 Invert()
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).invert();
                return *this;
            }

            /// <summary>
            /// �g��ϊ����s���܂��B
            /// </summary>
            /// <param name="sx">X �����g�嗦�B</param> 
            /// <param name="sy">Y �����g�嗦�B</param> 
            /// <param name="sz">Z �����g�嗦�B</param> 
            Matrix3x3 Scale(float sx, float sy, float sz)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).scale(sx, sy, sz);
                return *this;
            }

            /// <summary>
            /// �g��ϊ����s���܂��B
            /// </summary>
            /// <param name="s">X, Y, Z �����g�嗦�B</param> 
            Matrix3x3 Scale(float s)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).scale(s);
                return *this;
            }

            /// <summary>
            /// X ������ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix3x3 RotateX(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).rotateX(r);
                return *this;
            }

            /// <summary>
            /// Y ������ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix3x3 RotateY(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).rotateY(r);
                return *this;
            }

            /// <summary>
            /// Z ������ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix3x3 RotateZ(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).rotateZ(r);
                return *this;
            }

            /// <summary>
            /// �C�ӂ̎�����ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="ax">��]���� X �����B</param> 
            /// <param name="ay">��]���� Y �����B</param> 
            /// <param name="az">��]���� Z �����B</param> 
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix3x3 RotateAroundAxis(float ax, float ay, float az, float r)
            {
                auto q = Quaternion(Vector3(ax, ay, az), r);
                return this->Transform(Matrix3x3(q));
            }

            /// <summary>
            /// �C�ӂ̎�����ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="axis">��]���B</param> 
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix3x3 RotateAroundAxis(Vector3 axis, float r)
            {
                auto q = Quaternion(axis, r);
                return this->Transform(Matrix3x3(q));
            }

            /// <summary>
            /// �C�ӂ̕ϊ����s���܂��B
            /// </summary>
            /// <param name="m">�ϊ��s��B</param> 
            Matrix3x3 Transform(Matrix3x3 m)
            {
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x3&>(m);
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).transform(_m);
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
                    return reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).determinant;
                }
            }

            /// <summary>
            /// �t�s����擾���܂��B
            /// </summary>
            property Matrix3x3 Inverse
            {
                Matrix3x3 get()
                {
                    return reinterpret_cast<Matrix3x3&>(reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).inverse);
                }
            }

            float M11, M12, M13;

            float M21, M22, M23;

            float M31, M32, M33;

        internal:

            static Matrix3x3 Mul(Matrix3x3 a, Matrix3x3 b)
            {
                auto& _a = reinterpret_cast<zephyr::linalg::Matrix3x3&>(a);
                auto& _b = reinterpret_cast<zephyr::linalg::Matrix3x3&>(b);
                return reinterpret_cast<Matrix3x3&>(zephyr::linalg::mul(_a, _b));
            }

            static Vector3 Mul(Vector3 v, Matrix3x3 m)
            {
                auto& _v = reinterpret_cast<zephyr::linalg::Vector3&>(v);
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x3&>(m);
                return reinterpret_cast<Vector3&>(zephyr::linalg::mul(_v, _m));
            }

        public:

            /// <summary>
            /// �t�s����擾���܂��B
            /// </summary>
            /// <param name="m">�t�s����v�Z����s��B</param> 
            static Matrix3x3 Invert(Matrix3x3 m)
            {
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x3&>(m);
                return reinterpret_cast<Matrix3x3&>(zephyr::linalg::invert(_m));
            }

            /// <summary>
            /// �s��̏�Z���s���܂��B
            /// </summary>
            /// <param name="a">�������炩������s��B</param> 
            /// <param name="b">�E�����炩������s��B</param> 
            static Matrix3x3 operator *(Matrix3x3 a, Matrix3x3 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �x�N�g���ƍs��̏�Z���s���܂��B�x�N�g���� w ������ 1 �Ƃ��Čv�Z���܂��B
            /// </summary>
            /// <param name="a">�x�N�g���B</param> 
            /// <param name="b">�s��B</param> 
            static Vector3 operator *(Vector3 a, Matrix3x3 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �����񂩂�s��ɕϊ����܂��B
            /// </summary>
            /// <param name="str">�e�v�f�� , �ŋ�؂�ꂽ������B</param> 
            static Matrix3x3 Parse(System::String^ str);

        public:

            property zephyr::linalg::Matrix3x3 Native
            {
                zephyr::linalg::Matrix3x3 get()
                {
                    return zephyr::linalg::Matrix3x3(M11, M12, M13, M21, M22, M23, M31, M32, M33);
                }

                void set(zephyr::linalg::Matrix3x3 m)
                {
                    M11 = m.m11;
                    M12 = m.m12;
                    M13 = m.m13;
                    M21 = m.m21;
                    M22 = m.m22;
                    M23 = m.m23;
                    M31 = m.m31;
                    M32 = m.m32;
                    M33 = m.m33;
                }
            }
        };
    }
}
