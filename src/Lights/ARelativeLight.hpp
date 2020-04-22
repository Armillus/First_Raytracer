#pragma once

#include "ILight.hpp"

namespace rt {

    class ARelativeLight : public ILight {
    public:

        ARelativeLight(const maths::Vector3f &direction, const Color &color, float intensity)
            : _dir       { direction }
            , _color     { color     }
            , _intensity { intensity }
            {}

        inline const maths::Vector3f &position() const override
        {
            return _dir;
        }

        inline const Color &color() const override
        {
            return _color;
        }

    protected:
        maths::Vector3f _dir;
        Color _color;
        float _intensity;
    };

}