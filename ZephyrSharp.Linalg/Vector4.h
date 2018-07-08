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
        /// 四次元同次ベクトルを表します。
        /// </summary>
        public value class Vector4
        {
        public:

            /// <summary>
            /// 全成分の値を個別に指定してベクトルを作成します。
            /// </summary>
            /// <param name="v">X, Y, Z の初期値</param> 
            /// <param name="w">W の初期値</param> 
            Vector4(Vector3 v, float w) : X(v.X), Y(v.Y), Z(v.Z), W(w) {}

            /// <summary>
            /// 全成分の値を個別に指定してベクトルを作成します。
            /// </summary>
            /// <param name="x">X の初期値</param> 
            /// <param name="y">Y の初期値</param> 
            /// <param name="z">Z の初期値</param> 
            /// <param name="w">W の初期値</param> 
            Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

            Vector4(const zephyr::linalg::Vector4& v)
                : X(v.x), Y(v.y), Z(v.z), W(v.w)
            {
            }

            System::String^ ToString() override;

            /// <summary>
            /// 文字列をベクトルに変換します。
            /// </summary>
            /// <param name="str">変換元の文字列。各要素は , で区切ること。</param> 
            static Vector4 Parse(System::String^ str);

            /// <summary>
            /// ゼロベクトル。
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
