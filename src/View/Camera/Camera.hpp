#pragma once

#include "Ray.hpp"
#include "Resolution.hpp"
#include "Trigonometry.hpp"

namespace rt {

    auto constexpr const DEFAULT_FOV = 45.0f;

    class Camera {
    public:
        Camera(const maths::Vector3f &origin, const Resolution &screenRes, float fieldOfView = DEFAULT_FOV);
        Camera(float x, float y, float z, unsigned int width, unsigned int height, float fieldOfView = DEFAULT_FOV);
        virtual ~Camera() = default;

        virtual Ray getPrimaryRay(unsigned int x, unsigned int y) const;

        inline void setOrigin(const maths::Vector3f &newOrigin)
        {
            _origin = newOrigin;
        }

        inline void setFieldOfView(float newFov)
        {
            _fov = maths::toRadians(newFov);
        }

        inline void resizeImagePlane(unsigned int width, unsigned int height)
        {
            Resolution screenRes = {width, height};

            resizeImagePlane(screenRes);
        }

        inline void resizeImagePlane(const Resolution &screenRes)
        {
            _screenRes = screenRes;
            computeAspectRatio();
        }

    private:
        inline constexpr float normalizePixelInX(unsigned int x) const
        {
            unsigned int width = _screenRes.width;

            return ((2 * ((x + 0.5) / width) - 1) * tan(_fov) * _aspectRatio);
        }

        inline constexpr float normalizePixelInY(unsigned int y) const
        {
            unsigned int height = _screenRes.height;

            return (1 - 2 * ((y + 0.5) / height)) * tan(_fov);
        }

        inline void computeAspectRatio(void)
        {
            _aspectRatio = _screenRes.width / (float) _screenRes.height;
        }

    protected:
        maths::Vector3f _origin;
        Resolution _screenRes;
        float _fov;
        float _aspectRatio;
    };

}