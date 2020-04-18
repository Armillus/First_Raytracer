#pragma once

#include "Vector3.hpp"

namespace rt {

    class Ray {
    public:
        Ray(const maths::Vector3f &origin, const maths::Vector3f &direction)
            : _origin(origin), _direction(direction.normalize())
        {
            
        }

        ~Ray() = default;


        inline const maths::Vector3f &origin() const
        {
            return _origin;
        }

        inline const maths::Vector3f &direction() const
        {
            return _direction;
        }

    private:
        maths::Vector3f _origin;
        maths::Vector3f _direction;
    };

}