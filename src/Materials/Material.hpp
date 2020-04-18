#pragma once

#include "Color.hpp"

namespace rt {

    class Material {
    public:
        Material(const Color &color, float diffuseCoeff, float specularCoeff, float shininess, float reflectivity = 0.0f, float refractiveIndex = 1.0f)
            : color(color), diffuseCoefficient(diffuseCoeff),
            specularCoefficient(specularCoeff), shininess(shininess),
            reflectivity(reflectivity), refractiveIndex(refractiveIndex)
        {}

        ~Material() = default;

        Color color;
        float diffuseCoefficient;
        float specularCoefficient;
        float shininess;
        float reflectivity;
        float refractiveIndex;
    };

}