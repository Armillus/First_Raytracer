#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "IGraphicalLibrary.hpp"

namespace rt {

    class SfmlLibrary : public IGraphicalLibrary {
    public:
        SfmlLibrary(const Resolution &screenRes, const std::string &windowTitle)
            : _window(sf::VideoMode(screenRes.width, screenRes.height), windowTitle),
            _screenResolution(screenRes), _isAlive(true)
        {
            _texture.create(screenRes.width, screenRes.height);
            _sprite.setTexture(_texture);
            _window.setFramerateLimit(60);

            auto desktop = sf::VideoMode::getDesktopMode();
            int x = desktop.width / 2 - _window.getSize().x / 2;
            int y = desktop.height / 2 - _window.getSize().y / 2;
            _window.setPosition({x, y});
        }

        ~SfmlLibrary() override = default;

        void setResizeCallback(const resizeCallback &callback) override
        {
            _resizeCallback = callback;
        }

        bool shouldClose() override
        {
            return !_isAlive;
        }

        std::queue<Event> handleEvents(void) override
        {
            sf::Event event;

            while (_window.pollEvent(event))
            {
                // fermeture de la fenêtre lorsque l'utilisateur le souhaite
                if (event.type == sf::Event::Closed)
                {
                    _window.close();
                    _isAlive = false;
                }
            }

            checkResolutionSettings();

            return std::queue<Event>();
        }

        inline void clear(const Color &color) override
        {
            sf::Color clearColor(color.r, color.g, color.b, color.a);

            _window.clear(clearColor);
        }
    
        inline void draw(const FrameBuffer &frameBuffer) override
        {
            _texture.update((sf::Uint8 *)(frameBuffer.buffer()));
            _window.draw(_sprite);
        }

        inline void display(void) override
        {
            _window.display();
        }

    private:
        void checkResolutionSettings(void)
        {
            auto screenRes = _window.getSize();

            if (screenResolutionHasChanged(screenRes))
            {
                _screenResolution.width = screenRes.x;
                _screenResolution.height = screenRes.y;
                _resizeCallback(_screenResolution);
            }
        }

        inline constexpr bool screenResolutionHasChanged(const sf::Vector2u &screenRes)
        {
            return (_screenResolution.height != screenRes.y ||
                    _screenResolution.width != screenRes.x);
        }

        resizeCallback _resizeCallback;
        sf::RenderWindow _window;
        sf::Sprite _sprite;
        sf::Texture _texture;
        Resolution _screenResolution;
        bool _isAlive;
    };

}