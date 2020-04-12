#pragma once

namespace rt::maths {

    template<typename T>
    class Vector3 {
    public:
        Vector3(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {}
        ~Vector3() = default;
        
        inline Vector3<T> operator-(const Vector3<T> &v)
        {
            return Vector3<T>(x - v.x, y - v.y, z - v.z);
        }

        inline Vector3<T> operator*(float t)
        {
            return Vector3<T>(x * t, y * t, z * t);
        }

        /**
         * @brief Return the scalar product (also called 'dot' product) of two vectors.
         * @param v The other vector used to compute the operation.
         * 
         */
        inline T operator*(const Vector3<T> &v)
        {
            return (x * v.x + y * v.y + z * v.z);
        }

        inline Vector3<T> operator+(const Vector3<T> &v)
        {
            return Vector3<T>(x + v.x, y + v.y, z + v.z);
        }

        inline float squarePower(void)
        {
            return *this * *this;
        }

        T x;
        T y;
        T z;
    };

    typedef Vector3<float> Vector3f;

}