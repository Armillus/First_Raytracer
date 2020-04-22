#pragma once

#include "Ray.hpp"
#include "Resolution.hpp"
#include "Trigonometry.hpp"

namespace rt {

    auto constexpr const DEFAULT_FOV = 45.0f;

    class Camera {
    public:
        Camera(const maths::Vector3f &origin, const maths::Vector3f &lookAt, const Resolution &screenRes, float fieldOfView = DEFAULT_FOV);
        Camera(float x, float y, float z, uint width, uint height, float fieldOfView = DEFAULT_FOV);
        virtual ~Camera() = default;

        virtual Ray getPrimaryRay(uint x, uint y) const;

        inline void setOrigin(const maths::Vector3f &newOrigin)
        {
            _origin = newOrigin;
            _hasChanged = true;
        }

        inline void setFieldOfView(float newFov)
        {
            _fov = maths::toRadians(newFov);
            _hasChanged = true;
        }

        inline void wasRendered(void)
        {
            if (_hasChanged)
                _hasChanged = false;
        }

        inline void resizeImagePlane(uint width, uint height)
        {
            Resolution screenRes = {width, height};

            resizeImagePlane(screenRes);
        }

        inline void resizeImagePlane(const Resolution &screenRes)
        {
            _imagePlane = screenRes;
            computeAspectRatio();
            _hasChanged = true;
        }

        inline auto constexpr &origin(void)
        {
            _hasChanged = true;
            return _origin;
        }

        inline auto constexpr &direction(void)
        {
            _hasChanged = true;
            return _direction;
        }

        inline void computeDirection(void)
        {
            // _direction = (-_origin).normalize();
            // _right = _direction.cross(_up);
        }

        inline auto constexpr hasChangedSinceLastFrame(void)
        {
            if (!_hasChanged)
                return (false);

            _hasChanged = false;

            return (true);
        }

    private:
        inline constexpr float normalizePixelInX(uint x) const
        {
            uint width = _imagePlane.width;

            return ((2 * ((x + 0.5) / width) - 1) * tan(_fov) * _aspectRatio);
        }

        inline constexpr float normalizePixelInY(uint y) const
        {
            uint height = _imagePlane.height;

            return (1 - 2 * ((y + 0.5) / height)) * tan(_fov);
        }

        inline void computeAspectRatio(void)
        {
            _aspectRatio = _imagePlane.width / (float) _imagePlane.height;
        }

    protected:
        maths::Vector3f _origin;
        maths::Vector3f _direction;
        maths::Vector3f _up;
        maths::Vector3f _right;
        Resolution _imagePlane;
        float _fov;
        float _aspectRatio;
        bool _hasChanged;
    };

}