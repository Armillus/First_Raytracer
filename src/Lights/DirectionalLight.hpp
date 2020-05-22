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
            return -_dir;
        }

        inline maths::Vector3f directionFrom([[maybe_unused]] const maths::Vector3f &hitPoint, int offset) const override
        {
            auto pos(-_dir);

            // pos.x -= offset;
            // pos.y += offset;
            pos.z += offset;

            return pos;
        }

        inline maths::Vector3f directionFrom([[maybe_unused]] const maths::Vector3f &hitPoint, int xOffset, int yOffset) const override
        {
            auto pos(-_dir);

            // pos.x -= offset;
            // pos.y += offset;
            pos.z += xOffset + yOffset;

            return pos;
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