#pragma once

#include "zephyr\assert.h"
#include "zephyr.linalg\Matrix4x3.h"
#include "zephyr.linalg\Vector3.h"
#include "collision.h"
#include "shapes.h"

namespace zephyr
{
    namespace collision
    {
        template <typename Shape> class CollisionObject;

        template <typename Shape1, typename Shape2>
        inline static Vector3 CalculateCollisionPoint(const CollisionObject<Shape1>* obj1, const CollisionObject<Shape2>* obj2)
        {
            auto& shape1 = obj1->shape;
            auto& shape2 = obj2->shape;
            auto& matrix1 = obj1->matrix;
            auto& matrix2 = obj2->matrix;
            auto& velocity1 = obj1->velocity;
            auto& velocity2 = obj2->velocity;
            bool obj1moving = obj1->velocity.squared_magnitude > 0;
            bool obj2moving = obj2->velocity.squared_magnitude > 0;

            if (obj1moving && obj2moving)
                return CalculateCollisionPoint(shape1, matrix1, velocity1, shape2, matrix2, velocity2);

            if (obj1moving && !obj2moving)
                return CalculateCollisionPoint(shape1, matrix1, velocity1, shape2, matrix2);

            if (!obj1moving && obj2moving)
                return CalculateCollisionPoint(shape1, matrix1, shape2, matrix2, velocity2);

            if (!obj1moving && !obj2moving)
                return CalculateCollisionPoint(shape1, matrix1, shape2, matrix2);
        }

        template <typename Shape1, typename Shape2>
        inline static float CalculateCollisionTime(const CollisionObject<Shape1>* obj1, const CollisionObject<Shape2>* obj2)
        {
            auto& shape1 = obj1->shape;
            auto& shape2 = obj2->shape;
            auto& matrix1 = obj1->matrix;
            auto& matrix2 = obj2->matrix;
            auto& velocity1 = obj1->velocity;
            auto& velocity2 = obj2->velocity;
            bool obj1moving = obj1->velocity.squared_magnitude > 0;
            bool obj2moving = obj2->velocity.squared_magnitude > 0;

            if (obj1moving && obj2moving)
                return CalculateCollisionTime(shape1, matrix1, velocity1, shape2, matrix2, velocity2);

            if (obj1moving && !obj2moving)
                return CalculateCollisionTime(shape1, matrix1, velocity1, shape2, matrix2);

            if (!obj1moving && obj2moving)
                return CalculateCollisionTime(shape1, matrix1, shape2, matrix2, velocity2);

            if (!obj1moving && !obj2moving)
                return CalculateCollisionTime(shape1, matrix1, shape2, matrix2);
        }

        class AbstractCollisionObject
        {
        public:

            Matrix4x3 matrix;

            Vector3 velocity;

        public:

            virtual Vector3 collide_point(const AbstractCollisionObject* other) const
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 collide_point(const CollisionObject<Box>* other) const
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 collide_point(const CollisionObject<Line>* other) const
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 collide_point(const CollisionObject<LineSegment>* other) const
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 collide_point(const CollisionObject<PlaneSurface>* other) const
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 collide_point(const CollisionObject<CurvedSurface>* other) const
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 collide_point(const CollisionObject<Sphere>* other) const
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual float collide_time(const AbstractCollisionObject* other) const
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float collide_time(const CollisionObject<Box>* other) const
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float collide_time(const CollisionObject<Line>* other) const
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float collide_time(const CollisionObject<LineSegment>* other) const
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float collide_time(const CollisionObject<PlaneSurface>* other) const
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float collide_time(const CollisionObject<CurvedSurface>* other) const
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float collide_time(const CollisionObject<Sphere>* other) const
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }
        };

        template <typename Shape>
        class CollisionObject : public AbstractCollisionObject
        {
        public:

            Shape shape;

        public:

            virtual Vector3 collide_point(const AbstractCollisionObject* other) const
            {
                return other->collide_point(this);
            }

            virtual Vector3 collide_point(const CollisionObject<Box>* other) const
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 collide_point(const CollisionObject<Line>* other) const
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 collide_point(const CollisionObject<LineSegment>* other) const
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 collide_point(const CollisionObject<PlaneSurface>* other) const
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 collide_point(const CollisionObject<CurvedSurface>* other) const
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 collide_point(const CollisionObject<Sphere>* other) const
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual float collide_time(const AbstractCollisionObject* other) const
            {
                return other->collide_time(this);
            }

            virtual float collide_time(const CollisionObject<Box>* other) const
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float collide_time(const CollisionObject<Line>* other) const
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float collide_time(const CollisionObject<LineSegment>* other) const
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float collide_time(const CollisionObject<PlaneSurface>* other) const
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float collide_time(const CollisionObject<CurvedSurface>* other) const
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float collide_time(const CollisionObject<Sphere>* other) const
            {
                return CalculateCollisionTime(this, other);
            }
        };
    }
}
