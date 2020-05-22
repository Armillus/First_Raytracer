#pragma once

#include "Material.hpp"

namespace rt {

    class Dielectric : public Material {
    public:
        Dielectric(const Color &color, 
                   float diffuseCoeff, 
                   float specularCoeff,
                   float shininess = 100.0f,
                   float reflectivity = 0.5f,
                   float transmittance = 0.5f,
                   float refractiveIndex = 1.0f)
            : Material(color, 
                       diffuseCoeff,
                       specularCoeff,
                       shininess,
                       reflectivity,
                       transmittance,
                       refractiveIndex)
        {

        }

        ~Dielectric() override = default;

    };
}