#pragma once

#include "zephyr\runtime_assert.h"
#include "zephyr.linalg\linalg.h"

namespace zephyr
{
    namespace collision
    {
        class Box;
        class CurvedSurface;
        class Line;
        class LineSegment;
        class PlaneSurface;
        class Point;
        class Sphere;

        using Vector3 = linalg::Vector3;
        using Vector4 = linalg::Vector4;
        using Matrix4x3 = linalg::Matrix4x3;

        template <typename T1, typename T2>
        Vector3 CalculateCollisionPoint(const T1&, const Matrix4x3&, const T2&, const Matrix4x3&)
        {
            //runtime_assert(false, "Not implementation.");
            return Vector3(NAN, NAN, NAN);
        }

        template <typename T1, typename T2>
        Vector3 CalculateCollisionPoint(const T1&, const Matrix4x3&, const Vector3&, const T2&, const Matrix4x3&)
        {
            runtime_assert(false, "Not implementation.");
            return Vector3(NAN, NAN, NAN);
        }

        template <typename T1, typename T2>
        Vector3 CalculateCollisionPoint(const T1&, const Matrix4x3&, const T2&, const Matrix4x3&, const Vector3&)
        {
            runtime_assert(false, "Not implementation.");
            return Vector3(NAN, NAN, NAN);
        }

        template <typename T1, typename T2>
        Vector3 CalculateCollisionPoint(const T1&, const Matrix4x3&, const Vector3&, const T2&, const Matrix4x3&, const Vector3&)
        {
            runtime_assert(false, "Not implementation.");
            return Vector3(NAN, NAN, NAN);
        }

        template <> Vector3 CalculateCollisionPoint(const Line& obj1, const Matrix4x3& matrix1, const PlaneSurface& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const PlaneSurface& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const Sphere& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const Sphere& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const Box& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const CurvedSurface& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const CurvedSurface& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const CurvedSurface& obj2, const Matrix4x3& matrix2);
        
        template <> Vector3 CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const PlaneSurface& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2);

        template <> Vector3 CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Box& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const CurvedSurface& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const PlaneSurface& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2);

        template <> Vector3 CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Box& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const CurvedSurface& obj2, const Matrix4x3& matrix2);

        template <> Vector3 CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2);

        template <typename T1, typename T2>
        float CalculateCollisionTime(const T1&, const Matrix4x3&, const T2&, const Matrix4x3&)
        {
            //runtime_assert(false, "Not implementation.");
            return NAN;
        }

        template <typename T1, typename T2>
        float CalculateCollisionTime(const T1&, const Matrix4x3&, const Vector3&, const T2&, const Matrix4x3&)
        {
            runtime_assert(false, "Not implementation.");
            return NAN;
        }

        template <typename T1, typename T2>
        float CalculateCollisionTime(const T1&, const Matrix4x3&, const T2&, const Matrix4x3&, const Vector3&)
        {
            runtime_assert(false, "Not implementation.");
            return NAN;
        }

        template <typename T1, typename T2>
        float CalculateCollisionTime(const T1&, const Matrix4x3&, const Vector3&, const T2&, const Matrix4x3&, const Vector3&)
        {
            runtime_assert(false, "Not implementation.");
            return NAN;
        }

        template <> float CalculateCollisionTime(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2);

        template <> float CalculateCollisionTime(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2);

        float CalculateDistance(const Line& obj1, const Matrix4x3& matrix1, const Line& obj2, const Matrix4x3& matrix2);

        float CalculateDistance(const Point& point, const Matrix4x3& matrix1, const PlaneSurface& obj2, const Matrix4x3& matrix2);

        float CalculateHeight(const Vector3& point, const PlaneSurface& obj2, const Matrix4x3& matrix2);

        float CalculateHeight(const Vector3& point, const CurvedSurface& obj2, const Matrix4x3& matrix2);
    }
}
