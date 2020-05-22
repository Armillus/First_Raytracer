#pragma once

#include "AWorldLight.hpp"

namespace rt {

    class SphericalLight : public AWorldLight {
    public:

        SphericalLight(const maths::Vector3f &position, const Color &color, float intensity)
            : AWorldLight { position, color, intensity }
            {}

        ~SphericalLight() override = default;

        // Getting the direction of the light from a point.
        inline maths::Vector3f directionFrom(const maths::Vector3f &hitPoint) const override
        {
            return _pos - hitPoint;
           // return (_pos - hitPoint).normalize();
        }

        inline maths::Vector3f directionFrom(const maths::Vector3f &hitPoint, int offset) const override
        {
            auto pos(_pos);

            pos.x -= offset;
            pos.y += offset;

            return pos - hitPoint;
        }

        inline maths::Vector3f directionFrom(const maths::Vector3f &hitPoint, int xOffset, int yOffset) const override
        {
            auto pos(_pos);

            pos.x += xOffset;
            pos.y += yOffset;

            return pos - hitPoint;
        }

        // Getting the intensity of the light.
        inline float intensity(const maths::Vector3f &hitPoint) const override
        {
            //std::cout << "INTENSITY = " << _intensity << std::endl;
            return _intensity / (float)(4.f * M_PI * (_pos - hitPoint).norm());
        }

        // Getting the distance .
        inline float distance(const maths::Vector3f &hitPoint) const override
        {
            return std::sqrt((_pos - hitPoint).norm());
        }
    };
}