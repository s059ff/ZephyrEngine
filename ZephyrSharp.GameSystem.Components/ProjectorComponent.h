#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// プロジェクターを表します。
            /// </summary>
            public ref class ProjectorComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// このクラスの新しいインスタンスを作成します。
                /// </summary>
                ProjectorComponent();

                /// <summary>
                /// 透視投影モードを設定します。
                /// </summary>
                /// <param name="fovY">視野角。</param> 
                /// <param name="aspect">投影領域のアスペクト比。</param> 
                /// <param name="zn">投影領域の Z Near 値。</param> 
                /// <param name="zf">投影領域の Z Far 値。</param> 
                void SetPerspectiveMode(float fovY, float aspect, float zn, float zf);

                /// <summary>
                /// 平行投影モードを設定します。
                /// </summary>
                /// <param name="width">投影領域の幅。</param> 
                /// <param name="height">投影領域の高さ。</param> 
                /// <param name="zn">投影領域の Z Near 値。</param> 
                /// <param name="zf">投影領域の Z Far 値。</param> 
                void SetOrthogonalMode(float width, float height, float zn, float zf);

                /// <summary>
                /// プロジェクション行列を取得します。
                /// </summary>
                Matrix4x4 ProjectionMatrix;
            };
        }
    }
}
