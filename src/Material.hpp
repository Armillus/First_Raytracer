#pragma once

#include "Color.hpp"

namespace rt {

    class Material {
    public:
        Material(const Color &color, float reflection = 0)
            : color(color), reflection(reflection)
        {}

        ~Material() = default;

        Color color;
        float reflection;
    };

}