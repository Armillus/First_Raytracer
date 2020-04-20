#include "FrameBuffer.hpp"

rt::FrameBuffer::FrameBuffer(uint width, uint height)
    : _buffer(createBuffer(width, height)),
    _screenWidth(width)
{

}

rt::FrameBuffer::~FrameBuffer()
{
    destroy();
}

void rt::FrameBuffer::resize(const Resolution &screenRes)
{
    resize(screenRes.width, screenRes.height);
}

void rt::FrameBuffer::resize(uint width, uint height)
{
    destroy();
    _buffer = createBuffer(width, height);
    _screenWidth = width;
}

void rt::FrameBuffer::updatePixelColor(uint x, uint y, const Color &color)
{
    _buffer[x + y * _screenWidth] = color.toInt();
}