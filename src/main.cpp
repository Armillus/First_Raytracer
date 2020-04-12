#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Sphere.hpp"

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

            if (s.intersects(r, &t))
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
    rt::Ray r({0.f, 0.f, -2000.f}, {0.f, 0.f, 1.f});
    sf::Color blue = sf::Color::Blue;
    sf::Color cyan = sf::Color::Cyan;
    sf::Color magenta = sf::Color::Magenta;

    objects.push_back(rt::Sphere({500.f, 300.f, 0.f}, 100, {blue.r, blue.g, blue.b}));
    objects.push_back(rt::Sphere({100.f, 100.f, 0.f}, 100, {cyan.r, cyan.g, cyan.b}));
    objects.push_back(rt::Sphere({300.f, 500.f, 0.f}, 100, {magenta.r, magenta.g, magenta.b}));
    

    for (unsigned int y = 0; y < height; ++y)
    {
        r.origin().y = y;
        for (unsigned int x = 0; x < width; ++x)
        {
            float t = 20000.0;
            r.origin().x = x;

            unsigned int i = (x + y * width) * 4;
            rt::Sphere *obj = nullptr;

            for (auto &object : objects)
            {
                if (object.intersects(r, &t))
                {
                    obj = &object;
                }
            }
            if (obj)
            {
                auto color = obj->color();

                pixels[i] = color.r;
                pixels[i + 1] = color.g;
                pixels[i + 2] = color.b;
                pixels[i + 3] = color.a;

                auto p = r.direction() * t + r.origin();

                
            }
            else
            {
                pixels[i] = 0;
                pixels[i + 1] = 0;
                pixels[i + 2] = 0;
                pixels[i + 3] = 255;
            }
            i += 4;
        }
    }
}

static void renderInSfml(void)
{
    unsigned int width = 800;
    unsigned int height = 600;

    sf::Uint8 *pixels = new sf::Uint8[width * height * 4];

    sf::Texture texture;
    texture.create(width, height); 

    fillFramebuffer(pixels, width, height);

    texture.update(pixels);

    sf::Sprite sprite(texture); // needed to draw the texture on screen

    sf::RenderWindow window(sf::VideoMode(width, height), "My window");

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