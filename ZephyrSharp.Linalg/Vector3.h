#pragma once

#include "zephyr\math.h"
#include "zephyr.linalg\Vector3.h"

#include "common.h"

using namespace zephyr;

namespace ZephyrSharp
{
    namespace Linalg
    {
        /// <summary>
        /// 三次元ベクトルを表します。
        /// </summary>
        public value class Vector3
        {
        public:

            /// <summary>
            /// 全成分の値を個別に指定してベクトルを作成します。
            /// </summary>
            /// <param name="x">X の初期値</param> 
            /// <param name="y">Y の初期値</param> 
            /// <param name="z">Z の初期値</param> 
            Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

            Vector3(const zephyr::linalg::Vector3& v)
                : X(v.x), Y(v.y), Z(v.z)
            {
            }

            /// <summary>
            /// このベクトルを正規化して返します。
            /// </summary>
            Vector3 Normalize()
            {
                float oneOverMag = 1 / this->Magnitude;
                this->X *= oneOverMag;
                this->Y *= oneOverMag;
                this->Z *= oneOverMag;
                return *this;
            }

            System::String^ ToString() override;

            /// <summary>
            /// ベクトルの大きさを返します。
            /// </summary>
            property float Magnitude { float get() { return sqrt(X*X + Y*Y + Z*Z); } };

            /// <summary>
            /// ベクトルの大きさの２乗を返します。
            /// </summary>
            property float SquaredMagnitude { float get() { return X*X + Y*Y + Z*Z; } };

            /// <summary>
            /// 正規化したベクトルを返します。
            /// </summary>
            /// <param name="v">正規化するベクトル。</param> 
            static Vector3 Normalize(Vector3 v)
            {
                return v.Normalize();
            }

            /// <summary>
            /// ベクトルの内積を返します。
            /// </summary>
            /// <param name="a">演算対象のベクトル。</param> 
            /// <param name="b">演算対象のベクトル。</param> 
            static float Inner(Vector3 a, Vector3 b)
            {
                return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
            }

            /// <summary>
            /// ベクトルの外積を返します。
            /// </summary>
            /// <param name="a">演算対象のベクトル。</param> 
            /// <param name="b">演算対象のベクトル。</param> 
            static Vector3 Outer(Vector3 a, Vector3 b)
            {
                return Vector3(a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X);
            }

            /// <summary>
            /// 二つのベクトルの成す角を返します。
            /// </summary>
            /// <param name="a">演算対象のベクトル。</param> 
            /// <param name="b">演算対象のベクトル。</param> 
            static float Angle(Vector3 a, Vector3 b)
            {
                float cos = Inner(a, b) / (a.Magnitude * b.Magnitude);
                return acos((cos > 1) ? 1 : (cos < -1) ? -1 : cos);
            }

            /// <summary>
            /// あるベクトルを別のベクトルに投影したベクトルを返します。
            /// </summary>
            /// <param name="v">投影するベクトル。</param> 
            /// <param name="n">投影されるベクトル。</param> 
            static Vector3 Project(Vector3 v, Vector3 n)
            {
                return n * (Inner(v, n) / n.SquaredMagnitude);
            }

            /// <summary>
            /// 文字列をベクトルに変換します。
            /// </summary>
            /// <param name="str">変換元の文字列。各要素は , で区切ること。</param> 
            static Vector3 Parse(System::String^ str);

            /// <summary>
            /// ゼロベクトル。
            /// </summary>
            static const Vector3 Zero = Vector3(0, 0, 0);

            static Vector3 operator - (Vector3 v)
            {
                return Vector3(-v.X, -v.Y, -v.Z);
            }

            static Vector3 operator +(Vector3 a, Vector3 b)
            {
                return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
            }

            static Vector3 operator -(Vector3 a, Vector3 b)
            {
                return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
            }

            static Vector3 operator *(Vector3 v, float s)
            {
                return Vector3(s * v.X, s * v.Y, s * v.Z);
            }

            static Vector3 operator *(float s, Vector3 v)
            {
                return Vector3(s * v.X, s * v.Y, s * v.Z);
            }

            static Vector3 operator /(Vector3 v, float s)
            {
                return Vector3(v.X / s, v.Y / s, v.Z / s);
            }

            float X, Y, Z;

        public:

            property zephyr::linalg::Vector3 Native
            {
                zephyr::linalg::Vector3 get()
                {
                    return zephyr::linalg::Vector3(X, Y, Z);
                }

                void set(zephyr::linalg::Vector3 v)
                {
                    X = v.x;
                    Y = v.y;
                    Z = v.z;
                }
            }
        };
    }
}
