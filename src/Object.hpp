#pragma once

#include "Ray.hpp"
#include "Color.hpp"

namespace rt {

    class Object {
    public:
        Object(const Color &color) : _color(color) {}
        virtual ~Object() = default;

        virtual bool intersect(Ray &ray, float *t) = 0;

        inline Color &color()
        {
            return _color;
        }

    private:
        Color _color;
        float _reflection;
    };

}