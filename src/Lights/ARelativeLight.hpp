#pragma once

#include "ALight.hpp"

namespace rt {

    class ARelativeLight : public ALight {
    public:

        ARelativeLight(const maths::Vector3f &direction, const Color &color, float intensity)
            : ALight(color, intensity, Directional)
            , _dir       { direction }
            {}

        inline const maths::Vector3f &position() const override
        {
            return _dir;
        }

        inline void setDirection(const maths::Vector3f &direction)
        {
            _dir = direction;
        }

    protected:
        maths::Vector3f _dir;
    };

}