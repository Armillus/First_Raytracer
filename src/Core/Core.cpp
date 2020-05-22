#include "Core.hpp"

rt::Core::Core([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
    : _graphicLibrary(std::make_unique<SfmlLibrary>(
        DEFAULT_WIN_RES, DEFAULT_WIN_TITLE)),
    _renderer(std::make_unique<RayTracer>(DEFAULT_WIN_RES)),
    _viewer(DEFAULT_WIN_RES, argc, argv)
{
    setCallbacks();
}

void rt::Core::setCallbacks(void)
{
    //setEventsCallbacks();
    setResizeCallback();
}

void rt::Core::setEventsCallbacks(void)
{
    _eventsCallbacks[Event::Left] = [this](){ _viewer.moveCamToLeft(); };
    _eventsCallbacks[Event::Right] = [this](){ _viewer.moveCamToRight(); };
    _eventsCallbacks[Event::Up] = [this](){ _viewer.moveCameraForward(); };
    _eventsCallbacks[Event::Down] = [this](){ _viewer.moveCameraBackward(); };

    _eventsCallbacks[Event::W] = [this](){ _viewer.rotateCamUp(); };
    _eventsCallbacks[Event::A] = [this](){ _viewer.rotateCamToLeft(); };
    _eventsCallbacks[Event::D] = [this](){ _viewer.rotateCamToRight(); };
    _eventsCallbacks[Event::S] = [this](){ _viewer.rotateCamDown(); };

    _eventsCallbacks[Event::Q] = [this](){ _viewer.moveCamUp(); };
    _eventsCallbacks[Event::E] = [this](){ _viewer.moveCamDown(); };
}

void rt::Core::setResizeCallback(void)
{
    _graphicLibrary->setResizeCallback([this]
        (const Resolution &screenRes)
        {
            _renderer->setScreenResolution(screenRes);
            _viewer.changeScreenResolution(screenRes);
        }
    );
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
        auto callback = _eventsCallbacks.find(event);

        if (callback != _eventsCallbacks.end())
            callback->second();

        events.pop();
    }
}