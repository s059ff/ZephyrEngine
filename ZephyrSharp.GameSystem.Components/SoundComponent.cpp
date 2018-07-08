#include "zephyr\algorithm.h"

#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "SoundComponent.h"
#include "SoundObserverComponent.h"

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
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

            static float div(Vector3 v, Vector3 n)
            {
                auto a = { abs(n.X), abs(n.Y), abs(n.Z) };
                auto x = std::max_element(a.begin(), a.end());
                auto i = (int)std::distance(a.begin(), x);
                switch (i)
                {
                case 0:
                    return v.X / n.X;
                case 1:
                    return v.Y / n.Y;
                case 2:
                    return v.Z / n.Z;
                default:
                    return 0;
                }
            }

            void SoundComponent::ReceiveMessage(System::Object^ message, System::Object^ argument)
            {
                if (message == "update")
                {
                    this->Update();
                }
            }

            void SoundComponent::OnDestroy()
            {
                this->Sound->Stop();
                this->Sound->Release();
            }

            void SoundComponent::Update()
            {
                Vector3 po = SoundObserverComponent::Observer->Position;
                Vector3 vo = -SoundObserverComponent::Observer->Velocity;

                Vector3 ps = Owner->Get<TransformComponent^>()->Position;
                Vector3 vs = Vector3::Zero;
                if (Owner->Has<PhysicsComponent^>())
                    vs = Owner->Get<PhysicsComponent^>()->Velocity;

                this->Sound->Volume = volume(Vector3::operator-(po, ps).Magnitude) * this->VolumeFactor;
                Vector3 relative = Vector3::operator-(po, ps).Normalize();
                if (relative.SquaredMagnitude > 0)
                {
                    Vector3 _vs = Vector3::Project(vs, relative);
                    Vector3 _vo = Vector3::Project(vo, relative);
                    this->Sound->Frequency = frequency(div(_vs, relative), div(_vo, relative), this->Sound->OriginalFrequency);
                }
                else
                {
                    this->Sound->Frequency = this->Sound->OriginalFrequency;
                }

                Vector3 p = ps * SoundObserverComponent::Observer->Matrix.Inverse;
                if (p.X != 0)
                {
                    p.Normalize();
                    this->Sound->Pan = p.X;
                }
                else
                {
                    this->Sound->Pan = 0;
                }
            }
        }
    }
}
