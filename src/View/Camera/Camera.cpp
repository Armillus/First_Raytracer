#include "Camera.hpp"

rt::Camera::Camera(const maths::Vector3f &origin, const maths::Vector3f &lookAt, const Resolution &screenRes, float fieldOfView)
    : _origin(origin), _direction((lookAt - origin).normalize()),
    _up(0, 1, 0), _right(_direction.cross(_up)),
    _imagePlane(screenRes),
    _fov(maths::toRadians(fieldOfView)), _aspectRatio(0), _hasChanged(true)
{
    _up = _right.cross(_direction);
    resizeImagePlane(_imagePlane);
}

rt::Camera::Camera(float x, float y, float z, uint width, uint height, float fieldOfView)
    : _origin(x, y, z), _direction((-_origin).normalize()),
    _up(0, 1, 0), _right(_direction.cross(_up)),
    _imagePlane({width, height}),
    _fov(maths::toRadians(fieldOfView)), _aspectRatio(0), _hasChanged(true)
{
    _up = _right.cross(_direction);
    resizeImagePlane(_imagePlane);
}
