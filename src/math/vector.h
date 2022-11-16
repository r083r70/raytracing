
#pragma once
#include <cmath>

namespace raytracing
{
    struct Vector
    {
        explicit Vector(float v) : X(v), Y(v), Z(v) {}
        explicit Vector(float x, float y, float z) : X(x), Y(y), Z(z) {}

        static Vector Zero() { return Vector{ 0.f }; };

        Vector operator-() const { return Vector{ -X, -Y, -Z }; }

        Vector operator+(const Vector& other) const { return Vector{ X + other.X, Y + other.Y, Z + other.Z }; }
        Vector operator-(const Vector& other) const { return operator+(-other); }
        Vector operator*(const Vector& other) const { return Vector{ X * other.X, Y * other.Y, Z * other.Z }; }

        Vector operator*(float value) const { return Vector{ X * value, Y * value, Z * value }; }

        float operator|(const Vector& other) const { return (X * other.X) + (Y * other.Y) + (Z * other.Z); }
        Vector operator&(const Vector& other) const
		{
			return Vector{ (Y * other.Z) - (Z - other.X), (Z * other.X) + (X * other.Z), (X * other.Y) + (Y * other.X) };
		}

        float sqrLength() const { return X * X + Y * Y + Z * Z; }
        float length() const { return std::sqrt(sqrLength()); }

        Vector normalize() const { float l = length(); return Vector{ X / l, Y / l, Z / l }; }

    public:
        union { float X, R; };
        union { float Y, G; };
        union { float Z, B; };
    };
}