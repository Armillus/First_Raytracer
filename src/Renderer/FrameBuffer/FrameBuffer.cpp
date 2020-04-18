#include "FrameBuffer.hpp"

rt::FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
    : _buffer(createBuffer(width, height)), _screenWidth(width)
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

void rt::FrameBuffer::resize(unsigned int width, unsigned int height)
{
    destroy();
    _buffer = createBuffer(width, height);
    _screenWidth = width;
}

void rt::FrameBuffer::updatePixelColor(unsigned int x, unsigned int y, const Color &color)
{
    _buffer[x + y * _screenWidth] = color.toInt();
}