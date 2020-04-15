#pragma once

#include "Vector3.hpp"

namespace rt {

    struct Resolution {
        float width;
        float height;
    };

    class Camera {
    public:
        Camera(const maths::Vector3f &origin, const maths::Vector3f &direction,
               const maths::Vector3f &orientation, float distanceFromOriginToViewPlane,
               float fieldOfView)
            : _origin(origin), _direction(direction), _orientation(orientation),
            _viewPlane(0, 0, -1), _fov(fieldOfView),
            _distanceFromOriginToViewPlane(distanceFromOriginToViewPlane)
        {}

        ~Camera() = default;

        maths::Vector3f _origin;
        maths::Vector3f _direction;
        maths::Vector3f _orientation;

        maths::Vector3f _viewPlane;
        Resolution _viewPlaneRes;

        Resolution _screenRes;
        float _fov;
        float _aspectRatio;

        float _distanceFromOriginToViewPlane;


    };

}