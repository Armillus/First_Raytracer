#pragma once

#include <string>

#include "Ray.hpp"
#include "Color.hpp"

namespace rt {

    class Object {
    public:
        Object(const Color &color) : _color(color), _reflection(0.5) {}
        virtual ~Object() = default;

        virtual bool intersect(Ray &ray, float *t) = 0;
        virtual maths::Vector3f normalSurface(maths::Vector3f &p) = 0;

        virtual maths::Vector3f &center() = 0;

        inline Color &color()
        {
            return _color;
        }

        inline float &reflection(void)
        {
            return _reflection;
        }




    private:
        Color _color;
        float _reflection;
    };

}