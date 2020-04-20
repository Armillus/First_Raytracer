#pragma once

#include <SFML/Graphics.hpp>

#include "Texture.hpp"

namespace rt {

    class SfmlTexture : public Texture {
    public:
        SfmlTexture(const std::string &filepath);
        ~SfmlTexture() override = default;

        Color getTextureColor(float x, float y) const;
        Color getTextureColor(uint x, uint y) const;
        void loadFromFile(const std::string &filepath) override;

        inline uint width() const override
        {
            return _image.getSize().x;
        }

        inline uint height() const override
        {
            return _image.getSize().y;
        }

    private:
        sf::Image _image;
    };
}