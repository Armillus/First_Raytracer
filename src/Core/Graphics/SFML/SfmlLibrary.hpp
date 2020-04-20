#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "IGraphicalLibrary.hpp"

namespace rt {

    class SfmlLibrary : public IGraphicalLibrary {
    public:
        SfmlLibrary(const Resolution &screenRes,
                    const std::string &windowTitle);

        ~SfmlLibrary() override = default;

        inline void setResizeCallback(const resizeCallback &callback) override
        {
            _resizeCallback = callback;
        }

        inline bool shouldClose() const override
        {
            return !_isAlive;
        }

        std::queue<Event> handleEvents(void) override;

        inline void clear(const Color &color = Color::Black) override
        {
            sf::Color clearColor(color.r, color.g, color.b, color.a);

            _window.clear(clearColor);
        }
    
        inline void draw(const FrameBuffer &frameBuffer) override
        {
            _texture.update(static_cast<sf::Uint8 *>(frameBuffer.buffer()));
            _window.draw(_sprite);
        }

        inline void display(void) override
        {
            _window.display();
        }

        inline void setFramerateLimit(uint limit = 60u)
        {
            _window.setFramerateLimit(limit);
        }

    private:

        inline constexpr bool screenResolutionHasChanged(const sf::Vector2u &screenRes)
        {
            return (_screenResolution.height != screenRes.y ||
                    _screenResolution.width != screenRes.x);
        }

        void checkResolutionSettings();

        void initDrawableElement();
        void centerWindowOnScreen();
        void fillKeymap();

        std::unordered_map<int, rt::Event> _keymap;
        resizeCallback _resizeCallback;
        sf::RenderWindow _window;
        sf::Sprite _sprite;
        sf::Texture _texture;
        Resolution _screenResolution;
        bool _isAlive;
    };

}