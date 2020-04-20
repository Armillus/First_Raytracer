#include "Color.hpp"

namespace rt
{
    const Color Color::Black = Color(0.0f, 0.0f, 0.0f);
    const Color Color::White = Color(1.0f, 1.0f, 1.0f);

}

rt::Color::Color(uint r, uint g, uint b, uint a)
    : r(r), g(g), b(b), a(a)
{

}

rt::Color::Color(float r, float g, float b, float a)
    : r(r * 255.f), g(g * 255.f), b(b * 255.f), a(a * 255.f)
{

}

rt::Color::Color(uint value, uint a)
    : r(value), g(value), b(value), a(a)
{

}

rt::Color::Color(float value, float a)
    : r(value * 255.f), g(value * 255.f), b(value * 255.f), a(a * 255.f)
{

}

rt::Color::Color() 
    : r(0u), g(0u), b(0u), a(255u)
{

}
