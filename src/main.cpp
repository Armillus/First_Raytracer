#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Sphere.hpp"
#include "Light.hpp"

static void renderInAscii(void)
{
    rt::Sphere s({20.f, 20.f, 20.f}, 10);
    rt::Ray r({0.f, 0.f, 0.f}, {0.f, 0.f, 1.f});
    float t = 20000.0;

    for (unsigned int x = 0; x < 40; ++x)
    {
        r.origin().x = x;
        for (unsigned int y = 0; y < 40; ++y)
        {
            r.origin().y = y;

            if (s.intersect(r, &t))
            {
                std::cout << "++";
            }
            else
            {
                std::cout << "--";
            }
        }
        std::cout << std::endl;
    }
}

static void fillFramebuffer(sf::Uint8 *pixels, unsigned int width, unsigned int height)
{
    std::vector<rt::Sphere> objects;
    std::vector<rt::Light> lights;
    rt::Ray r({0.f, 0.f, -2000.f}, {0.f, 0.f, 1.f});
    sf::Color blue = sf::Color::Blue;
    sf::Color cyan = sf::Color::Cyan;
    sf::Color magenta = sf::Color::Magenta;
    rt::Color ambientLight(0.2f, 0.2f, 0.2f);

    objects.push_back(rt::Sphere({500.f, 300.f, -10.f}, 100, {blue.r, blue.g, blue.b}));
    objects.push_back(rt::Sphere({100.f, 100.f, 0.f}, 100, {cyan.r, cyan.g, cyan.b}));
    objects.push_back(rt::Sphere({300.f, 500.f, 0.f}, 100, {magenta.r, magenta.g, magenta.b}));
    
    //lights.emplace_back(rt::Light({0.f, 240.f, -100.f}, {1.f, 1.f, 1.f}));
    //lights.emplace_back(rt::Light({3200.f, 3000.f, -1000.f}, {0.6f, 0.7f, 1.f}));
    lights.emplace_back(rt::Light({600.f, 0.f, -100.f}, {0.3f, 0.5f, 1.f}));

    for (unsigned int y = 0; y < height; ++y)
    {
        r.origin().y = y;
        for (unsigned int x = 0; x < width; ++x)
        {
            float t = 20000.0f;
            r.origin().x = x;

            unsigned int i = (x + y * width) * 4;
            rt::Sphere *obj = nullptr;

            for (auto &object : objects)
            {
                if (object.intersect(r, &t))
                {
                    obj = &object;
                }
            }
            if (obj)
            {
                auto V = r.direction();
                auto P = r.origin() + V * t;
                auto N = obj->normalSurface(P);

                auto color = obj->color() * ambientLight;
                auto diffuseCoeff = rt::Color(1.f, 1.f, 1.f) - ambientLight;

                for (auto &light : lights)
                {
                    bool shadowed = false;
                    auto distanceFromPtoLight = light.position() - P;
                    auto shadowRay = rt::Ray(P, distanceFromPtoLight.normalize());
                    float scalar = shadowRay.direction() * N;

                    // This part of the object isn't lit.
                    if (scalar < 0.0f)
                        continue;

                    t = 20000;
                    for (auto &object : objects)
                    {
                        if (object.intersect(shadowRay, &t))
                        {
                            auto distanceFromPtoObject = shadowRay.origin() - object.center();
                            
                            if (t > 0.01 && distanceFromPtoObject.norm() < distanceFromPtoLight.norm())
                            {
                                shadowed = true;
                                break;
                            }
                        }
                    }

                    if (!shadowed)
                    {
                        color += light.color() * diffuseCoeff * scalar;
                    }
                    else
                    {
                        color = color * 0.99;
                    }
                    
                }
                // float facing_ratio = N * V;

                // std::cout << N << std::endl;
                
               // auto color = obj->color() * (facing_ratio * 0.5);
            
                pixels[i] = color.r;
                pixels[i + 1] = color.g;
                pixels[i + 2] = color.b;
                pixels[i + 3] = color.a;
            }
            else
            {
                auto color = rt::Color(0.2f, 0.2f, 0.2f);

                pixels[i] = color.r;
                pixels[i + 1] = color.g;
                pixels[i + 2] = color.b;
                pixels[i + 3] = 255;
            }
        }
    }
}

static void renderInSfml(void)
{
    unsigned int width = 1200;
    unsigned int height = 800;

    sf::Uint8 *pixels = new sf::Uint8[width * height * 4];

    sf::Texture texture;
    texture.create(width, height); 

    fillFramebuffer(pixels, width, height);

    texture.update(pixels);

    sf::Sprite sprite(texture); // needed to draw the texture on screen

    sf::RenderWindow window(sf::VideoMode(width, height), "My window");

    window.setFramerateLimit(60);

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // effacement de la fenêtre en noir
        window.clear(sf::Color::Black);

        // c'est ici qu'on dessine tout
        window.draw(sprite);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }
}

int main(void)
{
    renderInSfml();
    return (0);
}