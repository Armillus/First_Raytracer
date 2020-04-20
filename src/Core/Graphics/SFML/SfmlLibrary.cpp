#include "SfmlLibrary.hpp"

rt::SfmlLibrary::SfmlLibrary(const Resolution &screenRes,
                             const std::string &windowTitle)
    : _window(sf::VideoMode(screenRes.width, screenRes.height),
              windowTitle),
    _screenResolution(screenRes), _isAlive(true)
{
    centerWindowOnScreen();
    initDrawableElement();
    setFramerateLimit();
    fillKeymap();
}

void rt::SfmlLibrary::initDrawableElement(void)
{
    _texture.create(_screenResolution.width, _screenResolution.height);
    _sprite.setTexture(_texture);
}

void rt::SfmlLibrary::centerWindowOnScreen(void)
{
    auto desktop = sf::VideoMode::getDesktopMode();
    auto winSize = _window.getSize();
    int x = desktop.width / 2 - winSize.x / 2;
    int y = desktop.height / 2 - winSize.y / 2;
    
    _window.setPosition({x, y});
}

void rt::SfmlLibrary::fillKeymap(void)
{
    this->_keymap[sf::Keyboard::Unknown] = Event::Undefined;
    this->_keymap[sf::Keyboard::A] = Event::A;
    this->_keymap[sf::Keyboard::B] = Event::B;
    this->_keymap[sf::Keyboard::C] = Event::C;
    this->_keymap[sf::Keyboard::D] = Event::D;
    this->_keymap[sf::Keyboard::E] = Event::E;
    this->_keymap[sf::Keyboard::F] = Event::F;
    this->_keymap[sf::Keyboard::G] = Event::G;
    this->_keymap[sf::Keyboard::H] = Event::H;
    this->_keymap[sf::Keyboard::I] = Event::I;
    this->_keymap[sf::Keyboard::J] = Event::J;
    this->_keymap[sf::Keyboard::K] = Event::K;
    this->_keymap[sf::Keyboard::L] = Event::L;
    this->_keymap[sf::Keyboard::M] = Event::M;
    this->_keymap[sf::Keyboard::N] = Event::N;
    this->_keymap[sf::Keyboard::O] = Event::O;
    this->_keymap[sf::Keyboard::P] = Event::P;
    this->_keymap[sf::Keyboard::Q] = Event::Q;
    this->_keymap[sf::Keyboard::R] = Event::R;
    this->_keymap[sf::Keyboard::S] = Event::S;
    this->_keymap[sf::Keyboard::T] = Event::T;
    this->_keymap[sf::Keyboard::U] = Event::U;
    this->_keymap[sf::Keyboard::V] = Event::V;
    this->_keymap[sf::Keyboard::W] = Event::W;
    this->_keymap[sf::Keyboard::X] = Event::X;
    this->_keymap[sf::Keyboard::Y] = Event::Y;
    this->_keymap[sf::Keyboard::Z] = Event::Z;
    this->_keymap[sf::Keyboard::F1] = Event::F1;
    this->_keymap[sf::Keyboard::F2] = Event::F2;
    this->_keymap[sf::Keyboard::F3] = Event::F3;
    this->_keymap[sf::Keyboard::F4] = Event::F4;
    this->_keymap[sf::Keyboard::F5] = Event::F5;
    this->_keymap[sf::Keyboard::F6] = Event::F6;
    this->_keymap[sf::Keyboard::F7] = Event::F7;
    this->_keymap[sf::Keyboard::F8] = Event::F8;
    this->_keymap[sf::Keyboard::F9] = Event::F9;
    this->_keymap[sf::Keyboard::F10] = Event::F10;
    this->_keymap[sf::Keyboard::F11] = Event::F11;
    this->_keymap[sf::Keyboard::F12] = Event::F12;
    this->_keymap[sf::Keyboard::Num0] = Event::Num0;
    this->_keymap[sf::Keyboard::Num1] = Event::Num1;
    this->_keymap[sf::Keyboard::Num2] = Event::Num2;
    this->_keymap[sf::Keyboard::Num3] = Event::Num3;
    this->_keymap[sf::Keyboard::Num4] = Event::Num4;
    this->_keymap[sf::Keyboard::Num5] = Event::Num5;
    this->_keymap[sf::Keyboard::Num6] = Event::Num6;
    this->_keymap[sf::Keyboard::Num7] = Event::Num7;
    this->_keymap[sf::Keyboard::Num8] = Event::Num8;
    this->_keymap[sf::Keyboard::Num9] = Event::Num9;
    this->_keymap[sf::Keyboard::Space] = Event::Space;
    this->_keymap[sf::Keyboard::Enter] = Event::Enter;
    this->_keymap[sf::Keyboard::Up] = Event::Up;
    this->_keymap[sf::Keyboard::Down] = Event::Down;
    this->_keymap[sf::Keyboard::Left] = Event::Left;
    this->_keymap[sf::Keyboard::Right] = Event::Right;
    this->_keymap[sf::Keyboard::Escape] = Event::Escape;
    this->_keymap[sf::Keyboard::Tab] = Event::Tab;
}

std::queue<rt::Event> rt::SfmlLibrary::handleEvents(void)
{
    std::queue<Event> events;
    sf::Event event;

    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _window.close();
            _isAlive = false;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (_keymap.find(event.key.code) != _keymap.end())
                events.push(_keymap[event.key.code]);
            else
                events.push(_keymap[sf::Keyboard::Unknown]);
        }
    }
    checkResolutionSettings();
    return events;
}

void rt::SfmlLibrary::checkResolutionSettings()
{
    auto screenRes = _window.getSize();

    if (screenResolutionHasChanged(screenRes))
    {
        _screenResolution.width = screenRes.x;
        _screenResolution.height = screenRes.y;
        _resizeCallback(_screenResolution);
        _texture.create(screenRes.x, screenRes.y);
    }
}