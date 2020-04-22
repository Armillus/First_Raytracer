#pragma once

#include <limits>
#include <thread>
#include <chrono>
#include <future>
#include <algorithm>

#include "Renderer.hpp"

namespace rt {

    enum Options {
        None = 0,
        Shadows = 1,
        Reflections = 2,
        Refractions = 4,
        Illumination = 8,
    };

    // only needed for thread developpement
    auto constexpr const TIME_DEBUG = false;


    auto constexpr const DEFAULT_OPTIONS = Shadows | Reflections | Illumination | Refractions;
    auto constexpr const DEFAULT_REFLECTIONS_DEPTH = 10u;

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
        Color computePixelColor(const Scene &scene, const Ray &ray, uint depth, float reflectionCoeff, float refractionCoeff, bool isPrimaryRay);
        std::optional<std::pair<std::shared_ptr<rt::Object>, float>>  findClosestObject(const Scene &scene, const Ray &ray);

        Color computeLightsAndShadows(const Scene &scene, const Ray &ray, std::shared_ptr<Object> object, float t);
        Color computeGlobalIllumination(const Scene &scene, const Ray &ray, std::shared_ptr<Object> object, float t);
        bool isShadowed(const Scene &scene, const Ray &shadowRay, const maths::Vector3f &distanceFromPtoLight);
        bool detectShadows(const Scene &scene, const Ray &shadowRay, const maths::Vector3f &distanceFromPtoLight);

        Color computeReflections(const Scene &scene, const Ray &ray,
                                 std::shared_ptr<Object> object, float t,
                                 uint depth, float reflectionCoeff, float refractionCoeff);

        Color computeRefractions(const Scene &scene, const Ray &ray,
                                 std::shared_ptr<Object> object, float t,
                                 uint depth, float &reflectionCoeff, float refractionCoeff);

        float fresnel(const maths::Vector3f &I, maths::Vector3f &N, const float &ior) 
        { 
            float angle = I * N;
            float cosi = std::clamp(-1.0f, 1.0f, angle); 
            float etai = 1, etat = ior;
            if (cosi > 0) { std::swap(etai, etat); } 
            // Compute sini using Snell's law
            float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi)); 
            // Total internal reflection
            if (sint >= 1) { 
                return (1.0f);
            } 
            else { 
                float cost = sqrtf(std::max(0.f, 1 - sint * sint)); 
                cosi = fabsf(cosi); 
                float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
                float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
                return ((Rs * Rs + Rp * Rp) / 2.0f); 
            } 
            // As a consequence of the conservation of energy, transmittance is given by:
            // kt = 1 - kr;
        } 

        uint _enabledOptions;
        uint _reflectionsDepth;

        std::mutex _mutex;
    };


}