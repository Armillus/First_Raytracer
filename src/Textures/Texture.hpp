#pragma once

#include "Color.hpp"

namespace rt {

    class Texture {
    public:
        Texture() : _isLoaded(false) {}
        virtual ~Texture() = default;

        virtual inline Color getTextureColor(float x, float y) const = 0;
        virtual inline Color getTextureColor(uint x, uint y) const = 0;

        virtual inline void loadFromFile(const std::string &filepath) = 0;

        inline constexpr bool isLoaded(void) const
        {
            return _isLoaded;
        }

        virtual uint width() const = 0;
        virtual uint height() const = 0;

    protected:
        bool _isLoaded;
    };
}