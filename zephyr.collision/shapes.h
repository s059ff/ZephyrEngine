#pragma once

#include "zephyr\property.h"
#include "zephyr\matrix.h"
#include "zephyr.linalg\linalg.h"

namespace zephyr
{
    namespace collision
    {
        class AbstractShape abstract
        {
        protected:

            using Vector3 = linalg::Vector3;
            using Matrix4x3 = linalg::Matrix4x3;
        };

        /// <summary>
        /// 直方体を表します。
        /// </summary>
        class Box : public AbstractShape
        {
        public:

            /// <summary>
            /// 原点に位置し、各辺の長さが１の立方体として、新しいインスタンスを初期化します。
            /// </summary>
            Box()
            {
                this->lengthX = 1;
                this->lengthY = 1;
                this->lengthZ = 1;
            }

            /// <summary>
            /// 最小Ｘ境界座標を取得または設定します。
            /// </summary>
            float minX;

            /// <summary>
            /// 最小Ｙ境界座標を取得または設定します。
            /// </summary>
            float minY;

            /// <summary>
            /// 最小Ｚ境界座標を取得または設定します。
            /// </summary>
            float minZ;

            /// <summary>
            /// 最大Ｘ境界座標を取得または設定します。
            /// </summary>
            float maxX;

            /// <summary>
            /// 最大Ｙ境界座標を取得または設定します。
            /// </summary>
            float maxY;

            /// <summary>
            /// 最大Ｚ境界座標を取得または設定します。
            /// </summary>
            float maxZ;

            /// <summary>
            /// 幅を指定してX境界座標を設定します。もしくは幅を取得します。
            /// </summary>
            READWRITE_PROPERTY(float, lengthX, { return this->maxX - this->minX; }, { this->maxX = value / 2; this->minX = -value / 2; });

            /// <summary>
            /// 高さを指定してY境界座標を設定します。もしくは高さを取得します。
            /// </summary>
            READWRITE_PROPERTY(float, lengthY, { return this->maxY - this->minY; }, { this->maxY = value / 2; this->minY = -value / 2; });

            /// <summary>
            /// 奥行きを指定してZ境界座標を設定します。もしくは奥行きを取得します。
            /// </summary>
            READWRITE_PROPERTY(float, lengthZ, { return this->maxZ - this->minZ; }, { this->maxZ = value / 2; this->minZ = -value / 2; });
        };

        /// <summary>
        /// 直方体を構成する各辺が、XYZ軸に平行な直方体を表します。
        /// </summary>
        class AlignedBox : public Box
        {
        };

        /// <summary>
        /// 複数の頂点で構成されるメッシュ・マップを表します。
        /// </summary>
        class CurvedSurface : public AbstractShape
        {
        public:

            /// <summary>
            /// 曲面を構成する各頂点の高さを取得または設定します。
            /// </summary>
            matrix<float> heights;
        };

        /// <summary>
        /// 無限に伸びる直線を表します。
        /// </summary>
        class Line : public AbstractShape
        {
        public:

            /// <summary>
            /// 方向ベクトルを取得または設定します。
            /// </summary>
            Vector3 direction;
        };

        /// <summary>
        /// 線分を表します。
        /// </summary>
        class LineSegment : public AbstractShape
        {
        public:

            /// <summary>
            /// 開始位置を取得または設定します。
            /// </summary>
            Vector3 begin;

            /// <summary>
            /// 終端位置を取得または設定します。
            /// </summary>
            Vector3 end;

            /// <summary>
            /// 開始位置から終端位置への相対ベクトルを取得します。
            /// </summary>
            READONLY_PROPERTY(Vector3, direction, const{ return end - begin; });
        };

        /// <summary>
        /// 無限に広がる平面を表します。
        /// </summary>
        class PlaneSurface : public AbstractShape
        {
        public:

            /// <summary>
            /// 法線ベクトルを取得または設定します。法線ベクトルは正規化されている必要があります。
            /// </summary>
            Vector3 normal;
        };

        /// <summary>
        /// 点を表します。
        /// </summary>
        class Point : public AbstractShape {};

        /// <summary>
        /// 球体を表します。
        /// </summary>
        class Sphere : public AbstractShape
        {
        public:

            /// <summary>
            /// 半径を取得または設定します。
            /// </summary>
            float radius = 0.5f;

            /// <summary>
            /// 直径を取得または設定します。
            /// </summary>
            READWRITE_PROPERTY(float, diameter, { return this->radius * 2; }, { this->radius = value / 2; });
        };
    }
}
