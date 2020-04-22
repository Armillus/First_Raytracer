#include "SfmlTexture.hpp"

#include <cmath>

rt::SfmlTexture::SfmlTexture(const std::string &filepath)
{
    loadFromFile(filepath);
}

rt::Color rt::SfmlTexture::getTextureColor(uint x, uint y) const
{
    // auto size = _image.getSize();
   // std::cout << "AFTER : x = " << x << " | y = " << y << " | size = " << size.x << ", " << size.y << std::endl;

    return (Color(_image.getPixel(x, y)));

}

rt::Color rt::SfmlTexture::getTextureColor(float x, float y) const
{
    auto size = _image.getSize();

    return (Color(_image.getPixel(x * size.x, y * size.y)));
}

void rt::SfmlTexture::loadFromFile(const std::string &filepath)
{
    if (_image.loadFromFile(filepath))
        _isLoaded = true;
}