#include "Renderer.hpp"

rt::Renderer::Renderer(const Resolution &screenRes)
    : _frameBuffer(screenRes.width, screenRes.height),
    _screenResolution(screenRes)
{
}