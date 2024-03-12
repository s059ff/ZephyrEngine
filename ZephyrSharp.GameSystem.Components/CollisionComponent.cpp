#include <cmath>
#include <cfloat>

#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            void CollisionComponent::OnAttach()
            {
                s_colliders->AddFirst(this);
            }

            void CollisionComponent::OnDetach()
            {
                s_colliders->Remove(this);
            }

            void CollisionComponent::Update()
            {
                if (this->Object == nullptr)
                    return;

                this->Object->Matrix = this->Owner->Get<TransformComponent^>()->Matrix;
                if (this->Owner->Has<PhysicsComponent^>())
                    this->Object->Velocity = this->Owner->Get<PhysicsComponent^>()->Velocity;

                Vector3 thisPosition = this->Owner->Get<TransformComponent^>()->Position;

                if (this->Penetration)
                {
                    for each (CollisionComponent^ other in s_colliders)
                    {
                        if (((this->OtherGroups & other->Group) != 0) && (this != other) && (other->Object != nullptr))
                        {
                            if (this->Excludes == nullptr || !System::Linq::Enumerable::Contains(this->Excludes, other))
                            {
                                other->Object->Matrix = other->Owner->Get<TransformComponent^>()->Matrix;
                                if (other->Owner->Has<PhysicsComponent^>())
                                    other->Object->Velocity = other->Owner->Get<PhysicsComponent^>()->Velocity;

                                Vector3 point = other->Object->CollidePoint(this->Object);
                                if (!isnan(point.X) && !isnan(point.Y) && !isnan(point.Z))
                                {
                                    this->Collided(other->Owner, point);
                                }
                            }
                        }
                    }
                }
                else
                {
                    Entity^ collisionOther = nullptr;
                    Vector3 collisionPoint;
                    float minDistance = FLT_MAX;

                    for each (CollisionComponent^ other in s_colliders)
                    {
                        if (((this->OtherGroups & other->Group) != 0) && (this != other) && (other->Object != nullptr))
                        {
                            if (this->Excludes == nullptr || !System::Linq::Enumerable::Contains(this->Excludes, other))
                            {
                                other->Object->Matrix = other->Owner->Get<TransformComponent^>()->Matrix;
                                if (other->Owner->Has<PhysicsComponent^>())
                                    other->Object->Velocity = other->Owner->Get<PhysicsComponent^>()->Velocity;

                                Vector3 point = other->Object->CollidePoint(this->Object);
                                if (!isnan(point.X) && !isnan(point.Y) && !isnan(point.Z))
                                {
                                    float distance = Vector3::operator-(thisPosition, point).SquaredMagnitude;
                                    if (distance < minDistance)
                                    {
                                        collisionOther = other->Owner;
                                        collisionPoint = point;
                                        minDistance = distance;
                                    }
                                }
                            }
                        }
                    }

                    if (collisionOther != nullptr)
                    {
                        this->Collided(collisionOther, collisionPoint);
                    }
                }
            }
        }
    }
}
