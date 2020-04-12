#pragma once

namespace rt {

    class Color {
    public:
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
            : r(r), g(g), b(b), a(a)
        {}
        ~Color() = default;

        unsigned int r;
        unsigned int g;
        unsigned int b;
        unsigned int a;
    };

}