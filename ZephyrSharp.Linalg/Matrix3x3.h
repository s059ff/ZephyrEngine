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
        /// 3x3 行列を表します。各要素は行優先で格納されます。
        /// </summary>
        public value class Matrix3x3
        {
        public:

            /// <summary>
            /// 全成分の値を個別に指定して行列を作成します。
            /// </summary>
            /// <param name="m11">(1,1) 成分の初期値。</param> 
            /// <param name="m12">(1,2) 成分の初期値。</param> 
            /// <param name="m13">(1,3) 成分の初期値。</param> 
            /// <param name="m21">(2,1) 成分の初期値。</param> 
            /// <param name="m22">(2,2) 成分の初期値。</param> 
            /// <param name="m23">(2,3) 成分の初期値。</param> 
            /// <param name="m31">(3,1) 成分の初期値。</param> 
            /// <param name="m32">(3,2) 成分の初期値。</param> 
            /// <param name="m33">(3,3) 成分の初期値。</param> 
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
            /// 配列に格納された値から行列を作成します。
            /// </summary>
            /// <param name="m">各成分の初期値を行優先順に格納した配列。</param> 
            Matrix3x3(array<float>^ m)
                : Matrix3x3(
                    m[0], m[1], m[2],
                    m[3], m[4], m[5],
                    m[6], m[7], m[8])
            {
                assert(m->Length == 9);
            }

            /// <summary>
            /// クォータニオンと同じ変換を表す行列を作成します。
            /// </summary>
            /// <param name="q">クォータニオン。</param> 
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
            /// この行列を恒等行列にして返します。
            /// </summary>
            Matrix3x3 Identity()
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).identity();
                return *this;
            }

            /// <summary>
            /// この行列を逆行列にして返します。
            /// </summary>
            Matrix3x3 Invert()
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).invert();
                return *this;
            }

            /// <summary>
            /// 拡大変換を行います。
            /// </summary>
            /// <param name="sx">X 方向拡大率。</param> 
            /// <param name="sy">Y 方向拡大率。</param> 
            /// <param name="sz">Z 方向拡大率。</param> 
            Matrix3x3 Scale(float sx, float sy, float sz)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).scale(sx, sy, sz);
                return *this;
            }

            /// <summary>
            /// 拡大変換を行います。
            /// </summary>
            /// <param name="s">X, Y, Z 方向拡大率。</param> 
            Matrix3x3 Scale(float s)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).scale(s);
                return *this;
            }

            /// <summary>
            /// X 軸周りで回転変換を行います。
            /// </summary>
            /// <param name="r">回転角度。ラジアンで指定。</param> 
            Matrix3x3 RotateX(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).rotateX(r);
                return *this;
            }

            /// <summary>
            /// Y 軸周りで回転変換を行います。
            /// </summary>
            /// <param name="r">回転角度。ラジアンで指定。</param> 
            Matrix3x3 RotateY(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).rotateY(r);
                return *this;
            }

            /// <summary>
            /// Z 軸周りで回転変換を行います。
            /// </summary>
            /// <param name="r">回転角度。ラジアンで指定。</param> 
            Matrix3x3 RotateZ(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).rotateZ(r);
                return *this;
            }

            /// <summary>
            /// 任意の軸周りで回転変換を行います。
            /// </summary>
            /// <param name="ax">回転軸の X 成分。</param> 
            /// <param name="ay">回転軸の Y 成分。</param> 
            /// <param name="az">回転軸の Z 成分。</param> 
            /// <param name="r">回転角度。ラジアンで指定。</param> 
            Matrix3x3 RotateAroundAxis(float ax, float ay, float az, float r)
            {
                auto q = Quaternion(Vector3(ax, ay, az), r);
                return this->Transform(Matrix3x3(q));
            }

            /// <summary>
            /// 任意の軸周りで回転変換を行います。
            /// </summary>
            /// <param name="axis">回転軸。</param> 
            /// <param name="r">回転角度。ラジアンで指定。</param> 
            Matrix3x3 RotateAroundAxis(Vector3 axis, float r)
            {
                auto q = Quaternion(axis, r);
                return this->Transform(Matrix3x3(q));
            }

            /// <summary>
            /// 任意の変換を行います。
            /// </summary>
            /// <param name="m">変換行列。</param> 
            Matrix3x3 Transform(Matrix3x3 m)
            {
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x3&>(m);
                reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).transform(_m);
                return *this;
            }

            System::String^ ToString() override;

        public:

            /// <summary>
            /// 行列式を取得します。
            /// </summary>
            property float Determinant
            {
                float get()
                {
                    return reinterpret_cast<zephyr::linalg::Matrix3x3&>(*this).determinant;
                }
            }

            /// <summary>
            /// 逆行列を取得します。
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
            /// 逆行列を取得します。
            /// </summary>
            /// <param name="m">逆行列を計算する行列。</param> 
            static Matrix3x3 Invert(Matrix3x3 m)
            {
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x3&>(m);
                return reinterpret_cast<Matrix3x3&>(zephyr::linalg::invert(_m));
            }

            /// <summary>
            /// 行列の乗算を行います。
            /// </summary>
            /// <param name="a">左側からかけられる行列。</param> 
            /// <param name="b">右側からかけられる行列。</param> 
            static Matrix3x3 operator *(Matrix3x3 a, Matrix3x3 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// ベクトルと行列の乗算を行います。ベクトルの w 成分は 1 として計算します。
            /// </summary>
            /// <param name="a">ベクトル。</param> 
            /// <param name="b">行列。</param> 
            static Vector3 operator *(Vector3 a, Matrix3x3 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// 文字列から行列に変換します。
            /// </summary>
            /// <param name="str">各要素が , で区切られた文字列。</param> 
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
