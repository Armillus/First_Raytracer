#include "Core.hpp"

rt::Core::Core([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
    : _graphicLibrary(std::make_unique<SfmlLibrary>(
        DEFAULT_WIN_RES, DEFAULT_WIN_TITLE)),
    _renderer(std::make_unique<RayTracer>(DEFAULT_WIN_RES)),
    _viewer(DEFAULT_WIN_RES)
{
    setCallbacks();
    loadScene();
}

void rt::Core::setCallbacks(void)
{
    _graphicLibrary->setResizeCallback([this]
        (const Resolution &screenRes)
        {
            _renderer->setScreenResolution(screenRes);
            _viewer.changeScreenResolution(screenRes);
        }
    );
}

void rt::Core::loadScene(void)
{
    //Scene scene;
    //Camera camera(0, 0, 0, );

    //_viewer.setScene(scene);
    //_viewer.setCamera(camera);
}

int rt::Core::run(void)
{
    while (!_graphicLibrary->shouldClose())
    {
        auto events = _graphicLibrary->handleEvents();

        processEvents(events);
        _viewer.show(_graphicLibrary, _renderer);
    }

    return (0);
}

void rt::Core::processEvents(std::queue<Event> &events)
{
    while (!events.empty())
    {
        Event event = events.back();

        switch (event)
        {
            case Left: _viewer.moveCamToLeft(); break;
            case Right: _viewer.moveCamToRight(); break;
            case Up: _viewer.moveCamUp(); break;
            case Down: _viewer.moveCamDown(); break;
            default: break;
        }

        events.pop();
    }
}