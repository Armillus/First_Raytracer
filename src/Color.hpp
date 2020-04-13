#pragma once

namespace rt {

    class Color {
    public:
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
            : r(r), g(g), b(b), a(a)
        {}

        Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255)
            : r(r), g(g), b(b), a(a)
        {}

        Color(float r, float g, float b, float a = 1)
            : r(r * 255.f), g(g * 255.f), b(b * 255.f), a(a * 255.f)
        {}

        ~Color() = default;

        inline Color &operator+=(const Color &color)
        {
            r = std::min(r + color.r, 255);
            g = std::min(g + color.g, 255);
            b = std::min(b + color.b, 255);

            return *this;
        }

        inline Color operator+(const Color &color)
        {
            unsigned int red = std::min(r + color.r, 255);
            unsigned int green = std::min(g + color.g, 255);
            unsigned int blue = std::min(b + color.b, 255);

            return Color(red, green, blue);
        }

        inline Color operator-(const Color &color)
        {
            unsigned int red = std::max(r - color.r, 0);
            unsigned int green = std::max(g - color.g, 0);
            unsigned int blue = std::max(b - color.b, 0);

            return Color(red, green, blue);
        }

        inline Color operator*(const Color &color)
        {
            float red = (r / 255.f) * (color.r / 255.f);
            float green = (g / 255.f) * (color.g / 255.f);
            float blue = (b / 255.f) * (color.b / 255.f);

            // printf("Original : red = %d | green = %d | blue = %d\n", r, g, b); 
            // printf("Other color : red = %d | green = %d | blue = %d\n", color.r, color.g, color.b); 
            // printf("New : red = %f | green = %f | blue = %f\n\n", red, green, blue);
            return Color(red, green, blue);
        }

        inline Color operator*(float scalar)
        {
            float red = (r / 255.f) * scalar;
            float green = (g / 255.f) * scalar;
            float blue = (b / 255.f) * scalar;

            return Color(red, green, blue);
        }

        inline bool isBlack(void)
        {
            return r == 0 && g == 0 && b == 0;
        }

        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

}