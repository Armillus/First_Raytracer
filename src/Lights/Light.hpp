#pragma once

#include "Color.hpp"
#include "Vector3.hpp"

namespace rt {

    class Light {
    public:
        Light(const maths::Vector3f &position, const Color &color)
            : _pos(position), _color(color)
        {}
        ~Light() = default;

        inline maths::Vector3f &position()
        {
            return _pos;
        }

        inline Color &color()
        {
            return _color;
        }

    private:
        maths::Vector3f _pos;
        Color _color;
    };

}