#pragma once

#include <limits>

#include "Renderer.hpp"

namespace rt {

    enum Options {
        None = 0,
        Shadows = 1,
        Reflections = 2,
        Refractions = 4,
        Illumination = 8,
    };

    auto constexpr const DEFAULT_OPTIONS = Shadows | Reflections | Illumination;
    auto constexpr const DEFAULT_REFLECTIONS_DEPTH = 20u;

    auto constexpr const DEFAULT_BIAS = 0.5f;

    class RayTracer : public Renderer {
    public:
        RayTracer(const Resolution &screenRes, uint startingOptions = DEFAULT_OPTIONS);
        ~RayTracer() override = default;

        void render(const Scene &scene, const Camera &camera) override;
        void render(const Scene &scene, const Camera &camera, uint reflectionsDepth);

        inline void enableOptions(uint options)
        {
            _enabledOptions |= options;
        }

        inline void disableOptions(uint options)
        {
            _enabledOptions &= options;
        }

    private:
        Color computePixelColor(const Scene &scene, const Ray &ray, uint depth, float reflectionCoeff, bool isPrimaryRay);
        std::pair<std::shared_ptr<Object>, float> findClosestObject(const Scene &scene, const Ray &ray);

        Color computeLightsAndShadows(const Scene &scene, const Ray &ray, std::shared_ptr<Object> object, float t);
        Color computeGlobalIllumination(const Scene &scene, const Ray &ray, std::shared_ptr<Object> object, float t);
        bool isShadowed(const Scene &scene, const Ray &shadowRay, const maths::Vector3f &distanceFromPtoLight);
        bool detectShadows(const Scene &scene, const Ray &shadowRay, const maths::Vector3f &distanceFromPtoLight);

        Color computeReflections(const Scene &scene, const Ray &ray,
                                 std::shared_ptr<Object> object, float t,
                                 uint depth, float reflectionCoeff);

        uint _enabledOptions;
        uint _reflectionsDepth;
    };


}