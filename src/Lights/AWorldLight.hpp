#pragma once

#include "ILight.hpp"

namespace rt {

    class AWorldLight : public ILight {
    public:

        AWorldLight(const maths::Vector3f &position, const Color &color, float intensity)
            : _pos       { position }
            , _intensity { intensity }
            , _color     { color     }
            {}

        inline const maths::Vector3f &position() const override
        {
            return _pos;
        }

        inline const Color &color() const override
        {
            return _color;
        }

    protected:
        maths::Vector3f _pos;
        float _intensity;
        Color _color;
    };

}