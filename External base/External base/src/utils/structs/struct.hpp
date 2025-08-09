#pragma once
#include <cmath>

struct Vector2
{
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}
};

struct Vector3 {
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    bool operator==(const Vector3& other) const {
        const float epsilon = 0.0001f;
        return fabsf(x - other.x) < epsilon &&
            fabsf(y - other.y) < epsilon &&
            fabsf(z - other.z) < epsilon;
    }
    Vector3 operator+(const Vector3& other) const {
        return Vector3(
            x + other.x,
            y + other.y,
            z + other.z
        );
    }
    
};

struct Vector4 {
    float x, y, z, w;
};

struct Matrix4 {
    float data[16];
};

inline Vector3 VectorSub(Vector3 first, Vector3 second)
{
    Vector3 result{ first.x - second.x, first.y - second.y, first.z - second.z };
    return result;
}

inline Vector3 VectorAdd(Vector3 first, Vector3 second) {
    Vector3 result{ first.x + second.x, first.y + second.y, first.z + second.z };
    return result;
}

inline float VectorLength(const Vector3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline Vector3 VectorNormalize(const Vector3& v) {
    float len = VectorLength(v);
    if (len < 1e-6f) // avoid division by zero
        return Vector3{ 0.0f, 0.0f, 0.0f };
    return Vector3{ v.x / len, v.y / len, v.z / len };
}

inline Vector3 VectorMul(const Vector3& v, float scalar) {
    return Vector3{ v.x * scalar, v.y * scalar, v.z * scalar };
}

inline Vector3 VectorLerp(const Vector3& a, const Vector3& b, float t) {
    return Vector3{
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t
    };
}