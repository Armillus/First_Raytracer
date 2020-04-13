#pragma once

#include <iostream>

#include "Object.hpp"

namespace rt {

    class Plane : public Object {
    public:
        Plane(const maths::Vector3f &normal, const maths::Vector3f &point, const Color &color = Color(0u, 255u, 0u))
            : Object(color), _normal(normal), _point(point)
        {}

        ~Plane() = default;

        bool intersect(Ray &ray, float *t)
        {
            float denominator = ray.direction() * _normal;

            //std::cout << "denominator = " << denominator << " | dir = " << ray.direction() << " | normal = " << _normal << std::endl;
            if (std::abs(denominator) > 0.001f)
            {
                //float res = ((_point - ray.origin()) * _normal) / denominator;
                float res = ((ray.origin() * _normal) + 100.0) / (-denominator);

                if (res >= 0.001f && res < *t)
                {
                    *t = res;
                    return true;
                }
            }
            return false;
        }

        inline maths::Vector3f normalSurface(maths::Vector3f &p)
        {
            return _normal;
        }

        inline maths::Vector3f &center()
        {
            return _point;
        }

    private:
        maths::Vector3f _normal;
        maths::Vector3f _point;
    };

}