#pragma once

#include "zephyr\math.h"
#include "zephyr.linalg\Vector2.h"

#include "common.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        /// <summary>
        /// 二次元ベクトルを表します。
        /// </summary>
        public value class Vector2
        {
        public:
            
            /// <summary>
            /// 全成分の値を個別に指定してベクトルを作成します。
            /// </summary>
            /// <param name="x">X の初期値</param> 
            /// <param name="y">Y の初期値</param> 
            Vector2(float x, float y) : X(x), Y(y) {}

            Vector2(const zephyr::linalg::Vector2& v)
                : X(v.x), Y(v.y)
            {
            }

            /// <summary>
            /// このベクトルを正規化して返します。
            /// </summary>
            Vector2 Normalize()
            {
                float oneOverMag = 1 / this->Magnitude;
                this->X *= oneOverMag;
                this->Y *= oneOverMag;
                return *this;
            }

            System::String^ ToString() override;

            /// <summary>
            /// ベクトルの大きさを返します。
            /// </summary>
            property float Magnitude { float get() { return sqrt(X*X + Y*Y); } };

            /// <summary>
            /// ベクトルの大きさの２乗を返します。
            /// </summary>
            property float SquaredMagnitude { float get() { return X*X + Y*Y; } };

            /// <summary>
            /// 正規化したベクトルを返します。
            /// </summary>
            /// <param name="v">正規化するベクトル。</param> 
            static Vector2 Normalize(Vector2 v)
            {
                return v.Normalize();
            }

            /// <summary>
            /// 文字列をベクトルに変換します。
            /// </summary>
            /// <param name="str">変換元の文字列。各要素は , で区切ること。</param> 
            static Vector2 Parse(System::String^ str);

            static Vector2 operator - (Vector2 a)
            {
                return Vector2(-a.X, -a.Y);
            }

            static Vector2 operator + (Vector2 a, Vector2 b)
            {
                return Vector2(a.X + b.X, a.Y + b.Y);
            }

            static Vector2 operator - (Vector2 a, Vector2 b)
            {
                return Vector2(a.X - b.X, a.Y - b.Y);
            }

            static Vector2 operator * (Vector2 v, float s)
            {
                return Vector2(v.X * s, v.Y * s);
            }

            static Vector2 operator * (float s, Vector2 v)
            {
                return Vector2(v.X * s, v.Y * s);
            }

            static Vector2 operator / (Vector2 v, float s)
            {
                return Vector2(v.X / s, v.Y / s);
            }

            /// <summary>
            /// ゼロベクトル。
            /// </summary>
            static const Vector2 Zero = Vector2(0, 0);

            float X, Y;

        public:

            property zephyr::linalg::Vector2 Native
            {
                zephyr::linalg::Vector2 get()
                {
                    return zephyr::linalg::Vector2(X, Y);
                }

                void set(zephyr::linalg::Vector2 v)
                {
                    X = v.x;
                    Y = v.y;
                }
            }
        };
    }
}
