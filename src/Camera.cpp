#include "Camera.hpp"

rt::Camera::Camera(const maths::Vector3f &origin, const Resolution &screenRes, float fieldOfView)
    : _origin(origin), _screenRes(screenRes),
    _fov(maths::toRadians(fieldOfView))
{
    resizeImagePlane(_screenRes);
}

rt::Camera::Camera(float x, float y, float z, unsigned int width, unsigned height, float fieldOfView)
    : _origin(x, y, z), _screenRes({width, height}),
    _fov(maths::toRadians(fieldOfView))
{
    resizeImagePlane(_screenRes);
}

rt::Ray rt::Camera::getPrimaryRay(unsigned int x, unsigned int y) const
{
    float dirX = normalizePixelInX(x);
    float dirY = normalizePixelInY(y);

    return rt::Ray(_origin, maths::Vector3f(dirX, dirY, -1));
}
