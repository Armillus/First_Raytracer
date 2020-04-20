#pragma once

#include <cstdint>

#include "Color.hpp"
#include "Resolution.hpp"

namespace rt {

    class FrameBuffer {
    public:
        FrameBuffer(uint width, uint height);
        ~FrameBuffer();

        void resize(const Resolution &screenRes);
        void resize(uint width, uint height);
        void updatePixelColor(uint x, uint y, const Color &color);

        inline constexpr void *buffer(void) const
        {
            return _buffer;
        }
        
        inline void destroy(void)
        {
            if (_buffer)
            {
                delete[] _buffer;
                _buffer = nullptr;
            }
        }

    private:
        inline uint32_t *createBuffer(uint width, uint height)
        {
            return (new uint32_t[width * height]);
        }

        uint32_t *_buffer;
        unsigned int _screenWidth;
    };

}