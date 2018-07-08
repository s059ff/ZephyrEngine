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
            /// 3D �T�E���h�̊ϑ��҂�\���܂��B
            /// </summary>
            class SoundObserverComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// �T�E���h�̌��ʔ͈͂��擾�܂��͐ݒ肵�܂��B
                /// </summary>
                double EffectRange;

                /// <summary>
                /// �������擾�܂��͐ݒ肵�܂��B
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
