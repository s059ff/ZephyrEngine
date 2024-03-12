#pragma once

#include "common.h"
#include "shapes.h"

namespace ZephyrSharp
{
    namespace Collision
    {
        using ZephyrSharp::Linalg::Matrix4x3;
        using ZephyrSharp::Linalg::Vector3;

        template <typename Shape> ref class CollisionObject;

        template <typename Shape1, typename Shape2>
        inline static Vector3 CalculateCollisionPoint(CollisionObject<Shape1>^ obj1, CollisionObject<Shape2>^ obj2)
        {
            auto& shape1 = obj1->Shape->NativeRef;
            auto& shape2 = obj2->Shape->NativeRef;
            auto& matrix1 = reinterpret_cast<zephyr::linalg::Matrix4x3&>(obj1->Matrix);
            auto& matrix2 = reinterpret_cast<zephyr::linalg::Matrix4x3&>(obj2->Matrix);
            auto& velocity1 = reinterpret_cast<zephyr::linalg::Vector3&>(obj1->Velocity);
            auto& velocity2 = reinterpret_cast<zephyr::linalg::Vector3&>(obj2->Velocity);
            bool obj1moving = obj1->Velocity.SquaredMagnitude > 0;
            bool obj2moving = obj2->Velocity.SquaredMagnitude > 0;

            if (obj1moving && obj2moving)
                return reinterpret_cast<Vector3%>(zephyr::collision::CalculateCollisionPoint(shape1, matrix1, velocity1, shape2, matrix2, velocity2));

            if (obj1moving && !obj2moving)
                return reinterpret_cast<Vector3%>(zephyr::collision::CalculateCollisionPoint(shape1, matrix1, velocity1, shape2, matrix2));

            if (!obj1moving && obj2moving)
                return reinterpret_cast<Vector3%>(zephyr::collision::CalculateCollisionPoint(shape1, matrix1, shape2, matrix2, velocity2));

            if (!obj1moving && !obj2moving)
                return reinterpret_cast<Vector3%>(zephyr::collision::CalculateCollisionPoint(shape1, matrix1, shape2, matrix2));
        }

        template <typename Shape1, typename Shape2>
        inline static float CalculateCollisionTime(CollisionObject<Shape1>^ obj1, CollisionObject<Shape2>^ obj2)
        {
            auto& shape1 = obj1->Shape->NativeRef;
            auto& shape2 = obj2->Shape->NativeRef;
            auto& matrix1 = reinterpret_cast<zephyr::linalg::Matrix4x3&>(obj1->Matrix);
            auto& matrix2 = reinterpret_cast<zephyr::linalg::Matrix4x3&>(obj2->Matrix);
            auto& velocity1 = reinterpret_cast<zephyr::linalg::Vector3&>(obj1->Velocity);
            auto& velocity2 = reinterpret_cast<zephyr::linalg::Vector3&>(obj2->Velocity);
            bool obj1moving = obj1->Velocity.SquaredMagnitude > 0;
            bool obj2moving = obj2->Velocity.SquaredMagnitude > 0;

            if (obj1moving && obj2moving)
                return zephyr::collision::CalculateCollisionTime(shape1, matrix1, velocity1, shape2, matrix2, velocity2);

            if (obj1moving && !obj2moving)
                return zephyr::collision::CalculateCollisionTime(shape1, matrix1, velocity1, shape2, matrix2);

            if (!obj1moving && obj2moving)
                return zephyr::collision::CalculateCollisionTime(shape1, matrix1, shape2, matrix2, velocity2);

            if (!obj1moving && !obj2moving)
                return zephyr::collision::CalculateCollisionTime(shape1, matrix1, shape2, matrix2);
        }

        public ref class AbstractCollisionObject
        {
        public:

            Matrix4x3 Matrix;

            Vector3 Velocity;

        public:

            virtual Vector3 CollidePoint(AbstractCollisionObject^ other)
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 CollidePoint(CollisionObject<Box>^ other)
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 CollidePoint(CollisionObject<Line>^ other)
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 CollidePoint(CollisionObject<LineSegment>^ other)
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 CollidePoint(CollisionObject<PlaneSurface>^ other)
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 CollidePoint(CollisionObject<CurvedSurface>^ other)
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 CollidePoint(CollisionObject<Point>^ other)
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual Vector3 CollidePoint(CollisionObject<Sphere>^ other)
            {
                assert(false, "Not implementation.");
                return Vector3();
            }

            virtual float CollideTime(AbstractCollisionObject^ other)
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float CollideTime(CollisionObject<Box>^ other)
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float CollideTime(CollisionObject<Line>^ other)
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float CollideTime(CollisionObject<LineSegment>^ other)
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float CollideTime(CollisionObject<PlaneSurface>^ other)
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float CollideTime(CollisionObject<CurvedSurface>^ other)
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float CollideTime(CollisionObject<Point>^ other)
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }

            virtual float CollideTime(CollisionObject<Sphere>^ other)
            {
                assert(false, "Not implementation.");
                return 0.0f;
            }
        };

        template <typename ShapeType>
        public ref class CollisionObject : public AbstractCollisionObject
        {
        public:

            ShapeType^ Shape = gcnew ShapeType();

        public:

            virtual Vector3 CollidePoint(AbstractCollisionObject^ other) override
            {
                return other->CollidePoint(this);
            }

            virtual Vector3 CollidePoint(CollisionObject<Box>^ other) override
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 CollidePoint(CollisionObject<Line>^ other) override
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 CollidePoint(CollisionObject<LineSegment>^ other) override
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 CollidePoint(CollisionObject<PlaneSurface>^ other) override
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 CollidePoint(CollisionObject<CurvedSurface>^ other) override
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 CollidePoint(CollisionObject<Point>^ other) override
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual Vector3 CollidePoint(CollisionObject<Sphere>^ other) override
            {
                return CalculateCollisionPoint(this, other);
            }

            virtual float CollideTime(AbstractCollisionObject^ other) override
            {
                return other->CollideTime(this);
            }

            virtual float CollideTime(CollisionObject<Box>^ other) override
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float CollideTime(CollisionObject<Line>^ other) override
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float CollideTime(CollisionObject<LineSegment>^ other) override
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float CollideTime(CollisionObject<PlaneSurface>^ other) override
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float CollideTime(CollisionObject<CurvedSurface>^ other) override
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float CollideTime(CollisionObject<Point>^ other) override
            {
                return CalculateCollisionTime(this, other);
            }

            virtual float CollideTime(CollisionObject<Sphere>^ other) override
            {
                return CalculateCollisionTime(this, other);
            }
        };

        public ref class BoxCollisionObject : public CollisionObject<Box>
        {
        public:

            BoxCollisionObject() {}

            BoxCollisionObject(Box^ shape)
            {
                this->Shape = shape;
            }
        };

        public ref class LineCollisionObject : public CollisionObject<Line>
        {
        public:

            LineCollisionObject() {}

            LineCollisionObject(Line^ shape)
            {
                this->Shape = shape;
            }
        };

        public ref class LineSegmentCollisionObject : public CollisionObject<LineSegment>
        {
        public:

            LineSegmentCollisionObject() {}

            LineSegmentCollisionObject(LineSegment^ shape)
            {
                this->Shape = shape;
            }
        };

        public ref class PlaneSurfaceCollisionObject : public CollisionObject<PlaneSurface>
        {
        public:

            PlaneSurfaceCollisionObject() {}

            PlaneSurfaceCollisionObject(PlaneSurface^ shape)
            {
                this->Shape = shape;
            }

            float ComputeHeight(Vector3 point)
            {
                auto _point = reinterpret_cast<zephyr::linalg::Vector3&>(point);
                auto _matrix = reinterpret_cast<zephyr::linalg::Matrix4x3&>(Matrix);
                return zephyr::collision::CalculateHeight(_point, Shape->NativeRef, _matrix);
            }
        };

        public ref class CurvedSurfaceCollisionObject : public CollisionObject<CurvedSurface>
        {
        public:

            CurvedSurfaceCollisionObject() {}

            CurvedSurfaceCollisionObject(CurvedSurface^ shape)
            {
                this->Shape = shape;
            }

            float ComputeHeight(Vector3 point)
            {
                auto _point = reinterpret_cast<zephyr::linalg::Vector3&>(point);
                auto _matrix = reinterpret_cast<zephyr::linalg::Matrix4x3&>(Matrix);
                return zephyr::collision::CalculateHeight(_point, Shape->NativeRef, _matrix);
            }
        };

        public ref class PointCollisionObject : public CollisionObject<Point>
        {
        public:

            PointCollisionObject() {}

            PointCollisionObject(Point^ shape)
            {
                this->Shape = shape;
            }
        };

        public ref class SphereCollisionObject : public CollisionObject<Sphere>
        {
        public:

            SphereCollisionObject() {}

            SphereCollisionObject(Sphere^ shape)
            {
                this->Shape = shape;
            }
        };
    }
}
