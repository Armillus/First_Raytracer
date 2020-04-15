#pragma once

#include "Vector3.hpp"

namespace rt {

    class Ray {
    public:
        Ray(const maths::Vector3f &origin, const maths::Vector3f &direction)
            : _origin(origin), _direction(direction)
        {
            _direction = _direction.normalize();
        }

        ~Ray() = default;


        inline maths::Vector3f &origin()
        {
            return _origin;
        }

        inline maths::Vector3f &direction()
        {
            return _direction;
        }

    private:
        maths::Vector3f _origin;
        maths::Vector3f _direction;
    };

}