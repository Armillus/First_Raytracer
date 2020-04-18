#pragma once

#include <cstdint>

#include "Color.hpp"
#include "Resolution.hpp"

namespace rt {

    class FrameBuffer {
    public:
        FrameBuffer(unsigned int width, unsigned int height);
        ~FrameBuffer();

        void resize(const Resolution &screenRes);
        void resize(unsigned int width, unsigned int height);
        void updatePixelColor(unsigned int x, unsigned int y, const Color &color);

        inline const auto constexpr buffer(void) const
        {
            return _buffer;
        }
        
        inline void destroy(void)
        {
            if (_buffer)
                delete[] _buffer;
        }

    private:
        inline uint32_t *createBuffer(unsigned int width, unsigned int height)
        {
            return (new uint32_t[width * height]);
        }

        uint32_t *_buffer;
        unsigned int _screenWidth;
    };

}