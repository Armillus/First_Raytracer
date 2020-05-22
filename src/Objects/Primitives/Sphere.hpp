#pragma once

#include <cmath>

#include "Object.hpp"

namespace rt {

    class Sphere : public Object {
    public:
        Sphere(const maths::Vector3f &center,
               float radius, const Material &material);
        Sphere(const maths::Vector3f &center,
               float radius, const Material &material, const std::string &textureFilepath);
        ~Sphere() override = default;

        bool intersect(const Ray &ray, float *t) const override;

        inline maths::Vector3f normalSurface(const maths::Vector3f &p) const override
        {
            return (p - _center).normalize();
        }

        inline maths::Vector3f const &center() const override
        {
            return _center;
        }

        inline void setCenter(const maths::Vector3f &center)
        {
            _center = center;
        }

        inline void setRadius(float radius)
        {
            _radius = radius;
        }

        inline void setMaterial(const Material &material)
        {
            _material = material;
        }

        Color color(const maths::Vector3f &point) const override;

    private:
        maths::Vector3f _center;
        float _radius;
    };

}