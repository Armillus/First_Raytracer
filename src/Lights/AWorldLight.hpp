#pragma once

#include "ALight.hpp"

namespace rt {

    class AWorldLight : public ALight {
    public:

        AWorldLight(const maths::Vector3f &position, const Color &color, float intensity)
            : ALight(color, intensity, Spherical)
            , _pos       { position }
        {
        }

        inline const maths::Vector3f &position() const override
        {
            return _pos;
        }

        inline void setPosition(const maths::Vector3f &position)
        {
            _pos = position;
        }

    protected:
        maths::Vector3f _pos;
    };

}