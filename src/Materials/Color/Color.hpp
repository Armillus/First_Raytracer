#pragma once

#include <algorithm>
#include <iostream>

namespace rt {

    using uint = unsigned int;

    class Color {
    public:
        template<typename T>
        Color(const T &color) : r(color.r), g(color.g), b(color.b), a(color.a) {}
        Color(uint r, uint g, uint b, uint a = 255);
        Color(float r, float g, float b, float a = 1.0f);
        Color(float value, float a = 1.0f);
        Color(uint value, uint a = 255);

        ~Color() = default;

        static const Color Black;
        static const Color White;

        inline constexpr Color &operator+=(const Color &color)
        {
            r = std::min(r + color.r, 255);
            g = std::min(g + color.g, 255);
            b = std::min(b + color.b, 255);

            return *this;
        }

        inline Color operator+(const Color &color)
        {
            uint red = std::min(r + color.r, 255);
            uint green = std::min(g + color.g, 255);
            uint blue = std::min(b + color.b, 255);

            return Color(red, green, blue);
        }

        inline Color operator-(const Color &color) const
        {
            uint red = std::max(r - color.r, 0);
            uint green = std::max(g - color.g, 0);
            uint blue = std::max(b - color.b, 0);

            return Color(red, green, blue);
        }

        inline Color operator*(const Color &color) const
        {
            float red = (r * color.r) / 255.f;
            float green = (g * color.g) / 255.f;
            float blue = (b * color.b) / 255.f;

            return Color(red, green, blue);
        }

        inline Color operator*(float scalar) const
        {
            float red = (r / 255.f) * scalar;
            float green = (g / 255.f) * scalar;
            float blue = (b / 255.f) * scalar;

            return Color(red, green, blue);
        }

        inline constexpr Color &operator*=(const Color &color)
        {
            r = (r * color.r) / 255.f;
            g = (g * color.g) / 255.f;
            b = (b * color.b) / 255.f;

            return *this;
        }

        inline constexpr Color &operator*=(float scalar)
        {
            r = (r / 255.f) * scalar;
            g = (g / 255.f) * scalar;
            b = (b / 255.f) * scalar;

            return *this;
        }

        inline constexpr bool isBlack(void) const
        {
            return r == 0 && g == 0 && b == 0;
        }

        inline constexpr unsigned int toInt(void) const
        {
            return (r | (g << 8) | (b << 16) | (a << 24));
        }

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    inline std::ostream &operator<<(std::ostream &stream, const Color &color)
    {
        stream << "Color(" << (int) color.r << ", " << (int) color.g << ", " << (int) color.b << ")";
        return (stream);
    }

}