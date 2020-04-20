#pragma once

#include "FrameBuffer.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

namespace rt {

    class Renderer {
    public:
        Renderer(const Resolution &screenRes);
        virtual ~Renderer() = default;

        virtual void render(const Scene &scene, const Camera &camera) = 0;

        inline auto constexpr &frameBuffer(void) const
        {
            return _frameBuffer;
        }

        inline void setScreenResolution(const Resolution &screenRes)
        {
            _screenResolution = screenRes;
            _frameBuffer.resize(screenRes);
        }

    protected:
        rt::FrameBuffer _frameBuffer;
        Resolution _screenResolution;
    };

}