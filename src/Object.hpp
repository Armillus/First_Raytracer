#pragma once

#include <string>

#include "Ray.hpp"
#include "Material.hpp"

namespace rt {

    class Object {
    public:
        Object(const Material &mat) : _material(mat) {}
        Object(const Color &color, float reflection = 0.0f) : _material(color, reflection) {}
        virtual ~Object() = default;

        virtual bool intersect(const Ray &ray, float *t) = 0;
        virtual maths::Vector3f normalSurface(maths::Vector3f &p) = 0;

        virtual maths::Vector3f &center() = 0;

        inline Color &color()
        {
            return _material.color;
        }

        inline float &reflection(void)
        {
            return _material.reflection;
        }

    private:
        Material _material;
    };

}