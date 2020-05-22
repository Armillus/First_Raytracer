#pragma once

#include <list>
#include <memory>
#include <algorithm>
#include <string>

#include "DirectionalLight.hpp"
#include "SphericalLight.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

namespace rt {

    auto constexpr const STONE_TEXTURE_PATH = "./assets/textures/stone_HD.jpg";
    //auto constexpr const STONE_TEXTURE_PATH = "./assets/textures/axel_millot.jpg";
    auto constexpr const EARTH_TEXTURE_PATH = "./assets/textures/earth_HD.jpg";
    auto constexpr const GOLD_TEXTURE_PATH = "./assets/textures/gold_HD.jpg";
    auto constexpr const CHECKERBOARD_TEXTURE_PATH = "./assets/textures/checkerboard.jpg";

    class Scene {
    public:
        //Scene(const std::string &configFilepath) {}
        
        Scene(float ambientLightCoeff = 0.2f);
        
        virtual ~Scene() = default;

        inline auto constexpr const &objects(void) const
        {
            return (_objects);
        }

        inline auto constexpr const &lights(void) const
        {
            return (_lights);
        }

        inline void wasRendered(void)
        {
            if (_hasChanged)
                _hasChanged = false;
        }

        inline auto constexpr hasChangedSinceLastFrame(void)
        {
            if (!_hasChanged)
                return (false);

            _hasChanged = false;

            return (true);
        }

        inline float constexpr ambientLightCoefficient(void) const
        {
            return (_ambientLightCoeff);
        }

        // Creating objects and lights methods.
        std::vector<std::size_t> createObjects(ObjectType type, std::size_t numberOfInstances = 1);
        std::vector<std::size_t> createLights(LightType type, std::size_t numberOfInstances = 1);

        bool hasObject(std::size_t id) const;
        bool hasLight(std::size_t id) const;

        // Objects.
        void ochangeMaterial(std::size_t id, const Material &material);
        void ochangeCenter(std::size_t id, const rt::maths::Vector3f &center);
        void ochangeNormal(std::size_t id, const rt::maths::Vector3f &normal);
        void ochangeRadius(std::size_t id, float radius);
        void ochangePoints(std::size_t id, const maths::Vector3f &p1, const maths::Vector3f &p2, const maths::Vector3f &p3);
        void ochangeTexture(std::size_t id, const std::string &texture);

        // Lights.
        void lchangePosition(std::size_t id, const rt::maths::Vector3f &position);
        void lchangeDirection(std::size_t id, const rt::maths::Vector3f &direction);
        void lchangeColor(std::size_t id, const Color &color);
        void lchangeIntensity(std::size_t id, float intensity);

        std::size_t createObject(ObjectType type);
        std::size_t createLight(LightType type);

    private:
        void createScene();
        std::size_t addElementToList();

        typedef std::shared_ptr<IObject> (*objectFunc)();
        typedef std::shared_ptr<ILight> (*lightFunc)();

        std::unordered_map<ObjectType, objectFunc> _objectFactory = {
            { ObjectType::tSphere, []()->std::shared_ptr<IObject>
                { return std::make_shared<rt::Sphere>(
                    maths::Vector3f(0.f, 0.f, 0.f),
                    1.f,
                    Material(sf::Color::White, .1f, .1f, 80.f, .45f));
                }
            },
            { ObjectType::tPlane,  []()->std::shared_ptr<IObject>
                { return std::make_shared<rt::Plane>(
                    maths::Vector3f(0.f, 0.f, 0.f),
                    maths::Vector3f(0.f, 0.f, 0.f),
                    Material(sf::Color::White, .1f, .1f, 80.f, .45f));
                }
            },
            { ObjectType::tTriangle,  []()->std::shared_ptr<IObject>
                { return std::make_shared<rt::Triangle>(
                    maths::Vector3f(0.f, 0.f, 0.f),
                    maths::Vector3f(0.f, 0.f, 0.f),
                    maths::Vector3f(0.f, 0.f, 0.f),
                    Material(sf::Color::Blue, .1f, .5f, 150.f));//, .45f));
                }
            },
        };

        std::unordered_map<LightType, lightFunc> _lightFactory = {
            { LightType::Spherical,   []()->std::shared_ptr<ILight>
                { return std::make_shared<SphericalLight>(
                    maths::Vector3f(0.f, 0.f, 0.f),
                    Color(Color::White),
                    1.f);
                }
            },
            { LightType::Directional, []()->std::shared_ptr<ILight>
                { return std::make_shared<DirectionalLight>(
                    maths::Vector3f(0.f, 0.f, 0.f),
                    Color(Color::White),
                    1.f);
                }
            },
        };

    protected:
        std::unordered_map<std::size_t, std::shared_ptr<IObject>> _objects;
        std::unordered_map<std::size_t, std::shared_ptr<ILight>> _lights;

        std::vector<size_t> _elementIds;
        float _ambientLightCoeff;
        bool _hasChanged;
    };
}