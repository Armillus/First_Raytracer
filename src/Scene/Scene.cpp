#include <SFML/Graphics.hpp>

#include "Scene.hpp"

rt::Scene::Scene(float ambientLightCoeff)
    : _objects(), _lights(),
    _ambientLightCoeff(ambientLightCoeff), _hasChanged(true)
{
    createObjects();
    createLights();
}

void rt::Scene::createObjects(void)
{
    _objects.push_back(std::make_shared<rt::Sphere>(maths::Vector3f(-350.f, -50.f, -400.f), 
                        150, Material(sf::Color::Blue, 0.5f, 0.5f, 80.0f, 0.45f)));
    _objects.push_back(std::make_shared<rt::Sphere>(maths::Vector3f(-50.f, 400.f, -800.f),
                        200, Material(sf::Color::Cyan, 0.5f, 1.0f, 120.0f, 0.75f)));
    _objects.push_back(std::make_shared<rt::Sphere>(maths::Vector3f(275.f, -50.f, -500.f),
                        150, Material(sf::Color::Magenta, 0.5f, 0.7f, 108.0f, 0.5f)));

    _objects.push_back(std::make_shared<rt::Plane>(maths::Vector3f(0.f, 1.f, 0.f),
                        maths::Vector3f(0.f, -200.f, 0.f), Material(sf::Color::Yellow, 1.0f, 0.5f, 150.0f)));
    _objects.push_back(std::make_shared<rt::Plane>(maths::Vector3f(0.f, 0.f, -1.f),
                        maths::Vector3f(0.f, 0.f, -1000.f), Material(Color(0.7f, 0.7f, 0.7f), 1.0f, 1.0f, 10.0f, 1.0f)));
    // _objects.push_back(std::make_shared<rt::Plane>(maths::Vector3f(0.f, 0.f, -1.f),
    //                      maths::Vector3f(0.f, 0.f, 100.f), Material(Color(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0.0f, 1.0f)));
}

void rt::Scene::createLights(void)
{
    _lights.push_back(std::make_unique<rt::Light>(maths::Vector3f(-300.f, 200.f, -200.f), Color(1.f, 1.f, 1.f)));
    //_lights.emplace_back(rt::Light({3200.f, 3000.f, -1000.f}, {0.6f, 0.7f, 1.f}));
    _lights.push_back(std::make_unique<rt::Light>(maths::Vector3f(600.f, 300.f, -1000.f), Color(1.0f, 0.25f, 0.25f)));
}