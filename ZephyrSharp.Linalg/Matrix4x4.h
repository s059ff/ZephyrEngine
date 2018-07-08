#pragma once

#include "common.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3x2.h"
#include "Matrix3x3.h"
#include "Matrix4x3.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        /// <summary>
        /// 4x4 �s���\���܂��B�e�v�f�͍s�D��Ŋi�[����܂��B
        /// </summary>
        public value class Matrix4x4
        {
        public:

            /// <summary>
            /// �S�����̒l���ʂɎw�肵�čs����쐬���܂��B
            /// </summary>
            /// <param name="m11">(1,1) �����̏����l�B</param> 
            /// <param name="m12">(1,2) �����̏����l�B</param> 
            /// <param name="m13">(1,3) �����̏����l�B</param> 
            /// <param name="m14">(1,4) �����̏����l�B</param> 
            /// <param name="m21">(2,1) �����̏����l�B</param> 
            /// <param name="m22">(2,2) �����̏����l�B</param> 
            /// <param name="m23">(2,3) �����̏����l�B</param> 
            /// <param name="m24">(2,4) �����̏����l�B</param> 
            /// <param name="m31">(3,1) �����̏����l�B</param> 
            /// <param name="m32">(3,2) �����̏����l�B</param> 
            /// <param name="m33">(3,3) �����̏����l�B</param> 
            /// <param name="m34">(3,4) �����̏����l�B</param> 
            /// <param name="m41">(4,1) �����̏����l�B</param> 
            /// <param name="m42">(4,2) �����̏����l�B</param> 
            /// <param name="m43">(4,3) �����̏����l�B</param> 
            /// <param name="m44">(4,4) �����̏����l�B</param> 
            Matrix4x4(
                float m11, float m12, float m13, float m14,
                float m21, float m22, float m23, float m24,
                float m31, float m32, float m33, float m34,
                float m41, float m42, float m43, float m44)
                : M11(m11), M12(m12), M13(m13), M14(m14),
                M21(m21), M22(m22), M23(m23), M24(m24),
                M31(m31), M32(m32), M33(m33), M34(m34),
                M41(m41), M42(m42), M43(m43), M44(m44)
            {
            }

            /// <summary>
            /// �z��Ɋi�[���ꂽ�l����s����쐬���܂��B
            /// </summary>
            /// <param name="m">�e�����̏����l���s�D�揇�Ɋi�[�����z��B</param> 
            Matrix4x4(array<float>^ m) :
                Matrix4x4(
                    m[0], m[1], m[2], m[3],
                    m[4], m[5], m[6], m[7],
                    m[8], m[9], m[10], m[11],
                    m[12], m[13], m[14], m[15])
            {
                assert(m->Length == 16);
            }

            /// <summary>
            /// �N�H�[�^�j�I���Ɠ����ϊ���\���s����쐬���܂��B
            /// </summary>
            /// <param name="q">�N�H�[�^�j�I���B</param> 
            Matrix4x4(Quaternion q)
            {
                zephyr::linalg::Matrix4x4 _m(reinterpret_cast<zephyr::linalg::Quaternion&>(q));
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this) = _m;
            }

            /// <summary>
            /// 2 �����ϊ��s��� 3 �����ϊ��s��ɃA�b�v�L���X�g���܂��B
            /// </summary>
            /// <param name="m">3x2 �s��B</param> 
            Matrix4x4(Matrix3x2 m)
            {
                zephyr::linalg::Matrix4x4 _m(reinterpret_cast<zephyr::linalg::Matrix3x2&>(m));
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this) = _m;
            }

            /// <summary>
            /// 3x3 �s��� 4x4 �s��ɃA�b�v�L���X�g���܂��B
            /// </summary>
            /// <param name="m">3x3 �s��B</param> 
            Matrix4x4(Matrix3x3 m)
            {
                zephyr::linalg::Matrix4x4 _m(reinterpret_cast<zephyr::linalg::Matrix3x3&>(m));
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this) = _m;
            }

            /// <summary>
            /// 4x3 �s��� 4x4 �s��ɃA�b�v�L���X�g���܂��B
            /// </summary>
            /// <param name="m">4x3 �s��B</param> 
            Matrix4x4(Matrix4x3 m)
                : M11(m.M11), M12(m.M12), M13(m.M13), M14(0),
                M21(m.M21), M22(m.M22), M23(m.M23), M24(0),
                M31(m.M31), M32(m.M32), M33(m.M33), M34(0),
                M41(m.M41), M42(m.M42), M43(m.M43), M44(1)
            {
            }

            Matrix4x4(const zephyr::linalg::Matrix4x4& m)
            {
                this->M11 = m.m11;
                this->M12 = m.m12;
                this->M13 = m.m13;
                this->M14 = m.m14;
                this->M21 = m.m21;
                this->M22 = m.m22;
                this->M23 = m.m23;
                this->M24 = m.m24;
                this->M31 = m.m31;
                this->M32 = m.m32;
                this->M33 = m.m33;
                this->M34 = m.m34;
                this->M41 = m.m41;
                this->M42 = m.m42;
                this->M43 = m.m43;
                this->M44 = m.m44;
            }

            /// <summary>
            /// ���̍s����P���s��ɂ��ĕԂ��܂��B
            /// </summary>
            Matrix4x4 Identity()
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).identity();
                return *this;
            }

            /// <summary>
            /// ���̍s����t�s��ɂ��ĕԂ��܂��B
            /// </summary>
            Matrix4x4 Invert()
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).invert();
                return *this;
            }

            /// <summary>
            /// �ˉe�ϊ��s����쐬���܂��B
            /// </summary>
            /// <param name="fovY">Y �����̎���p�B���W�A���Ŏw��B</param> 
            /// <param name="aspect">�� / �����̃A�X�y�N�g��B</param> 
            /// <param name="zn">�j�A�[ Z �l�B</param> 
            /// <param name="zf">�t�@�[ Z �l�B</param> 
            Matrix4x4 Perspective(float fovY, float aspect, float zn, float zf)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).perspective(fovY, aspect, zn, zf);
                return *this;
            }

            /// <summary>
            /// ���s���e�ϊ��s����쐬���܂��B
            /// </summary>
            /// <param name="w">���앝�B</param> 
            /// <param name="h">���썂���B</param> 
            /// <param name="zn">�j�A�[ Z �l�B</param> 
            /// <param name="zf">�t�@�[ Z �l�B</param> 
            Matrix4x4 Orthogonal(float w, float h, float zn, float zf)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).orthogonal(w, h, zn, zf);
                return *this;
            }

            /// <summary>
            /// �r���[�|�[�g�ϊ��s����쐬���܂��B
            /// </summary>
            /// <param name="width">�r���[�|�[�g���B</param> 
            /// <param name="height">�r���[�|�[�g�����B</param> 
            Matrix4x4 Viewport(float width, float height)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).viewport(width, height);
                return *this;
            }

            /// <summary>
            /// ���̍s�������n�_����ʂ̂���n�_�𒍎�����s��ɂ��ĕԂ��܂��B
            /// </summary>
            /// <param name="from">�������B</param> 
            /// <param name="at">������B</param> 
            /// <param name="up">������������x�N�g���B</param> 
            Matrix4x4 LookAt(Vector3 from, Vector3 at, Vector3 up)
            {
                auto& _from = reinterpret_cast<zephyr::linalg::Vector3&>(from);
                auto& _at = reinterpret_cast<zephyr::linalg::Vector3&>(at);
                auto& _up = reinterpret_cast<zephyr::linalg::Vector3&>(up);
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).lookAt(_from, _at, _up);
                return *this;
            }

            /// <summary>
            /// ���̍s�������n�_����ʂ̂���n�_�𒍎�����s��ɂ��ĕԂ��܂��B������� (0, 1, 0) �ɂȂ�܂��B
            /// </summary>
            /// <param name="from">�������B</param> 
            /// <param name="at">������B</param> 
            Matrix4x4 LookAt(Vector3 from, Vector3 at)
            {
                auto& _from = reinterpret_cast<zephyr::linalg::Vector3&>(from);
                auto& _at = reinterpret_cast<zephyr::linalg::Vector3&>(at);
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).lookAt(_from, _at);
                return *this;
            }

            /// <summary>
            /// �ړ��ϊ����s���܂��BZ �����̈ړ��ʂ� 0 �ɂȂ�܂��B
            /// </summary>
            /// <param name="x">X �����̈ړ��ʁB</param> 
            /// <param name="y">Y �����̈ړ��ʁB</param> 
            Matrix4x4 Translate(float x, float y)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).translate(x, y);
                return *this;
            }

            /// <summary>
            /// �ړ��ϊ����s���܂��B
            /// </summary>
            /// <param name="x">X �����̈ړ��ʁB</param> 
            /// <param name="y">Y �����̈ړ��ʁB</param> 
            /// <param name="z">Z �����̈ړ��ʁB</param> 
            Matrix4x4 Translate(float x, float y, float z)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).translate(x, y, z);
                return *this;
            }

            /// <summary>
            /// �ړ��ϊ����s���܂��B
            /// </summary>
            /// <param name="v">�ړ��ʁB</param> 
            Matrix4x4 Translate(Vector3 v)
            {
                auto& _v = reinterpret_cast<zephyr::linalg::Vector3&>(v);
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).translate(_v);
                return *this;
            }

            /// <summary>
            /// �g��ϊ����s���܂��B
            /// </summary>
            /// <param name="sx">X �����g�嗦�B</param> 
            /// <param name="sy">Y �����g�嗦�B</param> 
            /// <param name="sz">Z �����g�嗦�B</param> 
            Matrix4x4 Scale(float sx, float sy, float sz)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).scale(sx, sy, sz);
                return *this;
            }

            /// <summary>
            /// �g��ϊ����s���܂��B
            /// </summary>
            /// <param name="s">X, Y, Z �����g�嗦�B</param> 
            Matrix4x4 Scale(float s)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).scale(s);
                return *this;
            }

            /// <summary>
            /// X ������ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix4x4 RotateX(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).rotateX(r);
                return *this;
            }

            /// <summary>
            /// Y ������ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix4x4 RotateY(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).rotateY(r);
                return *this;
            }

            /// <summary>
            /// Z ������ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix4x4 RotateZ(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).rotateZ(r);
                return *this;
            }

            /// <summary>
            /// �C�ӂ̎�����ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="ax">��]���� X �����B</param> 
            /// <param name="ay">��]���� Y �����B</param> 
            /// <param name="az">��]���� Z �����B</param> 
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix4x4 RotateAroundAxis(float ax, float ay, float az, float r)
            {
                auto q = Quaternion(Vector3(ax, ay, az), r);
                return this->Transform(Matrix4x4(q));
            }

            /// <summary>
            /// �C�ӂ̎�����ŉ�]�ϊ����s���܂��B
            /// </summary>
            /// <param name="axis">��]���B</param> 
            /// <param name="r">��]�p�x�B���W�A���Ŏw��B</param> 
            Matrix4x4 RotateAroundAxis(Vector3 axis, float r)
            {
                auto q = Quaternion(axis, r);
                return this->Transform(Matrix4x4(q));
            }

            /// <summary>
            /// �C�ӂ̕ϊ����s���܂��B
            /// </summary>
            /// <param name="m">�ϊ��s��B</param> 
            Matrix4x4 Transform(Matrix4x4 m)
            {
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix4x4&>(m);
                reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).transform(_m);
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
                    return reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).determinant;
                }
            }

            /// <summary>
            /// �t�s����擾���܂��B
            /// </summary>
            property Matrix4x4 Inverse
            {
                Matrix4x4 get()
                {
                    return reinterpret_cast<Matrix4x4&>(reinterpret_cast<zephyr::linalg::Matrix4x4&>(*this).inverse);
                }
            }

            /// <summary>
            /// 3x3 �s��Ƀ_�E���L���X�g���܂��B
            /// </summary>
            property Matrix3x3 _Matrix3x3
            {
                Matrix3x3 get()
                {
                    return Matrix3x3(M11, M12, M13, M21, M22, M23, M31, M32, M33);
                }

                void set(Matrix3x3 m)
                {
                    M11 = m.M11; M12 = m.M12; M13 = m.M13;
                    M21 = m.M21; M22 = m.M22; M23 = m.M23;
                    M31 = m.M31; M32 = m.M32; M33 = m.M33;
                }
            }

            /// <summary>
            /// 4x3 �s��Ƀ_�E���L���X�g���܂��B
            /// </summary>
            property Matrix4x3 _Matrix4x3
            {
                Matrix4x3 get()
                {
                    return Matrix4x3(M11, M12, M13, M21, M22, M23, M31, M32, M33, M41, M42, M43);
                }

                void set(Matrix4x3 m)
                {
                    M11 = m.M11; M12 = m.M12; M13 = m.M13;
                    M21 = m.M21; M22 = m.M22; M23 = m.M23;
                    M31 = m.M31; M32 = m.M32; M33 = m.M33;
                    M41 = m.M41; M42 = m.M42; M43 = m.M43;
                }
            }

            float M11, M12, M13, M14;

            float M21, M22, M23, M24;

            float M31, M32, M33, M34;

            float M41, M42, M43, M44;

        internal:

            static Matrix4x4 Mul(Matrix4x4 a, Matrix4x4 b)
            {
                auto& _a = reinterpret_cast<zephyr::linalg::Matrix4x4&>(a);
                auto& _b = reinterpret_cast<zephyr::linalg::Matrix4x4&>(b);
                return reinterpret_cast<Matrix4x4&>(zephyr::linalg::mul(_a, _b));
            }

            static Matrix4x4 Mul(Matrix4x3 a, Matrix4x4 b)
            {
                auto& _a = reinterpret_cast<zephyr::linalg::Matrix4x3&>(a);
                auto& _b = reinterpret_cast<zephyr::linalg::Matrix4x4&>(b);
                return reinterpret_cast<Matrix4x4&>(zephyr::linalg::mul(_a, _b));
            }

            static Matrix4x4 Mul(Matrix3x3 a, Matrix4x4 b)
            {
                auto& _a = reinterpret_cast<zephyr::linalg::Matrix3x3&>(a);
                auto& _b = reinterpret_cast<zephyr::linalg::Matrix4x4&>(b);
                return reinterpret_cast<Matrix4x4&>(zephyr::linalg::mul(_a, _b));
            }

            static Matrix4x4 Mul(Matrix4x4 a, Matrix4x3 b)
            {
                auto& _a = reinterpret_cast<zephyr::linalg::Matrix4x4&>(a);
                auto& _b = reinterpret_cast<zephyr::linalg::Matrix4x3&>(b);
                return reinterpret_cast<Matrix4x4&>(zephyr::linalg::mul(_a, _b));
            }

            static Matrix4x4 Mul(Matrix4x4 a, Matrix3x3 b)
            {
                auto& _a = reinterpret_cast<zephyr::linalg::Matrix4x4&>(a);
                auto& _b = reinterpret_cast<zephyr::linalg::Matrix3x3&>(b);
                return reinterpret_cast<Matrix4x4&>(zephyr::linalg::mul(_a, _b));
            }

            static Vector3 Mul(Vector3 v, Matrix4x4 m)
            {
                auto& _v = reinterpret_cast<zephyr::linalg::Vector3&>(v);
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix4x4&>(m);
                return reinterpret_cast<Vector3&>(zephyr::linalg::mul(_v, _m));
            }

            static Vector4 Mul(Vector4 v, Matrix4x4 m)
            {
                auto& _v = reinterpret_cast<zephyr::linalg::Vector4&>(v);
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix4x4&>(m);
                return reinterpret_cast<Vector4&>(zephyr::linalg::mul(_v, _m));
            }

        public:

            /// <summary>
            /// �t�s����擾���܂��B
            /// </summary>
            /// <param name="m">�t�s����v�Z����s��B</param> 
            static Matrix4x4 Invert(Matrix4x4 m)
            {
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix4x4&>(m);
                return reinterpret_cast<Matrix4x4&>(zephyr::linalg::invert(_m));
            }

            /// <summary>
            /// �s��̏�Z���s���܂��B
            /// </summary>
            /// <param name="a">�������炩������s��B</param> 
            /// <param name="b">�E�����炩������s��B</param> 
            static Matrix4x4 operator *(Matrix4x4 a, Matrix4x4 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �s��̏�Z���s���܂��B
            /// </summary>
            /// <param name="a">�������炩������s��B</param> 
            /// <param name="b">�E�����炩������s��B</param> 
            static Matrix4x4 operator *(Matrix4x3 a, Matrix4x4 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �s��̏�Z���s���܂��B
            /// </summary>
            /// <param name="a">�������炩������s��B</param> 
            /// <param name="b">�E�����炩������s��B</param> 
            static Matrix4x4 operator *(Matrix3x3 a, Matrix4x4 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �s��̏�Z���s���܂��B
            /// </summary>
            /// <param name="a">�������炩������s��B</param> 
            /// <param name="b">�E�����炩������s��B</param> 
            static Matrix4x4 operator *(Matrix4x4 a, Matrix4x3 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �s��̏�Z���s���܂��B
            /// </summary>
            /// <param name="a">�������炩������s��B</param> 
            /// <param name="b">�E�����炩������s��B</param> 
            static Matrix4x4 operator *(Matrix4x4 a, Matrix3x3 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �x�N�g���ƍs��̏�Z���s���܂��B�x�N�g���� w ������ 1 �Ƃ��Čv�Z���܂��B
            /// </summary>
            /// <param name="a">�x�N�g���B</param> 
            /// <param name="b">�s��B</param> 
            static Vector3 operator *(Vector3 a, Matrix4x4 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �x�N�g���ƍs��̏�Z���s���܂��B
            /// </summary>
            /// <param name="a">�x�N�g���B</param> 
            /// <param name="b">�s��B</param> 
            static Vector4 operator *(Vector4 a, Matrix4x4 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// �����񂩂�s��ɕϊ����܂��B
            /// </summary>
            /// <param name="str">�e�v�f�� , �ŋ�؂�ꂽ������B</param> 
            static Matrix4x4 Parse(System::String^ str);

        public:

            property zephyr::linalg::Matrix4x4 Native
            {
                zephyr::linalg::Matrix4x4 get()
                {
                    return zephyr::linalg::Matrix4x4(M11, M12, M13, M14, M21, M22, M23, M24, M31, M32, M33, M34, M41, M42, M43, M44);
                }

                void set(zephyr::linalg::Matrix4x4 m)
                {
                    M11 = m.m11;
                    M12 = m.m12;
                    M13 = m.m13;
                    M14 = m.m14;
                    M21 = m.m21;
                    M22 = m.m22;
                    M23 = m.m23;
                    M24 = m.m24;
                    M31 = m.m31;
                    M32 = m.m32;
                    M33 = m.m33;
                    M34 = m.m34;
                    M41 = m.m41;
                    M42 = m.m42;
                    M43 = m.m43;
                    M44 = m.m44;
                }
            }
        };
    }
}
