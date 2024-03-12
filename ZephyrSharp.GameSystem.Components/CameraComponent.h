#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// カメラを表します。
            /// </summary>
            public ref class CameraComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ある地点から別のある地点を注視するようにカメラの向きを設定します。
                /// </summary>
                /// <param name="eye">カメラの座標。</param> 
                /// <param name="at">注視先の座標。</param> 
                void LookAt(Vector3 eye, Vector3 at);

                /// <summary>
                /// ビューイング行列を取得します。
                /// </summary>
                property Matrix4x3 ViewingMatrix { Matrix4x3 get(); }
            };
        }
    }
}
