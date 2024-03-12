#pragma once

#include "zephyr.linalg\Quaternion.h"

#include "common.h"
#include "Vector3.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        value class Matrix3x3;

        /// <summary>
        /// 任意の軸周りの回転を表します。
        /// </summary>
        public value class Quaternion
        {
        public:

            /// <summary>
            /// 任意の軸周りの回転を表すクォータニオンを作成します。
            /// </summary>
            /// <param name="axis">回転軸。</param> 
            /// <param name="theta">回転量。ラジアンで指定。</param> 
            Quaternion(Vector3 axis, float theta)
            {
                zephyr::linalg::Vector3 _a(axis.Native);
                zephyr::linalg::Quaternion _q(_a, theta);
                reinterpret_cast<zephyr::linalg::Quaternion&>(*this) = _q;
            }

            /// <summary>
            /// 回転行列をクォータニオンに変換します。
            /// </summary>
            /// <param name="matrix">回転行列。</param> 
            Quaternion(Matrix3x3 matrix);

            /// <summary>
            /// 三次元上の点をクォータニオンに拡張します。
            /// </summary>
            /// <param name="point">三次元上の点。</param> 
            Quaternion(Vector3 point)
            {
                zephyr::linalg::Vector3 _p(point.Native);
                zephyr::linalg::Quaternion _q(_p);
                reinterpret_cast<zephyr::linalg::Quaternion&>(*this) = _q;
            }

            /// <summary>
            /// 恒等変換を表すクォータニオンにして返します。
            /// </summary>
            Quaternion Identity()
            {
                reinterpret_cast<zephyr::linalg::Quaternion&>(*this).identity();
                return *this;
            }

            /// <summary>
            /// クォータニオンを正規化して返します。
            /// </summary>
            Quaternion Normalize()
            {
                reinterpret_cast<zephyr::linalg::Quaternion&>(*this).normalize();
                return *this;
            }

            /// <summary>
            /// クォータニオンの内積を返します。
            /// </summary>
            /// <param name="q1">演算対象のクォータニオン。</param> 
            /// <param name="q2">演算対象のクォータニオン。</param> 
            static float Inner(Quaternion q1, Quaternion q2)
            {
                auto& _q1 = reinterpret_cast<zephyr::linalg::Quaternion&>(q1);
                auto& _q2 = reinterpret_cast<zephyr::linalg::Quaternion&>(q2);

                return zephyr::linalg::inner(_q1, _q2);
            }

            /// <summary>
            /// 二つのクォータニオンを補間するクォータニオンを返します。
            /// </summary>
            /// <param name="q0">演算対象のクォータニオン。</param> 
            /// <param name="q1">演算対象のクォータニオン。</param> 
            /// <param name="t">q0 から q1 に近づける割合。</param> 
            static Quaternion Slerp(Quaternion q0, Quaternion q1, float t)
            {
                auto& _q0 = reinterpret_cast<zephyr::linalg::Quaternion&>(q0);
                auto& _q1 = reinterpret_cast<zephyr::linalg::Quaternion&>(q1);
                auto& _q2 = zephyr::linalg::slerp(_q0, _q1, t);

                return reinterpret_cast<Quaternion&>(_q2);
            }

            /// <summary>
            /// クォータニオンのべき乗を計算します。
            /// </summary>
            /// <param name="q">演算対象のクォータニオン。</param> 
            /// <param name="t">回転の割合。 t = 0 のとき、恒等クォータニオン、 t = 1 のとき、もとのクォータニオンと同じ。</param> 
            static Quaternion Pow(Quaternion q, float t)
            {
                auto& _q = reinterpret_cast<zephyr::linalg::Quaternion&>(q);
                auto& _q2 = zephyr::linalg::pow(_q, t);

                return reinterpret_cast<Quaternion&>(_q2);
            }

            /// <summary>
            /// クォータニオンの共役を計算します。
            /// </summary>
            /// <param name="q">演算対象のクォータニオン。</param> 
            static Quaternion operator -(Quaternion q)
            {
                auto _q = -reinterpret_cast<zephyr::linalg::Quaternion&>(q);
                return reinterpret_cast<Quaternion&>(_q);
            }

            /// <summary>
            /// クォータニオンの外積を計算します。
            /// </summary>
            /// <param name="q1">演算対象のクォータニオン。</param> 
            /// <param name="q2">演算対象のクォータニオン。</param> 
            static Quaternion operator *(Quaternion q1, Quaternion q2)
            {
                auto& _q1 = reinterpret_cast<zephyr::linalg::Quaternion&>(q1);
                auto& _q2 = reinterpret_cast<zephyr::linalg::Quaternion&>(q2);
                auto& _q3 = zephyr::linalg::mul(_q1, _q2);

                return reinterpret_cast<Quaternion&>(_q3);
            }

            /// <summary>
            /// このクォータニオンが表す回転の回転軸を取得します。
            /// </summary>
            property Vector3 Axis { Vector3 get() { return reinterpret_cast<Vector3&>(reinterpret_cast<zephyr::linalg::Quaternion&>(*this).axis); }}

            /// <summary>
            /// このクォータニオンが表す回転の回転角を取得します。
            /// </summary>
            property float Theta { float get() { return reinterpret_cast<zephyr::linalg::Quaternion&>(*this).theta; }}

        public:

            float X, Y, Z, W;
        };
    }
}
