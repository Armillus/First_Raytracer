#pragma once

#include "Ray.hpp"
#include "Color.hpp"

namespace rt {

    class Object {
    public:
        Object(const Color &color) : _color(color) {}
        virtual ~Object() = default;

        virtual bool intersects(Ray &ray, float *t)
        { 
            return false;
        }

        inline Color &color()
        {
            return _color;
        }

    private:
        Color _color;
        float _reflection;
    };

}