#pragma once

#include "Material.hpp"

namespace rt {

    class Conductor : public Material {
    public:
        Conductor(const Color &color, 
                  float diffuseCoeff, 
                  float specularCoeff,
                  float shininess = 100.0f,
                  float reflectivity = 1.0f)
            : Material(color, 
                       diffuseCoeff,
                       specularCoeff,
                       shininess,
                       reflectivity,
                       0.0f, 0.0f)
        {

        }

        ~Conductor() override = default;

    };
}