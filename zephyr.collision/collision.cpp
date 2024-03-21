#include "zephyr\algorithm.h"
#include "zephyr\tuple.h"
#include "zephyr.linalg\Vector3.h"
#include "zephyr.linalg\Vector4.h"
#include "zephyr.linalg\Matrix4x3.h"
#include "zephyr.linalg\linalg.h"

#include "collision.h"
#include "shapes.h"

using namespace zephyr;
using namespace zephyr::linalg;

static const Vector3 NANVector = Vector3(NAN, NAN, NAN);

static bool nearly0(float value)
{
    return abs(value) < 0.0001f;
}

static bool collided(const Vector3& v)
{
    return !isnan(v.x + v.y + v.z);
}

static bool collided(float time)
{
    return !isnan(time) && (0 <= time) && (time <= 1);
}

static Vector3 CollisionPoint_Line_PlaneSurface(
    Vector3 line_start,
    Vector3 line_direction,
    Vector3 plane_point,
    Vector3 plane_normal)
{
    if (nearly0(inner(plane_normal, line_direction)))
    {
        return NANVector;
    }

    auto nx = plane_normal.x;
    auto ny = plane_normal.y;
    auto nz = plane_normal.z;
    auto d = -inner(plane_normal, plane_point);
    auto x0 = plane_point.x;
    auto y0 = plane_point.y;
    auto z0 = plane_point.z;

    auto x1 = line_start.x;
    auto y1 = line_start.y;
    auto z1 = line_start.z;
    auto dx = line_direction.x;
    auto dy = line_direction.y;
    auto dz = line_direction.z;

    auto t = -(nx * (x1 - x0) + ny * (y1 - y0) + nz * (z1 - z0) + d) / (nx * dx + ny * dy + nz * dz);

    return Vector3(x1 + dx * t, y1 + dy * t, z1 + dz * t);
}

static Vector3 CollisionPoint_LineSegment_PlaneSurface(
    Vector3 segment_start,
    Vector3 segment_direction,
    Vector3 plane_point,
    Vector3 plane_normal)
{
    auto segment_terminal = segment_start + segment_direction;

    auto d1 = inner((segment_start - plane_point).normalize(), plane_normal);
    auto d2 = inner((segment_terminal - plane_point).normalize(), plane_normal);

    if (d1 * d2 > 0)
    {
        return NANVector;
    }
    else
    {
        auto nx = plane_normal.x;
        auto ny = plane_normal.y;
        auto nz = plane_normal.z;
        auto d = -inner(plane_normal, plane_point);

        auto x1 = segment_start.x;
        auto y1 = segment_start.y;
        auto z1 = segment_start.z;
        auto dx = segment_direction.x;
        auto dy = segment_direction.y;
        auto dz = segment_direction.z;

        auto t = -(nx * x1 + ny * y1 + nz * z1 + d) / (nx * dx + ny * dy + nz * dz);

        if (collided(t))
            return Vector3(x1 + dx * t, y1 + dy * t, z1 + dz * t);
        else
            return NANVector;
    }
}

static Vector3 CollisionPoint_LineSegment_Sphere(
    Vector3 segment_start,
    Vector3 segment_direction,
    Vector3 sphere_point,
    float sphere_radius)
{
    auto area = magnitude(outer(segment_direction, sphere_point - segment_start));
    auto length = magnitude(segment_direction);

    auto distance = area / length;

    if (distance < sphere_radius)
    {
        auto dx = segment_direction.x;
        auto dy = segment_direction.y;
        auto dz = segment_direction.z;

        auto tx = segment_start.x - sphere_point.x;
        auto ty = segment_start.y - sphere_point.y;
        auto tz = segment_start.z - sphere_point.z;

        auto a = dx * dx + dy * dy + dz * dz;
        auto b = dx * tx + dy * ty + dz * tz;
        auto c = tx * tx + ty * ty + tz * tz - sphere_radius * sphere_radius;

        auto D = b * b - a * c;
        if (D >= 0)
        {
            auto t = (-b - sqrt(D)) / a;
            if (collided(t))
            {
                return Vector3(segment_start.x + dx * t, segment_start.y + dy * t, segment_start.z + dz * t);
            }
        }
    }
    return NANVector;
}

static Vector3 CollisionPoint_LineSegment_AlignedBox(
    Vector3 segment_start,
    Vector3 segment_direction,
    float minx, float maxx,
    float miny, float maxy,
    float minz, float maxz)
{
    bool inside = true;
    float xt, yt, zt;

    if (segment_start.x < minx)
    {
        xt = minx - segment_start.x;
        if (xt > segment_direction.x)
        {
            return NANVector;
        }
        xt /= segment_direction.x;
        inside = false;

    }
    else if (segment_start.x > maxx)
    {
        xt = maxx - segment_start.x;
        if (xt < segment_direction.x)
        {
            return NANVector;
        }
        xt /= segment_direction.x;
        inside = false;

    }
    else
    {
        xt = -1;
    }

    if (segment_start.y < miny)
    {
        yt = miny - segment_start.y;
        if (yt > segment_direction.y)
        {
            return NANVector;
        }
        yt /= segment_direction.y;
        inside = false;

    }
    else if (segment_start.y > maxy)
    {
        yt = maxy - segment_start.y;
        if (yt < segment_direction.y)
        {
            return NANVector;
        }
        yt /= segment_direction.y;
        inside = false;

    }
    else
    {
        yt = -1;
    }

    if (segment_start.z < minz)
    {
        zt = minz - segment_start.z;
        if (zt > segment_direction.z)
        {
            return NANVector;
        }
        zt /= segment_direction.z;
        inside = false;

    }
    else if (segment_start.z > maxz)
    {
        zt = maxz - segment_start.z;
        if (zt < segment_direction.z)
        {
            return NANVector;
        }
        zt /= segment_direction.z;
        inside = false;

    }
    else
    {
        zt = -1;
    }

    // ボックスの中ならnullを返す
    if (inside)
    {
        return NANVector;
    }

    // もっとも遠い平面と衝突している
    int which = 0;
    auto t = xt;
    if (yt > t)
    {
        which = 1;
        t = yt;
    }
    if (zt > t)
    {
        which = 2;
        t = zt;
    }

    switch (which)
    {
    case 0: {
        // yz平面と衝突
        auto y = segment_start.y + segment_direction.y * t;
        if (y < miny || y > maxy)
        {
            return NANVector;
        }
        auto z = segment_start.z + segment_direction.z * t;
        if (z < minz || z > maxz)
        {
            return NANVector;
        }
        return Vector3(segment_start.x + segment_direction.x * t, y, z);
    }

    case 1: {
        // xz平面と衝突
        auto x = segment_start.x + segment_direction.x * t;
        if (x < minx || x > maxx)
        {
            return NANVector;
        }
        auto z = segment_start.z + segment_direction.z * t;
        if (z < minz || z > maxz)
        {
            return NANVector;
        }
        return Vector3(x, segment_start.y + segment_direction.y * t, z);
    }

    default: {
        // xy平面と衝突
        auto x = segment_start.x + segment_direction.x * t;
        if (x < minx || x > maxx)
        {
            return NANVector;
        }
        auto y = segment_start.y + segment_direction.y * t;
        if (y < miny || y > maxy)
        {
            return NANVector;
        }
        return Vector3(x, y, segment_start.z + segment_direction.z * t);
    }
    }
}

static Vector3 CollisionPoint_LineSegment_Box(
    Vector3 segment_start,
    Vector3 segment_direction,
    float minx, float maxx,
    float miny, float maxy,
    float minz, float maxz,
    Matrix4x3 box_matrix)
{
    Matrix4x3 box_local = box_matrix.inverse;

    Vector3 _segment_start = segment_start * box_local;
    Vector3 _segment_direction = (Vector4(segment_direction, 0) * box_local).xyz;

    Vector3 point = CollisionPoint_LineSegment_AlignedBox(
        _segment_start,
        _segment_direction,
        minx,
        maxx,
        miny,
        maxy,
        minz,
        maxz);

    if (collided(point))
        return point * box_matrix;
    else
        return NANVector;
}

static Vector3 CollisionPoint_LineSegment_Polygon3(
    Vector3 segment_start,
    Vector3 segment_direction,
    Vector3 polygon_vertex1,
    Vector3 polygon_vertex2,
    Vector3 polygon_vertex3
)
{
    Vector3 normal = outer(polygon_vertex2 - polygon_vertex1, polygon_vertex3 - polygon_vertex1).normalize();

    // 平面との衝突地点を計算する
    Vector3 point = CollisionPoint_LineSegment_PlaneSurface(segment_start, segment_direction, polygon_vertex1, normal);
    if (!collided(point))
        return NANVector;

    // 内部にあるか調べる
    Vector3 outer1 = outer(polygon_vertex2 - polygon_vertex1, point - polygon_vertex1);
    Vector3 outer2 = outer(polygon_vertex3 - polygon_vertex2, point - polygon_vertex2);
    Vector3 outer3 = outer(polygon_vertex1 - polygon_vertex3, point - polygon_vertex3);

    auto dot2 = inner(outer1, outer2);
    auto dot3 = inner(outer1, outer3);

    if (dot2 > 0 && dot3 > 0)
        //if (signbit(outer1.x) == signbit(outer2.x) && signbit(outer1.x) == signbit(outer3.x))
    {
        return point;
    }
    else
    {
        return NANVector;
    }
}

static Vector3 CollisionPoint_LineSegment_CurvedSurface(
    Vector3 segment_start,
    Vector3 segment_direction,
    const matrix<float>& surface_heights,
    Matrix4x3 surface_matrix)
{
    const int N = static_cast<int>(surface_heights.rows);

    Vector3 local_start = segment_start * surface_matrix.inverse;
    Vector3 local_terminal = (segment_start + segment_direction) * surface_matrix.inverse;

    int j0 = (int)((local_start.x + 0.5f) * (float)(N - 1));
    int i0 = (int)((-local_start.y + 0.5f) * (float)(N - 1));
    int j1 = (int)((local_terminal.x + 0.5f) * (float)(N - 1));
    int i1 = (int)((-local_terminal.y + 0.5f) * (float)(N - 1));

    zephyr::tie(i0, i1) = zephyr::minmax({ i0, i1 });
    zephyr::tie(j0, j1) = zephyr::minmax({ j0, j1 });

    i0 = zephyr::max(i0, 0);
    i1 = zephyr::min(i1, N - 1);
    j0 = zephyr::max(j0, 0);
    j1 = zephyr::min(j1, N - 1);

    for (int i = i0; i <= i1; i++)
    {
        for (int j = j0; j <= j1; j++)
        {
            float xmin = -0.5f + (float)(j) / (float)(N - 1);
            float xmax = -0.5f + (float)(j + 1) / (float)(N - 1);
            float ymin = 0.5f - (float)(i + 1) / (float)(N - 1);
            float ymax = 0.5f - (float)(i) / (float)(N - 1);

            float x1 = xmin;
            float y1 = ymax;
            float z1 = -surface_heights(i, j);

            float x2 = xmax;
            float y2 = ymax;
            float z2 = -surface_heights(i, j + 1);

            float x3 = xmin;
            float y3 = ymin;
            float z3 = -surface_heights(i + 1, j);

            float x4 = xmax;
            float y4 = ymin;
            float z4 = -surface_heights(i + 1, j + 1);

            Vector3 v1 = Vector3(x1, y1, z1) * surface_matrix;
            Vector3 v2 = Vector3(x2, y2, z2) * surface_matrix;
            Vector3 v3 = Vector3(x3, y3, z3) * surface_matrix;
            Vector3 v4 = Vector3(x4, y4, z4) * surface_matrix;

            Vector3 point = CollisionPoint_LineSegment_Polygon3(segment_start, segment_direction, v1, v2, v3);
            if (collided(point))
                return point;

            point = CollisionPoint_LineSegment_Polygon3(segment_start, segment_direction, v3, v2, v4);
            if (collided(point))
                return point;
        }
    }

    return NANVector;
}

static float Height_Point_PlaneSurface(
    Vector3 point,
    Vector3 plane_point,
    Vector3 plane_normal)
{
    float x0 = plane_point.x;
    float y0 = plane_point.y;
    float z0 = plane_point.z;

    float a = plane_normal.x;
    float b = plane_normal.y;
    float c = plane_normal.z;

    // a(x-x0) + b(y-y0) + c(z-z0) = 0
    // ax + by + cz -ax0 -by0 -cz0 = 0
    // ax + by + cz + d = 0
    // d = -(ax0 + by0 + cz0)

    float d = -(a * x0 + b * y0 + c * z0);

    float x1 = point.x;
    float y1 = point.y;
    float z1 = point.z;

    // ax1 + by* + cz1 + d = 0
    // y* = -(ax1 + cz1 + d) / b

    float y = -(a * x1 + c * z1 + d) / b;
    return y1 - y;
}

static float Height_Point_CurvedSurface(
    Vector3 point,
    const matrix<float>& surface_heights,
    Matrix4x3 surface_matrix)
{
    // v1 ----- v2
    // |        |
    // |  v0    |
    // | /      |
    // v3 ----- v4

    //    ^ +y
    //    |
    //    |
    //    o-----> +x
    //   /
    //  * -z

    const int N = static_cast<int>(surface_heights.rows);

    Vector3 local_point = point * surface_matrix.inverse;
    float x0 = local_point.x;
    float y0 = local_point.y;

    if (fabsf(x0) > 0.5f || fabsf(y0) > 0.5f)
        return NAN;

    int j = (int)((x0 + 0.5f) * (float)(N - 1));
    int i = (int)((-y0 + 0.5f) * (float)(N - 1));

    float xmin = -0.5f + (float)(j) / (float)(N - 1);
    float xmax = -0.5f + (float)(j + 1) / (float)(N - 1);
    float ymin = 0.5f - (float)(i + 1) / (float)(N - 1);
    float ymax = 0.5f - (float)(i) / (float)(N - 1);

    constexpr float eps = 1e-6f;
    assert(0 <= i && i < N - 1);
    assert(0 <= j && j < N - 1);
    assert(xmin < xmax);
    assert(ymin < ymax);
    assert(xmin - eps <= x0 && x0 <= xmax + eps);
    assert(ymin - eps <= y0 && y0 <= ymax + eps);

    float x1 = xmin;
    float y1 = ymax;
    float z1 = -surface_heights(i, j);

    float x2 = xmax;
    float y2 = ymax;
    float z2 = -surface_heights(i, j + 1);

    float x3 = xmin;
    float y3 = ymin;
    float z3 = -surface_heights(i + 1, j);

    float x4 = xmax;
    float y4 = ymin;
    float z4 = -surface_heights(i + 1, j + 1);

    Vector2 u0 = Vector2(x0, y0);
    Vector2 u1 = Vector2(x1, y1);
    Vector2 u2 = Vector2(x2, y2);
    Vector2 u3 = Vector2(x3, y3);
    Vector2 u4 = Vector2(x4, y4);

    Vector3 v1 = Vector3(x1, y1, z1);
    Vector3 v2 = Vector3(x2, y2, z2);
    Vector3 v3 = Vector3(x3, y3, z3);
    Vector3 v4 = Vector3(x4, y4, z4);

    float cross_product = outer(u2 - u3, u0 - u3);

    Vector3 plane_point;
    Vector3 plane_normal;
    if (0 <= cross_product)
    {
        plane_point = v1;
        plane_normal = outer(v1 - v3, v2 - v3);
    }
    else
    {
        plane_point = v4;
        plane_normal = outer(v2 - v3, v4 - v3);
    }

    plane_point = plane_point * surface_matrix;
    plane_normal = plane_normal * surface_matrix.get_matrix3x3();

    return Height_Point_PlaneSurface(point, plane_point, plane_normal);
}

static auto CollisionPoint_SweepingPoint_Plane = CollisionPoint_LineSegment_PlaneSurface;

static auto CollisionPoint_SweepingPoint_Sphere = CollisionPoint_LineSegment_Sphere;

static auto CollisionPoint_SweepingPoint_AlignedBox = CollisionPoint_LineSegment_AlignedBox;

static auto CollisionPoint_SweepingPoint_Box = CollisionPoint_LineSegment_Box;

static float CollisionTime_SweepingSphere_SweepingSphere(
    Vector3 sweep1_start,
    Vector3 sweep1_direction,
    float sweep1_radius,
    Vector3 sweep2_start,
    Vector3 sweep2_direction,
    float sweep2_radius)
{
    auto sumRadius = sweep1_radius + sweep2_radius;
    Vector3 c = sweep1_start - sweep2_start;
    Vector3 d = sweep2_direction - sweep1_direction;
    auto cx = c.x, cy = c.y, cz = c.z;
    auto dx = d.x, dy = d.y, dz = d.z;
    auto p = dx * dx + dy * dy + dz * dz;
    auto q = cx * dx + cy * dy + cz * dz;
    auto r = cx * cx + cy * cy + cz * cz - sumRadius * sumRadius;
    auto D = q * q - p * r;
    if (D >= 0)
    {
        if (nearly0(D))
        {
            auto time = -q / p;
            return time;
        }
        else
        {
            auto time = (-q + sqrt(D)) / p;
            return time;
        }
    }
    return NAN;
}

static Vector3 CollisionPoint_SweepingSphere_SweepingSphere(
    Vector3 sweep_start1,
    Vector3 sweep_direction1,
    float sweep_radius1,
    Vector3 sweep_start2,
    Vector3 sweep_direction2,
    float sweep_radius2)
{
    auto time = CollisionTime_SweepingSphere_SweepingSphere(sweep_start1, sweep_direction1, sweep_radius1, sweep_start2, sweep_direction2, sweep_radius2);
    if (collided(time))
    {
        Vector3 point = (sweep_start1 + sweep_start2) / 2;
        Vector3 relative = (sweep_direction1 + sweep_direction2) / 2;
        return point + relative;
    }
    else
    {
        return NANVector;
    }
}

static float CollisionTime_SweepingPoint_SweepingSphere(
    Vector3 sweep_start1,
    Vector3 sweep_direction1,
    Vector3 sweep_start2,
    Vector3 sweep_direction2,
    float sweep_radius2)
{
    return CollisionTime_SweepingSphere_SweepingSphere(sweep_start1, sweep_direction1, 0, sweep_start2, sweep_direction2, sweep_radius2);
}

static Vector3 CollisionPoint_SweepingPoint_SweepingSphere(
    Vector3 sweep_start1,
    Vector3 sweep_direction1,
    Vector3 sweep_start2,
    Vector3 sweep_direction2,
    float sweep_radius2)
{
    return CollisionPoint_SweepingSphere_SweepingSphere(sweep_start1, sweep_direction1, 0, sweep_start2, sweep_direction2, sweep_radius2);
}

static float Distance_Line_Line(
    Vector3 line1_start,
    Vector3 line1_direction,
    Vector3 line2_start,
    Vector3 line2_direction)
{
    Vector3 n = outer(line1_direction, line2_direction);
    n.normalize();
    Vector3 v = line2_start - line1_start;
    return abs(inner(n, v));
}

static float Distance_Point_PlaneSurface(
    Vector3 point,
    Vector3 plane_point,
    Vector3 plane_normal)
{
    Vector3 v = point - plane_point;
    return inner(v, plane_normal);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Line& obj1, const Matrix4x3& matrix1, const PlaneSurface& obj2, const Matrix4x3& matrix2)
{
    auto& line = obj1;
    auto& line_matrix = matrix1;
    auto& plane = obj2;
    auto& plane_matrix = matrix2;

    Vector3 line_start = line_matrix.position;
    Vector3 line_direction = (Vector4(line.direction, 0) * line_matrix).xyz;
    Vector3 plane_point = plane_matrix.position;
    Vector3 plane_normal = (Vector4(plane.normal, 0) * plane_matrix).xyz;

    return CollisionPoint_Line_PlaneSurface(line_start, line_direction, plane_point, plane_normal);
}

template<> Vector3 zephyr::collision::CalculateCollisionPoint(const Line & obj1, const Matrix4x3 & matrix1, const CurvedSurface & obj2, const Matrix4x3 & matrix2)
{
    return Vector3();
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const PlaneSurface& obj2, const Matrix4x3& matrix2)
{
    auto& segment = obj1;
    auto& segment_matrix = matrix1;
    auto& plane = obj2;
    auto& plane_matrix = matrix2;

    Vector3 segment_start = segment_matrix.position;
    Vector3 segment_direction = (Vector4(segment.direction, 0) * segment_matrix).xyz;
    Vector3 plane_point = plane_matrix.position;
    Vector3 plane_normal = (Vector4(plane.normal, 0) * plane_matrix).xyz;
    plane_normal.normalize();

    return CollisionPoint_LineSegment_PlaneSurface(segment_start, segment_direction, plane_point, plane_normal);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const Sphere& obj2, const Matrix4x3& matrix2)
{
    auto& segment = obj1;
    auto& segment_matrix = matrix1;
    auto& sphere = obj2;
    auto& sphere_matrix = matrix2;

    Vector3 segment_start = segment_matrix.position;
    Vector3 segment_direction = (Vector4(segment.direction, 0) * segment_matrix).xyz;
    Vector3 sphere_point = sphere_matrix.position;
    float sphere_radius = sphere.radius;

    return CollisionPoint_LineSegment_Sphere(segment_start, segment_direction, sphere_point, sphere_radius);
}

#if 0
Vector3 zephyr::collision::CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const AlignedBox& obj2)
{
    auto& segment = obj1;
    auto& segment_matrix = matrix1;
    auto& alignedbox = obj2;

    Vector3 segment_start = segment_matrix.position;
    Vector3 segment_direction = (Vector4(segment.direction, 0) * segment_matrix).xyz;

    return CollisionPoint_LineSegment_AlignedBox(
        segment_start,
        segment_direction,
        alignedbox.minX,
        alignedbox.maxX,
        alignedbox.minY,
        alignedbox.maxY,
        alignedbox.minZ,
        alignedbox.maxZ);
}
#endif

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const Box& obj2, const Matrix4x3& matrix2)
{
    auto& segment = obj1;
    auto& segment_matrix = matrix1;
    auto& box = obj2;
    auto& box_matrix = matrix2;

    Vector3 segment_start = segment_matrix.position * segment_matrix;
    Vector3 segment_direction = (Vector4(segment.direction, 0) * segment_matrix).xyz;

    return CollisionPoint_LineSegment_Box(
        segment_start,
        segment_direction,
        box.minX,
        box.maxX,
        box.minY,
        box.maxY,
        box.minZ,
        box.maxZ,
        box_matrix);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const LineSegment& obj1, const Matrix4x3& matrix1, const CurvedSurface& obj2, const Matrix4x3& matrix2)
{
    auto& segment = obj1;
    auto& segment_matrix = matrix1;
    auto& surface = obj2;
    auto& surface_heights = surface.heights;
    auto& surface_matrix = matrix2;

    Vector3 segment_start = segment_matrix.position;
    Vector3 segment_direction = (Vector4(segment.direction, 0) * segment_matrix).xyz;

    return CollisionPoint_LineSegment_CurvedSurface(segment_start, segment_direction, surface_heights, surface_matrix);
}

template<> Vector3 zephyr::collision::CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const CurvedSurface& obj2, const Matrix4x3& matrix2)
{
    return NANVector;
}

template<> Vector3 zephyr::collision::CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const CurvedSurface& obj2, const Matrix4x3& matrix2)
{
    return NANVector;
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const PlaneSurface& obj2, const Matrix4x3& matrix2)
{
    auto& point = obj1;
    auto& point_matrix = matrix1;
    auto& point_veloticy = velocity1;
    auto& plane = obj2;
    auto& plane_matrix = matrix2;

    Vector3 point_start = point_matrix.position;
    Vector3 point_direction = point_veloticy;
    Vector3 plane_point = plane_matrix.position;
    Vector3 plane_normal = (Vector4(plane.normal, 0) * plane_matrix).xyz;
    plane_normal.normalize();

    return CollisionPoint_SweepingPoint_Plane(point_start, point_direction, plane_point, plane_normal);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2)
{
    auto& point = obj1;
    auto& point_matrix = matrix1;
    auto& point_veloticy = velocity1;
    auto& sphere = obj2;
    auto& sphere_matrix = matrix2;

    Vector3 point_start = point_matrix.position;
    Vector3 point_direction = point_veloticy;
    Vector3 sphere_point = sphere_matrix.position;
    float sphere_radius = sphere.radius;

    return CollisionPoint_SweepingPoint_Sphere(point_start, point_direction, sphere_point, sphere_radius);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2)
{
    auto& sweep1 = obj1;
    auto& sweep1_matrix = matrix1;
    auto& sweep1_direction = velocity1;
    auto& sweep2 = obj2;
    auto& sweep2_matrix = matrix2;
    auto& sweep2_direction = velocity2;

    Vector3 sweep1_start = sweep1_matrix.position;
    Vector3 sweep2_start = sweep2_matrix.position;
    float sweep2_radius = sweep2.radius;

    return CollisionPoint_SweepingPoint_SweepingSphere(sweep1_start, sweep1_direction, sweep2_start, sweep2_direction, sweep2_radius);
}

#if 0
Vector3 zephyr::collision::CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const AlignedBox& obj2)
{
    auto& sweep = obj1;
    auto& sweep_matrix = matrix1;
    auto& sweep_velocity = velocity1;
    auto& alignedbox = obj2;

    Vector3 sweep_start = sweep_matrix.position;
    Vector3 sweep_direction = sweep_start + sweep_velocity;

    return CollisionPoint_SweepingPoint_AlignedBox(
        sweep_start,
        sweep_direction,
        alignedbox.minX,
        alignedbox.maxX,
        alignedbox.minY,
        alignedbox.maxY,
        alignedbox.minZ,
        alignedbox.maxZ);
}
#endif

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Box& obj2, const Matrix4x3& matrix2)
{
    auto& sweep = obj1;
    auto& sweep_matrix = matrix1;
    auto& sweep_velocity = velocity1;
    auto& box = obj2;
    auto& box_matrix = matrix2;

    Vector3 sweep_start = sweep_matrix.position;
    Vector3 sweep_direction = velocity1;

    return CollisionPoint_SweepingPoint_Box(
        sweep_start,
        sweep_direction,
        box.minX,
        box.maxX,
        box.minY,
        box.maxY,
        box.minZ,
        box.maxZ,
        box_matrix);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const CurvedSurface& obj2, const Matrix4x3& matrix2)
{
    auto& point_start = matrix1.position;
    auto& point_direction = velocity1;
    auto& surface = obj2;
    auto& surface_heights = surface.heights;
    auto& surface_matrix = matrix2;

    return CollisionPoint_LineSegment_CurvedSurface(point_start, point_direction, surface_heights, surface_matrix);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const PlaneSurface& obj2, const Matrix4x3& matrix2)
{
    auto& sweep = obj1;
    auto& sweep_matrix = matrix1;
    auto& sweep_direction = velocity1;
    auto& plane = obj2;
    auto& plane_matrix = matrix2;

    Vector3 segment_start = sweep_matrix.position;
    Vector3 segment_direction = sweep_direction;
    Vector3 plane_point = plane_matrix.position;
    Vector3 plane_normal = (Vector4(plane.normal, 0) * plane_matrix).xyz;
    plane_normal.normalize();

    plane_point += plane_normal * sweep.radius;

    return CollisionPoint_LineSegment_PlaneSurface(segment_start, segment_direction, plane_point, plane_normal);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2)
{
    auto& sweep1 = obj1;
    auto& sweep1_matrix = matrix1;
    auto& sweep1_direction = velocity1;
    auto& sweep2 = obj2;
    auto& sweep2_matrix = matrix2;
    auto& sweep2_direction = velocity2;

    Vector3 sweep1_start = sweep1_matrix.position;
    Vector3 sweep2_start = sweep2_matrix.position;
    float sweep1_radius = sweep1.radius;
    float sweep2_radius = sweep2.radius;

    return CollisionPoint_SweepingSphere_SweepingSphere(sweep1_start, sweep1_direction, sweep1_radius, sweep2_start, sweep2_direction, sweep2_radius);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2)
{
    auto& sweep = obj1;
    auto& _sphere = obj2;

    Sphere sphere;
    sphere.radius = sweep.radius + _sphere.radius;

    return CalculateCollisionPoint((LineSegment&)sweep, matrix1, sphere, matrix2);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Box& obj2, const Matrix4x3& matrix2)
{
    auto& sweep = obj1;
    auto& _box = obj2;

    Box box = _box;
    auto radius = sweep.radius;
    box.minX -= radius;
    box.maxX += radius;
    box.minY -= radius;
    box.maxY += radius;
    box.minZ -= radius;
    box.maxZ += radius;
    return CalculateCollisionPoint((LineSegment&)(sweep), matrix1, box, matrix2);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const CurvedSurface& obj2, const Matrix4x3& matrix2)
{
    auto& point_matrix = matrix1;
    auto& point_velocity = velocity1;
    auto& surface = obj2;
    auto surface_matrix = matrix2;

    return CalculateCollisionPoint(Point(), point_matrix, point_velocity, surface, surface_matrix);
}

template <> Vector3 zephyr::collision::CalculateCollisionPoint(const Sphere& obj1, const Matrix4x3& matrix1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2)
{
    return CalculateCollisionPoint(obj2, matrix2, velocity2, obj1, matrix1);
}

template <> float zephyr::collision::CalculateCollisionTime(const Sphere& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2)
{
    auto& sweep1 = obj1;
    auto& sweep1_matrix = matrix1;
    auto& sweep1_direction = velocity1;
    auto& sweep2 = obj2;
    auto& sweep2_matrix = matrix2;
    auto& sweep2_direction = velocity2;

    Vector3 sweep1_start = sweep1_matrix.position;
    Vector3 sweep2_start = sweep2_matrix.position;
    float sweep1_radius = sweep1.radius;
    float sweep2_radius = sweep2.radius;

    return CollisionTime_SweepingSphere_SweepingSphere(sweep1_start, sweep1_direction, sweep1_radius, sweep2_start, sweep2_direction, sweep2_radius);
}

template <> float zephyr::collision::CalculateCollisionTime(const Point& obj1, const Matrix4x3& matrix1, const Vector3& velocity1, const Sphere& obj2, const Matrix4x3& matrix2, const Vector3& velocity2)
{
    auto& sweep1 = obj1;
    auto& sweep1_matrix = matrix1;
    auto& sweep1_direction = velocity1;
    auto& sweep2 = obj2;
    auto& sweep2_matrix = matrix2;
    auto& sweep2_direction = velocity2;

    Vector3 sweep1_start = sweep1_matrix.position;
    Vector3 sweep2_start = sweep2_matrix.position;
    float sweep2_radius = sweep2.radius;

    return CollisionTime_SweepingPoint_SweepingSphere(sweep1_start, sweep1_direction, sweep2_start, sweep2_direction, sweep2_radius);
}

float zephyr::collision::CalculateDistance(const Line& obj1, const Matrix4x3& matrix1, const Line& obj2, const Matrix4x3& matrix2)
{
    auto& line1 = obj1;
    auto& line1_matrix = matrix1;
    auto& line2 = obj2;
    auto& line2_matrix = matrix2;

    Vector3 line1_start = line1_matrix.position;
    Vector3 line2_start = line2_matrix.position;
    Vector3 line1_direction = (Vector4(line1.direction, 0) * line1_matrix).xyz;
    Vector3 line2_direction = (Vector4(line2.direction, 0) * line2_matrix).xyz;

    return Distance_Line_Line(line1_start, line1_direction, line2_start, line2_direction);
}

float zephyr::collision::CalculateDistance(const Point& obj1, const Matrix4x3& matrix1, const PlaneSurface& obj2, const Matrix4x3& matrix2)
{
    auto& plane = obj2;
    auto& plane_matrix = matrix2;

    Vector3 plane_point = plane_matrix.position;
    Vector3 plane_normal = (Vector4(plane.normal, 0) * plane_matrix).xyz;

    return Distance_Point_PlaneSurface(matrix1.position, plane_point, plane_normal);
}

float zephyr::collision::CalculateHeight(const Vector3& point, const PlaneSurface& obj2, const Matrix4x3& matrix2)
{
    auto& plane = obj2;
    auto& plane_matrix = matrix2;

    Vector3 plane_point = plane_matrix.position;
    Vector3 plane_normal = (Vector4(plane.normal, 0) * plane_matrix).xyz;
    plane_normal.normalize();

    return Height_Point_PlaneSurface(point, plane_point, plane_normal);
}

float zephyr::collision::CalculateHeight(const Vector3& point, const CurvedSurface& obj2, const Matrix4x3& matrix2)
{
    auto& curved = obj2;
    auto& curved_matrix = matrix2;

    return Height_Point_CurvedSurface(point, curved.heights, curved_matrix);
}
