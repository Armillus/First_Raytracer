#pragma once

#include "Color.hpp"
#include "Vector3.hpp"

namespace rt {

    class ILight {
    public:
        virtual ~ILight() = default;

        // Getting props.
        virtual const maths::Vector3f &position() const = 0;
        virtual const Color &color() const = 0;

        // Different for all types of lights.
        virtual maths::Vector3f directionFrom(const maths::Vector3f &hitPoint) const = 0;
        virtual float intensity(const maths::Vector3f &hitPoint) const = 0;
        virtual float distance(const maths::Vector3f &hitPoint) const = 0;

    };
}