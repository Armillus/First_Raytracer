#pragma once

#include "Color.hpp"

namespace rt {

    class Material {
    public:
        Material(const Color &color,
                 float diffuseCoeff,
                 float specularCoeff,
                 float shininess,
                 float reflectivity = 0.0f,
                 float transmittance = 0.0f,
                 float refractiveIndex = 1.0f)
            :   color(color),
                diffuseCoefficient(diffuseCoeff),
                specularCoefficient(specularCoeff),
                shininess(shininess),
                reflectivity(reflectivity),
                transmittance(transmittance),
                refractiveIndex(refractiveIndex)
        {

        }

        virtual ~Material() = default;

        Color color;
        float diffuseCoefficient;
        float specularCoefficient;
        float shininess;
        float reflectivity;
        float transmittance;
        float refractiveIndex;
    };

}