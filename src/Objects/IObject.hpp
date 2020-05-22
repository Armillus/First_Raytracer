#pragma once

#include "Ray.hpp"
#include "Material.hpp"
#include "SfmlTexture.hpp"

namespace rt {

    enum ObjectType {
        tTriangle,
        tSphere,
        tPlane
    };

    class IObject {
    public:
        virtual ~IObject() = default;

        virtual bool intersect(const Ray &ray, float *t) const = 0;
        virtual maths::Vector3f normalSurface(const maths::Vector3f &p) const = 0;
        virtual maths::Vector3f const &center() const = 0;
        virtual Color color(const maths::Vector3f &point) const = 0;
        virtual Material const &material() const = 0;
        virtual void createTetxureFromFile(const std::string &filepath) = 0;
        virtual ObjectType type() const = 0;
    };

}