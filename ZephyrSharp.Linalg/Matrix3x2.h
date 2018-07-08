#pragma once

#include "common.h"
#include "Vector2.h"
#include "Vector3.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        /// <summary>
        /// 3 列目の成分を 0, 0, 1 とする 3x3 行列を表します。各要素は行優先で格納されます。
        /// </summary>
        public value class Matrix3x2
        {
        public:

            /// <summary>
            /// 全成分の値を個別に指定して行列を作成します。
            /// </summary>
            /// <param name="m11">(1,1) 成分の初期値。</param> 
            /// <param name="m12">(1,2) 成分の初期値。</param> 
            /// <param name="m21">(2,1) 成分の初期値。</param> 
            /// <param name="m22">(2,2) 成分の初期値。</param> 
            /// <param name="m31">(3,1) 成分の初期値。</param> 
            /// <param name="m32">(3,2) 成分の初期値。</param> 
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
            /// 配列に格納された値から行列を作成します。
            /// </summary>
            /// <param name="m">各成分の初期値を行優先順に格納した配列。</param> 
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
            /// この行列を恒等行列にして返します。
            /// </summary>
            Matrix3x2 Identity()
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).identity();
                return *this;
            }

            /// <summary>
            /// この行列を逆行列にして返します。
            /// </summary>
            Matrix3x2 Invert()
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).invert();
                return *this;
            }

            /// <summary>
            /// 移動変換を行います。
            /// </summary>
            /// <param name="x">X 方向の移動量。</param> 
            /// <param name="y">Y 方向の移動量。</param> 
            Matrix3x2 Translate(float x, float y)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).translate(x, y);
                return *this;
            }

            /// <summary>
            /// 移動変換を行います。
            /// </summary>
            /// <param name="v">移動量。</param> 
            Matrix3x2 Translate(Vector2 v)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).translate(reinterpret_cast<zephyr::linalg::Vector2&>(v));
                return *this;
            }

            /// <summary>
            /// 拡大変換を行います。
            /// </summary>
            /// <param name="sx">X 方向拡大率。</param> 
            /// <param name="sy">Y 方向拡大率。</param> 
            Matrix3x2 Scale(float sx, float sy)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).scale(sx, sy);
                return *this;
            }

            /// <summary>
            /// 拡大変換を行います。
            /// </summary>
            /// <param name="s">X, Y 方向拡大率。</param> 
            Matrix3x2 Scale(float s)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).scale(s);
                return *this;
            }

            /// <summary>
            /// 回転変換を行います。
            /// </summary>
            /// <param name="r">回転角度。ラジアンで指定。</param> 
            Matrix3x2 Rotate(float r)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).rotate(r);
                return *this;
            }

            /// <summary>
            /// 任意の変換を行います。
            /// </summary>
            /// <param name="m">変換行列。</param> 
            Matrix3x2 Transform(Matrix3x2 m)
            {
                reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).transform(reinterpret_cast<zephyr::linalg::Matrix3x2&>(m));
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
                    return reinterpret_cast<zephyr::linalg::Matrix3x2&>(*this).determinant;
                }
            }

            /// <summary>
            /// 逆行列を取得します。
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
            /// 移動量を取得します。
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
            /// 逆行列を取得します。
            /// </summary>
            /// <param name="m">逆行列を計算する行列。</param> 
            static Matrix3x2 Invert(Matrix3x2 m)
            {
                auto& _m = reinterpret_cast<zephyr::linalg::Matrix3x2&>(m);
                return reinterpret_cast<Matrix3x2&>(zephyr::linalg::invert(_m));
            }

            /// <summary>
            /// 行列の乗算を行います。
            /// </summary>
            /// <param name="a">左側からかけられる行列。</param> 
            /// <param name="b">右側からかけられる行列。</param> 
            static Matrix3x2 operator *(Matrix3x2 a, Matrix3x2 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// ベクトルと行列の乗算を行います。ベクトルの w 成分は 1 として計算します。
            /// </summary>
            /// <param name="a">ベクトル。</param> 
            /// <param name="b">行列。</param> 
            static Vector3 operator *(Vector3 a, Matrix3x2 b)
            {
                return Mul(a, b);
            }

            /// <summary>
            /// 文字列から行列に変換します。
            /// </summary>
            /// <param name="str">各要素が , で区切られた文字列。</param> 
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
