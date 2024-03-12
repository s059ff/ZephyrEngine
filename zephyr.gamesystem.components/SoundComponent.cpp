#include "zephyr\algorithm.h"
#include "zephyr.linalg\linalg.h"
#include "zephyr.gamesystem\Entity.h"

#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "SoundComponent.h"
#include "SoundObserverComponent.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            static double clamp(double x, double min, double max)
            {
                return x < min ? min : x > max ? max : x;
            }

            static double volume(double distance)
            {
                //return (distance > 0) ? clamp(SoundObserverComponent::Observer->EffectRange / distance, 0, 1) : 1;
                return clamp(0.1 * (1 - log(distance / SoundObserverComponent::Observer->EffectRange)), 0, 1);
            }

            static unsigned int frequency(double vo, double vs, unsigned int f0)
            {
                double k = (SoundObserverComponent::Observer->SonicSpeed - vo) / (SoundObserverComponent::Observer->SonicSpeed - vs);
                k = clamp(k, 0, 10);
                return (unsigned int)(k * f0);
            }

            static float div(linalg::Vector3 v, linalg::Vector3 n)
            {
                auto a = { abs(n.x), abs(n.y), abs(n.z) };
                auto x = std::max_element(a.begin(), a.end());
                auto i = (int)std::distance(a.begin(), x);
                switch (i)
                {
                case 0:
                    return v.x / n.x;
                case 1:
                    return v.y / n.y;
                case 2:
                    return v.z / n.z;
                default:
                    return 0;
                }
            }

            void SoundComponent::ReceiveMessage(const string& message, void* params[])
            {
                if (message == "update")
                {
                    this->Update();
                }
            }

            void SoundComponent::OnDestroy()
            {
                this->Sound.Stop();
                this->Sound.Release();
            }

            void SoundComponent::Update()
            {
                linalg::Vector3 po = SoundObserverComponent::Observer->Position;
                linalg::Vector3 vo = -SoundObserverComponent::Observer->Velocity;

                linalg::Vector3 ps = Owner->Get<TransformComponent>()->Position;
                linalg::Vector3 vs = linalg::Vector3::Zero;
                if (Owner->Has<PhysicsComponent>())
                    vs = Owner->Get<PhysicsComponent>()->Velocity;

                this->Sound.Volume = volume((po - ps).magnitude) * this->VolumeFactor;
                auto relative = (po - ps).normalize();
                if (relative.squared_magnitude > 0)
                {
                    auto _vs = project(vs, relative);
                    auto _vo = project(vo, relative);
                    this->Sound.Frequency = frequency(div(_vs, relative), div(_vo, relative), this->Sound.OriginalFrequency);
                }
                else
                {
                    this->Sound.Frequency = this->Sound.OriginalFrequency;
                }

                auto p = ps * SoundObserverComponent::Observer->Matrix.inverse;
                if (p.x != 0)
                {
                    p.normalize();
                    this->Sound.Pan = p.x;
                }
                else
                {
                    this->Sound.Pan = 0;
                }
            }
        }
    }
}
