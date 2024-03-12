#pragma once

#include "zephyr\property.h"
#include "zephyr.linalg\Vector3.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            /// <summary>
            /// 3D サウンドの観測者を表します。
            /// </summary>
            class SoundObserverComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// サウンドの効果範囲を取得または設定します。
                /// </summary>
                double EffectRange;

                /// <summary>
                /// 音速を取得または設定します。
                /// </summary>
                double SonicSpeed;

                static SoundObserverComponent* Observer;

                linalg::Vector3 Position;

                linalg::Vector3 Velocity;

                linalg::Matrix4x3 Matrix;

            public:

                virtual void OnAttach() override;

                virtual void ReceiveMessage(const string& message, void* params[]) override;

            private:

                void Update();
            };
        }
    }
}
