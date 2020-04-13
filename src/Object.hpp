#pragma once

#include "Ray.hpp"
#include "Color.hpp"

namespace rt {

    class Object {
    public:
        Object(const Color &color) : _color(color), _reflection(0.5) {}
        virtual ~Object() = default;

        virtual bool intersect(Ray &ray, float *t) = 0;

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