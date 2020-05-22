#pragma once

#include "Color.hpp"
#include "Vector3.hpp"

namespace rt {

    enum LightType {
        Spherical,
        Directional
    };

    class ILight {
    public:
        virtual ~ILight() = default;

        // Getting props.
        virtual const maths::Vector3f &position() const = 0;
        virtual const Color &color() const = 0;
        virtual LightType const &type() const = 0;

        virtual void setIntensity(float intensity) = 0;
        virtual void setColor(const Color &color) = 0;

        // Different for all types of lights.
        virtual maths::Vector3f directionFrom(const maths::Vector3f &hitPoint) const = 0;
        virtual maths::Vector3f directionFrom(const maths::Vector3f &hitPoint, int offset) const = 0;
        virtual maths::Vector3f directionFrom(const maths::Vector3f &hitPoint, int xOffset, int yOffset) const = 0;
        virtual float intensity(const maths::Vector3f &hitPoint) const = 0;
        virtual float distance(const maths::Vector3f &hitPoint) const = 0;

    };
}

      