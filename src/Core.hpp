#pragma once

#include "RayTracer.hpp"
#include "Viewer.hpp"
#include "SfmlLibrary.hpp"

namespace rt {

    auto constexpr const DEFAULT_WIN_TITLE = "EpiTracer";
    Resolution constexpr const DEFAULT_WIN_RES = {1200, 800};

    class Core {
    public:
        Core(int argc, const char **argv);
        ~Core() = default;

        int run(void);
        void setCallbacks(void);
        void loadScene();

    private:
        std::unique_ptr<IGraphicalLibrary> _graphicLibrary;
        std::unique_ptr<Renderer> _renderer;
        Viewer _viewer;
    };
}