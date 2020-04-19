#pragma once

#include "IGraphicalLibrary.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

namespace rt {

    class Viewer {
    public:
        Viewer(const Resolution &screenRes) : _camera(0, 0, 0, screenRes.width, screenRes.height) {}
        Viewer(const Scene &scene, const Camera &camera);
        virtual ~Viewer() = default;

        void show(std::unique_ptr<IGraphicalLibrary> &graphicLibrary,
                  std::unique_ptr<Renderer> &renderer);

        inline void setCamera(const Camera &camera)
        {
            _camera = camera;
        }

        inline void setScene(const Scene &scene)
        {
            _scene = scene;
        }

        inline void moveCamToRight(float step = 1.0f)
        {
            _camera.origin().x += step;
        }

        inline void moveCamToLeft(float step = 1.0f)
        {
            _camera.origin().x -= step;
        }

        inline void moveCamUp(float step = 1.0f)
        {
            _camera.origin().y += step;
        }

        inline void moveCamDown(float step = 1.0f)
        {
            _camera.origin().y -= step;
        }

        inline void changeScreenResolution(const Resolution &screenRes)
        {
            _camera.resizeImagePlane(screenRes);
        }

    private:
        Scene _scene;
        Camera _camera;
    };

}