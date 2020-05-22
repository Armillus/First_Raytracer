#pragma once

#include <cmath>

#include "Object.hpp"

namespace rt {

    class Triangle : public Object {
    public:
        Triangle(const maths::Vector3f &p1, const maths::Vector3f &p2, const maths::Vector3f &p3,
                const Material &material);
        Triangle(const maths::Vector3f &p1, const maths::Vector3f &p2, const maths::Vector3f &p3,
                const Material &material, const std::string &textureFilepath);
        ~Triangle() override = default;

        bool intersect(const Ray &ray, float *t) const override;

        // We only need to compute the triangle normal once.
        void computeNormal()
        {
            maths::Vector3f edge1 = _v2 - _v1;
            maths::Vector3f edge2 = _v3 - _v1;

            _normal = edge1.cross(edge2);
            _d = _normal * _v1;
        }

        inline void setVertices(const maths::Vector3f &p1, const maths::Vector3f &p2, const maths::Vector3f &p3)
        {
            _v1 = p1;
            _v2 = p2;
            _v3 = p3;

            computeNormal();

            _center = maths::Vector3f {
                (_v1.x + _v2.x + _v3.x) / 3,
                (_v1.y + _v2.y + _v3.y) / 3,
                (_v1.z + _v2.z + _v3.z) / 3,
            };
        }

        inline maths::Vector3f normalSurface([[maybe_unused]] const maths::Vector3f &p) const override
        {
            return _normal.normalize();
        }

        inline maths::Vector3f const &center() const override
        {
            return _center;
        }

        inline void setMaterial(const Material &material)
        {
            _material = material;
        }

        Color color(const maths::Vector3f &point) const override;

    private:

        maths::Vector3f _v1;
        maths::Vector3f _v2;
        maths::Vector3f _v3;
        maths::Vector3f _center;
        maths::Vector3f _normal;
        float _d;
    };
}