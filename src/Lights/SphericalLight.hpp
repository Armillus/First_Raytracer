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
            return (_pos - hitPoint).normalize();
        }

        // Getting the intensity of the light.
        inline float intensity(const maths::Vector3f &hitPoint) const override
        {
            return _intensity / (4.f * M_PI * (_pos - hitPoint).norm());
        }

        // Getting the distance .
        inline float distance(const maths::Vector3f &hitPoint) const override
        {
            return std::sqrt((_pos - hitPoint).norm());
        }
    };
}