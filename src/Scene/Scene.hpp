#pragma once

#include <list>
#include <memory>
#include <algorithm>
#include <string>

#include "Sphere.hpp"
#include "Plane.hpp"
#include "Light.hpp"

namespace rt {

    auto constexpr const DEFAULT_STONE_TEXTURE_PATH = "./assets/textures/stone_HD.jpg";
    auto constexpr const DEFAULT_EARTH_TEXTURE_PATH = "./assets/textures/earth_HD.jpg";
    auto constexpr const DEFAULT_GOLD_TEXTURE_PATH = "./assets/textures/gold_HD.jpg";
    auto constexpr const DEFAULT_CHECKERBOARD_TEXTURE_PATH = "./assets/textures/checkerboard.jpg";

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

        inline float constexpr diffuseLightCoefficient(void) const
        {
            return (1.0f - _ambientLightCoeff);
        }

    private:
        void createObjects();
        void createLights();

    protected:
        std::list<std::shared_ptr<Object>> _objects;
        std::list<std::shared_ptr<Light>> _lights;
        float _ambientLightCoeff;
        bool _hasChanged;
    };

}