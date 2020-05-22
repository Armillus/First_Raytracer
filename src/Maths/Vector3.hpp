#pragma once

#include <cmath>
#include <iostream>
#include <array>

namespace rt::maths {

    template<typename T>
    class Vector3 {
    public:
        Vector3() : x(0), y(0), z(0) {}
        Vector3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {}
        Vector3(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {}
        Vector3(const std::array<float, 3> &v) : x(v.at(0)), y(v.at(1)), z(v.at(2)) {}
        ~Vector3() = default;

        inline constexpr float norm(void) const
        {
            // Remember the Pythagore theorem ? For 3D, just add z

            return (::sqrtf(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2)));
        }

        // inline constexpr float squaredNorm(void) const
        // {
        //     return ((std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2)));
        // }

        inline constexpr Vector3<T> &operator=(const Vector3<T> &v)
        {
            x = v.x;
            y = v.y;
            z = v.z;

            return *this;
        }

        inline constexpr Vector3<T> &operator=(const std::array<int, 3> &v)
        {
            x = v[0];
            y = v[1];
            z = v[2];
            return *this;
        }

        inline constexpr bool operator==(const Vector3<T> &v)
        {
            return (x == v.x && y == v.y && z == v.z);
        }

        inline constexpr bool operator!=(const Vector3<T> &v)
        {
            return (x != v.x || y != v.y || z != v.z);
        }

        inline constexpr Vector3<T> normalize(void) const
        {
            float vectorLength = norm();

            return Vector3<T>(x / vectorLength, y / vectorLength, z / vectorLength);
        }
        
        inline constexpr Vector3<T> operator-(const Vector3<T> &v) const
        {
            return Vector3<T>(x - v.x, y - v.y, z - v.z);
        }

        inline constexpr Vector3<T> operator-(void) const
        {
            return Vector3<T>(-x, -y, -z);
        }

        inline constexpr Vector3<T> operator*(float t) const
        {
            return Vector3<T>(x * t, y * t, z * t);
        }

        inline constexpr Vector3<T> cross(const Vector3<T> &v) const
        {
            float cx = (y * v.z) - (z * v.y);
            float cy = (z * v.x) - (x * v.z);
            float cz = (x * v.y) - (y * v.x);

            return Vector3<T>(cx, cy, cz);
        }

        /**
         * @brief Return the scalar product (also called 'dot' product) of two vectors.
         * @param v The other vector used to compute the operation.
         * 
         */
        inline constexpr T operator*(const Vector3<T> &v) const
        {
            return (x * v.x + y * v.y + z * v.z);
        }

        inline constexpr Vector3<T> operator+(const Vector3<T> &v) const
        {
            return Vector3<T>(x + v.x, y + v.y, z + v.z);
        }

        inline constexpr bool operator<(const Vector3<T> &v) const
        {
            return (this->norm() < v.norm());
            //return (this->squaredNorm() < v.squaredNorm());
        }

        inline constexpr bool operator<=(const Vector3<T> &v) const
        {
            return (this->norm() <= v.norm());
        }

        inline constexpr bool operator>(const Vector3<T> &v) const
        {
            return (this->norm() > v.norm());
        }

        inline constexpr bool operator>=(const Vector3<T> &v) const
        {
            return (this->norm() >= v.norm());
        }

        inline constexpr float squarePower(void) const
        {
            return *this * *this;
        }

        T x;
        T y;
        T z;
    };

    template <typename T>
    inline std::ostream &operator<<(std::ostream &stream, const Vector3<T> &v)
    {
        stream << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
        return (stream);
    }

    typedef Vector3<float> Vector3f;

}