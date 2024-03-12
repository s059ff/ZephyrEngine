#pragma once

#include "common.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture2D.h"
#include "VertexLayout.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// 頂点バッファやインデックスバッファをまとめる汎用グラフィックス リソースです。
        /// </summary>
        public ref class GraphicsModel
        {
            using Vector2 = ZephyrSharp::Linalg::Vector2;
            using Vector3 = ZephyrSharp::Linalg::Vector3;
            using Vector4 = ZephyrSharp::Linalg::Vector4;
            using Flags = System::FlagsAttribute;

        public:

            virtual ~GraphicsModel()
            {
                this->!GraphicsModel();
            }

            !GraphicsModel()
            {
                delete this->VertexPositions;
                this->VertexPositions = nullptr;

                delete this->VertexNormals;
                this->VertexNormals = nullptr;

                delete this->VertexTextureCoords;
                this->VertexTextureCoords = nullptr;

                delete this->VertexColors;
                this->VertexColors = nullptr;

                delete this->VertexTangents;
                this->VertexTangents = nullptr;

                delete this->VertexIndices;
                this->VertexIndices = nullptr;

                delete this->Texture;
                this->Texture = nullptr;

                delete this->NormalMap;
                this->NormalMap = nullptr;

                delete this->ChildModels;
                this->ChildModels = nullptr;
            }

            /// <summary>
            /// FBX ファイルから 3D モデルを作成します。
            /// </summary>
            /// <param name="path">ファイルパス。</param> 
            void CreateFromFBX(String^ path);

            /// <summary>
            /// 独自フォーマットのグラフィック モデルを読み込みます。
            /// </summary>
            /// <param name="path">ファイルパス。</param> 
            void CreateFromCX(String^ path);

            /// <summary>
            /// 直径 1 の球体モデルを作成します。モデルの頂点はインデックス付けされており、ローカル座標及び法線ベクトルを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            /// <param name="slices">主軸を回転軸としたスライスの数。</param>
            /// <param name="stacks">主軸に沿ったスタック数。</param>
            void CreateSphere(int slices, int stacks);

            /// <summary>
            /// 一片の長さが 1 の立方体モデルを生成します。モデルの頂点はインデックス付けされており、ローカル座標及び法線ベクトルを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            void CreateBox();

            /// <summary>
            /// 奥行 1、直径 1 の円柱モデルを生成します。生成される円柱モデルは、 Z 方向からみて円に見えるモデルになります。モデルの頂点はインデックス付けされており、位置及び法線ベクトルを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            /// <param name="slices">主軸を回転軸としたスライスの数。</param>
            void CreateCylinder(int slices, int stacks);

            /// <summary>
            /// トーラスモデルを生成します。モデルの頂点はインデックス付けされており、ローカル座標及び法線ベクトルを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            void CreateTorus();

            /// <summary>
            /// ティーポットモデルを生成します。モデルの頂点はインデックス付けされており、ローカル座標及び法線ベクトルを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            void CreateTeapot();

            /// <summary>
            /// 線分リストを生成します。モデルの頂点はインデックス付けされておらず、ローカル座標のみを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            /// <param name="positions">線分の始点の位置及び終点の位置の配列。配列の要素数は、２の倍数でなければならない。</param>
            void CreateLineList(array<Vector3>^ positions);

            /// <summary>
            /// 線分リストを生成します。モデルの頂点はインデックス付けされておらず、ローカル座標と頂点カラーを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            /// <param name="positions">線分の始点の位置及び終点の位置の配列。配列の要素数は、２の倍数でなければならない。</param>
            /// <param name="colors">各頂点の色を定義する頂点カラー。</param>
            void CreateLineList(array<Vector3>^ positions, array<Color>^ colors);

            /// <summary>
            /// 連続する一つの線分を生成します。モデルの頂点はインデックス付けされておらず、ローカル座標のみを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            /// <param name="positions">頂点の位置の配列。</param>
            void CreateLineStrip(array<Vector3>^ positions);

            /// <summary>
            /// 連続する一つの線分を生成します。モデルの頂点はインデックス付けされておらず、ローカル座標と頂点カラーを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            /// <param name="positions">節点の位置の配列。</param>
            /// <param name="colors">各頂点の色を定義する頂点カラー。</param>
            void CreateLineStrip(array<Vector3>^ positions, array<Color>^ colors);

            /// <summary>
            /// ビルボードモデルを生成します。モデルの頂点はインデックス付けされておらず、ローカル座標、法線ベクトル、テクスチャ座標、頂点カラーを持ちます。マテリアルおよびテクスチャは生成されません。
            /// </summary>
            void CreateBillBoard();

            /// <summary>
            /// メッシュマップ モデルを生成します。モデルの頂点はインデックス付けされており、ローカル座標、法線ベクトルを持ちます。マテリアルとテクスチャは設定されません。
            /// </summary>
            /// <param name="heights">グリッド状に区切ったメッシュマップの各頂点の高さ。行成分が Y 座標、列成分が X 座標に対応する。行と列の数は等しくなければならない。</param>
            void CreateMeshMap(array<float, 2>^ heights);

        private:

            void CreateFromCX(System::IO::Stream^ stream);

        public:

            /// <summary>
            /// 頂点座標。
            /// </summary>
            VertexBuffer<Vector3>^ VertexPositions = nullptr;

            /// <summary>
            /// 頂点の法線ベクトル。
            /// </summary>
            VertexBuffer<Vector3>^ VertexNormals = nullptr;

            /// <summary>
            /// 頂点のテクスチャ座標。
            /// </summary>
            VertexBuffer<Vector2>^ VertexTextureCoords = nullptr;

            /// <summary>
            /// 頂点の色。
            /// </summary>
            VertexBuffer<Color>^ VertexColors = nullptr;

            /// <summary>
            /// 頂点の Tangent。
            /// </summary>
            VertexBuffer<Vector3>^ VertexTangents = nullptr;

            /// <summary>
            /// 頂点の Binormal。
            /// </summary>
            VertexBuffer<Vector3>^ VertexBinormals = nullptr;

            /// <summary>
            /// 頂点インデックス。
            /// </summary>
            IndexBuffer^ VertexIndices = nullptr;

            /// <summary>
            /// テクスチャ。
            /// </summary>
            Texture2D^ Texture = nullptr;

            /// <summary>
            /// 法線マップテクスチャ。
            /// </summary>
            Texture2D^ NormalMap = nullptr;

            /// <summary>
            /// マテリアル情報。
            /// </summary>
            Material Material;

            /// <summary>
            /// プリミティブの構造。
            /// </summary>
            PrimitiveTopology Topology;

            /// <summary>
            /// 子モデル。
            /// </summary>
            array<GraphicsModel^>^ ChildModels = nullptr;
        };
    }
}
