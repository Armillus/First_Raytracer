#include <iostream>

#include "Core.hpp"

// static void fillFramebuffer(sf::Uint8 *pixels, unsigned int width, unsigned int height)
// {
//     rt::Scene scene;
//     rt::Camera camera({0, 0, 0});
//     std::list<rt::Object *> objects;
//     std::vector<rt::Light> lights;
//     rt::Ray ray({0.f, 00.f, 0.f}, {0.f, 0.f, -1.f});
//     sf::Color blue = sf::Color::Blue;
//     sf::Color cyan = sf::Color::Cyan;
//     sf::Color magenta = sf::Color::Magenta;
//     sf::Color yellow = sf::Color::Yellow;
//     rt::Color ambientLight(0.25f, 0.25f, 0.25f);

//     objects.push_back(new rt::Sphere({-150.f, -50.f, -400.f}, 150, {{blue.r, blue.g, blue.b}, 0.45f}));
//     objects.push_back(new rt::Sphere({-800.f, 100.f, -1000.f}, 200, {{cyan.r, cyan.g, cyan.b}, 0.75}));
//     objects.push_back(new rt::Sphere({175.f, -50.f, -500.f}, 150, {{magenta.r, magenta.g, magenta.b}, 0.5f}));


//     lights.emplace_back(rt::Light({-300.f, 200.f, -200.f}, {1.f, 1.f, 1.f}));
//     //lights.emplace_back(rt::Light({3200.f, 3000.f, -1000.f}, {0.6f, 0.7f, 1.f}));
//    // lights.emplace_back(rt::Light({600.f, 300.f, -1000.f}, {1.0f, 0.25f, 0.25f}));

//     // float imageAspectRatio = width / (float) height; // assuming width > height 
//     // float fov = 90.0;

//     for (unsigned int x = 0; x < width; ++x)
//     {
//         //float Py = (1 - 2 * ((y + 0.5) / height)) * tan(fov / 2.0 * M_PI / 180.0);
        
//         //ray.origin().y = y;
//         for (unsigned int y = 0; y < height; ++y)
//         {
//             //float Px = (2 * ((x + 0.5) / width) - 1) * tan(fov / 2 * M_PI / 180.0) * imageAspectRatio; 
//             //ray.origin().x = x;

//             //rt::Ray r(ray.origin(), rt::maths::Vector3f(Px, Py, -1) - ray.origin());
//             rt::Ray r(camera.getPrimaryRay(x, y, width, height));

//             //  std::cout << "Origin : " << r.origin() << " | Direction : " << r.direction() << std::endl;
//             //  std::cout << "Px : " << Px << " | Py " << Py << std::endl;
//             //  std::cout << "Result = " << rt::maths::Vector3f(Px, Py, 1) - r.origin() << std::endl;

//             unsigned int i = (x + y * width) * 4;
//             float reflectionCoeff = 1.0f;
//             int level = 10;
//             auto color = ambientLight;

//             do {
//                 float t = 20000.0f;
//                 rt::Object *obj = nullptr;

//                 for (auto &object : scene.objects())
//                 {
//                     if (object->intersect(r, &t))
//                     {
//                         obj = object.get();
//                     }
//                 }
//                // std::cout << "J = " << j << std::endl;
//                // if (closest == 3)
//                //     std::cout << "Closest = " << closest << std::endl;
//                 if (obj)
//                 {
//                     auto V = r.direction();
//                     auto P = r.origin() + V * t;
//                     auto N = obj->normalSurface(P);

//                     color = obj->color() * ambientLight;
//                     auto diffuseCoeff = rt::Color(1.f, 1.f, 1.f) - ambientLight;
//                     float bias = 0.5;

//                     for (auto &light : scene.lights())
//                     {
//                         bool shadowed = false;
//                         auto distanceFromPtoLight = light->position() - P;
//                         auto shadowRay = rt::Ray(P + N * bias, distanceFromPtoLight.normalize());
//                         float scalar = shadowRay.direction() * N;

//                         // This part of the object isn't lit.
//                         if (scalar < 0.0f)
//                             continue;

//                         t = 20000;
//                         for (auto &object : scene.objects())
//                         {
//                             if (object->intersect(shadowRay, &t))
//                             {
//                                 auto distanceFromPtoObject = shadowRay.origin() - object->center();
                                
//                                 if (t > 0.001f && distanceFromPtoObject.norm() < distanceFromPtoLight.norm())
//                                 {
//                                     shadowed = true;
//                                     break;
//                                 }
//                             }
//                         }

//                         if (!shadowed)
//                         {
//                             color += (light->color() * diffuseCoeff * scalar * reflectionCoeff);
//                         }
//                         // else
//                         // {
//                         //     //float facing_ratio = N * V;
//                         //     // std::cout << N << std::endl;
//                         //     //color = color * (facing_ratio * 0.5);
//                         //     color = color * 1.f;
//                         // }
//                     }
//                     rt::Ray reflectedRay(P, V - (N * 2.f * (V * N)));
//                     r = reflectedRay;
//                     reflectionCoeff *= obj->reflection();
//                 }
//                 level--;
//             } while (level > 0 && reflectionCoeff > 0.0f);
            
//             pixels[i] = color.r;
//             pixels[i + 1] = color.g;
//             pixels[i + 2] = color.b;
//             pixels[i + 3] = color.a;
//         }
//     }
// }

// static void renderInSfml(void)
// {
//     unsigned int width = 1200;
//     unsigned int height = 800;

//     sf::Uint8 *pixels = new sf::Uint8[width * height * 4];

//     sf::Texture texture;
//     texture.create(width, height); 

//     fillFramebuffer(pixels, width, height);

//     texture.update(pixels);

//     sf::Sprite sprite(texture); // needed to draw the texture on screen

//     sf::RenderWindow window(sf::VideoMode(width, height), "My window");

//     window.setFramerateLimit(60);

//     // on fait tourner le programme tant que la fenêtre n'a pas été fermée
//     while (window.isOpen())
//     {


//         // effacement de la fenêtre en noir
//         window.clear(sf::Color::Black);

//         // c'est ici qu'on dessine tout
//         window.draw(sprite);

//         // fin de la frame courante, affichage de tout ce qu'on a dessiné
//         window.display();
//     }
// }

int main(int argc, const char **argv)
{
    rt::Core core(argc, argv);

    return (core.run());
}