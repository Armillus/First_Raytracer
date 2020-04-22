#pragma once

#include "ARelativeLight.hpp"

namespace rt {

    class DirectionalLight : public ARelativeLight {
    public:

        DirectionalLight(const maths::Vector3f &direction, const Color &color, float intensity)
            : ARelativeLight { direction, color, intensity }
            {}

        ~DirectionalLight() override = default;

        // Getting the direction from the light.
        inline maths::Vector3f directionFrom([[maybe_unused]] const maths::Vector3f &hitPoint) const override
        {
            return (-_dir).normalize();
        }

        // Getting the intensity of the light.
        inline float intensity([[maybe_unused]] const maths::Vector3f &hitPoint) const override
        {
            return _intensity;
        }

        // Getting the intensity of the light.
        inline float distance([[maybe_unused]] const maths::Vector3f &hitPoint) const override
        {
            return INFINITY;
        }
    };
}