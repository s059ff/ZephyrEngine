#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Collision
    {
        /// <summary>
        /// 直方体を表します。
        /// </summary>
        public ref class Box : public INativeWrapper<zephyr::collision::Box>
        {
        public:

            /// <summary>
            /// 最小Ｘ境界座標を取得または設定します。
            /// </summary>
            property float MinX
            {
                float get() { return Native->minX; }
                void set(float value) { Native->minX = value; }
            }

            /// <summary>
            /// 最小Ｙ境界座標を取得または設定します。
            /// </summary>
            property float MinY
            {
                float get() { return Native->minY; }
                void set(float value) { Native->minY = value; }
            }

            /// <summary>
            /// 最小Ｚ境界座標を取得または設定します。
            /// </summary>
            property float MinZ
            {
                float get() { return Native->minZ; }
                void set(float value) { Native->minZ = value; }
            }

            /// <summary>
            /// 最大Ｘ境界座標を取得または設定します。
            /// </summary>
            property float MaxX
            {
                float get() { return Native->maxX; }
                void set(float value) { Native->maxX = value; }
            }

            /// <summary>
            /// 最大Ｙ境界座標を取得または設定します。
            /// </summary>
            property float MaxY
            {
                float get() { return Native->maxY; }
                void set(float value) { Native->maxY = value; }
            }

            /// <summary>
            /// 最大Ｚ境界座標を取得または設定します。
            /// </summary>
            property float MaxZ
            {
                float get() { return Native->maxZ; }
                void set(float value) { Native->maxZ = value; }
            }

            /// <summary>
            /// 幅を指定してX境界座標を設定します。もしくは幅を取得します。
            /// </summary>
            property float LengthX
            {
                float get() { return Native->lengthX; }
                void set(float value) { Native->lengthX = value; }
            }

            /// <summary>
            /// 高さを指定してY境界座標を設定します。もしくは高さを取得します。
            /// </summary>
            property float LengthY
            {
                float get() { return Native->lengthY; }
                void set(float value) { Native->lengthY = value; }
            }

            /// <summary>
            /// 奥行きを指定してZ境界座標を設定します。もしくは奥行きを取得します。
            /// </summary>
            property float LengthZ
            {
                float get() { return Native->lengthZ; }
                void set(float value) { Native->lengthZ = value; }
            }
        };

        /// <summary>
        /// 直方体を構成する各辺が、XYZ軸に平行な直方体を表します。
        /// </summary>
        public ref class AlignedBox : public Box
        {
        };

        /// <summary>
        /// 曲面を表します。
        /// </summary>
        public ref class CurvedSurface : public INativeWrapper<zephyr::collision::CurvedSurface>
        {
        public:

            /// <summary>
            /// 各頂点の高さを設定します。
            /// </summary>
            property array<float, 2>^ Heights
            {
                void set(array<float, 2>^ value)
                {
                    Native->heights.resize(value->GetLength(0), value->GetLength(1));
                    pin_ptr<float> ptr = &value[0, 0];
                    Native->heights.copy_from(ptr);
                }
            }
        };

        /// <summary>
        /// 無限に伸びる直線を表します。
        /// </summary>
        public ref class Line : public INativeWrapper<zephyr::collision::Line>
        {
        public:

            /// <summary>
            /// 方向ベクトルを取得または設定します。
            /// </summary>
            property ZephyrSharp::Linalg::Vector3 Direction
            {
                ZephyrSharp::Linalg::Vector3 get()
                {
                    return reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->direction);
                }

                void set(ZephyrSharp::Linalg::Vector3 value)
                {
                    reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->direction) = value;
                }
            }
        };

        /// <summary>
        /// 線分を表します。
        /// </summary>
        public ref class LineSegment : public INativeWrapper<zephyr::collision::LineSegment>
        {
        public:

            /// <summary>
            /// 方向ベクトルを取得または設定します。
            /// </summary>
            property ZephyrSharp::Linalg::Vector3 Direction
            {
                ZephyrSharp::Linalg::Vector3 get()
                {
                    return reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->direction);
                }
            }
        };

        /// <summary>
        /// 無限に広がる平面を表します。
        /// </summary>
        public ref class PlaneSurface : public INativeWrapper<zephyr::collision::PlaneSurface>
        {
        public:

            /// <summary>
            /// 法線ベクトルを取得または設定します。法線ベクトルは正規化されている必要があります。
            /// </summary>
            property ZephyrSharp::Linalg::Vector3 Normal
            {
                ZephyrSharp::Linalg::Vector3 get()
                {
                    return reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->normal);
                }

                void set(ZephyrSharp::Linalg::Vector3 value)
                {
                    reinterpret_cast<ZephyrSharp::Linalg::Vector3%>(Native->normal) = value;
                }
            }
        };

        /// <summary>
        /// 点を表します。
        /// </summary>
        public ref class Point : public INativeWrapper<zephyr::collision::Point>
        {
        };

        /// <summary>
        /// 球体を表します。
        /// </summary>
        public ref class Sphere : public INativeWrapper<zephyr::collision::Sphere>
        {
        public:

            /// <summary>
            /// 半径を取得または設定します。
            /// </summary>
            property float Radius
            {
                float get() { return Native->radius; }
                void set(float value) { Native->radius = value; }
            }

            /// <summary>
            /// 直径を取得または設定します。
            /// </summary>
            property float Diameter
            {
                float get() { return Native->diameter; }
                void set(float value) { Native->diameter = value; }
            }
        };
    }
}
