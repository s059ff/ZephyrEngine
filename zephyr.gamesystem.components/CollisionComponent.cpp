#include <cmath>
#include <cfloat>

#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            void CollisionComponent::OnAttach()
            {
                s_colliders.insert(this);
            }

            void CollisionComponent::OnDetach()
            {
                s_colliders.erase(this);
            }

            void CollisionComponent::Update()
            {
                if (this->Shape == nullptr)
                    return;

                this->Shape->matrix = this->Owner->Get<TransformComponent>()->Matrix;
                if (this->Owner->Has<PhysicsComponent>())
                    this->Shape->velocity = this->Owner->Get<PhysicsComponent>()->Velocity;

                auto thisPosition = this->Owner->Get<TransformComponent>()->Position;

                if (this->Penetration)
                {
                    for each (CollisionComponent* other in s_colliders)
                    {
                        if (((this->OtherGroups & other->Group) != 0) && (this != other) && (other->Shape != nullptr))
                        {
                            if (this->Excludes.empty() || this->Excludes.find(other) == this->Excludes.end())
                            {
                                other->Shape->matrix = other->Owner->Get<TransformComponent>()->Matrix;
                                if (other->Owner->Has<PhysicsComponent>())
                                    other->Shape->velocity = other->Owner->Get<PhysicsComponent>()->Velocity;

                                linalg::Vector3 point = other->Shape->collide_point(this->Shape);
                                if (!isnan(point.x) && !isnan(point.y) && !isnan(point.z))
                                {
                                    this->Collided(other->Owner, point);
                                }
                            }
                        }
                    }
                }
                else
                {
                    Entity* collisionOther = nullptr;
                    linalg::Vector3 collisionPoint;
                    float minDistance = FLT_MAX;

                    for each (CollisionComponent* other in s_colliders)
                    {
                        if (((this->OtherGroups & other->Group) != 0) && (this != other) && (other->Shape != nullptr))
                        {
                            if (this->Excludes.empty() || this->Excludes.find(other) == this->Excludes.end())
                            {
                                other->Shape->matrix = other->Owner->Get<TransformComponent>()->Matrix;
                                if (other->Owner->Has<PhysicsComponent>())
                                    other->Shape->velocity = other->Owner->Get<PhysicsComponent>()->Velocity;

                                linalg::Vector3 point = other->Shape->collide_point(this->Shape);
                                if (!isnan(point.x) && !isnan(point.y) && !isnan(point.z))
                                {
                                    float distance = (thisPosition - point).squared_magnitude;
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
