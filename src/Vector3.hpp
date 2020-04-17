#pragma once

#include <cmath>
#include <iostream>

namespace rt::maths {

    template<typename T>
    class Vector3 {
    public:
        Vector3() : x(0), y(0), z(0) {}
        Vector3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {}
        Vector3(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {}
        ~Vector3() = default;

        inline float norm(void) const
        {
            // Remember the Pythagore theorem ? For 3D, just add z

            return (::sqrtf(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2)));
        }

        inline Vector3<T> &operator=(const Vector3<T> &v)
        {
            x = v.x;
            y = v.y;
            z = v.z;

            return *this;
        }

        inline Vector3<T> normalize(void) const
        {
            float vectorLength = norm();

            return Vector3<T>(x / vectorLength, y / vectorLength, z / vectorLength);
        }
        
        inline Vector3<T> operator-(const Vector3<T> &v) const
        {
            return Vector3<T>(x - v.x, y - v.y, z - v.z);
        }

        inline Vector3<T> operator*(float t) const
        {
            return Vector3<T>(x * t, y * t, z * t);
        }

        /**
         * @brief Return the scalar product (also called 'dot' product) of two vectors.
         * @param v The other vector used to compute the operation.
         * 
         */
        inline T operator*(const Vector3<T> &v) const
        {
            return (x * v.x + y * v.y + z * v.z);
        }

        inline Vector3<T> operator+(const Vector3<T> &v) const
        {
            return Vector3<T>(x + v.x, y + v.y, z + v.z);
        }

        inline constexpr bool operator<(const Vector3<T> &v) const
        {
            return (this->norm() < v.norm());
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
        stream << "Vector3 --> (" << v.x << ", " << v.y << ", " << v.z << ")";
        return (stream);
    }

    typedef Vector3<float> Vector3f;

}