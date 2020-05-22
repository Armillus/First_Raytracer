#pragma once

#include "Object.hpp"

namespace rt {

    class Plane : public Object {
    public:
        Plane(const maths::Vector3f &normal,
              const maths::Vector3f &point, const Material &mat);
        Plane(const maths::Vector3f &normal,
              const maths::Vector3f &point, const Material &mat, const std::string &textureFilepath);

        ~Plane() override = default;

        bool intersect(const Ray &ray, float *t) const override;

        inline maths::Vector3f normalSurface([[maybe_unused]] const maths::Vector3f &p) const override
        {
            return _normal;
        }

        inline maths::Vector3f const &center() const override
        {
            return _point;
        }

        inline void setNormal(const maths::Vector3f &normal)
        {
            _normal = normal;
        }

        inline void setCenter(const maths::Vector3f &center)
        {
            _point = center;
        }

        inline void setMaterial(const Material &material)
        {
            _material = material;
        }

        Color color(const maths::Vector3f &point) const;


    private:
        void normalizeTextureCoordinates(long int &x, long int &y) const;

        maths::Vector3f _normal;
        maths::Vector3f _point;
    };

}