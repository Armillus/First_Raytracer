#pragma once

#include <functional>
#include <queue>

#include "FrameBuffer.hpp"
#include "Event.hpp"

namespace rt {

    typedef std::function<void (const Resolution &screenRes)> resizeCallback;

    class IGraphicalLibrary {
    public:
        virtual ~IGraphicalLibrary() = default;

        virtual void setResizeCallback(const resizeCallback &callback) = 0;

        virtual bool shouldClose(void) const = 0;

        virtual std::queue<Event> handleEvents(void) = 0;

        virtual void clear(const Color &color) = 0;
        virtual void draw(const FrameBuffer &frameBuffer) = 0;
        virtual void display(void) = 0;

    };
}