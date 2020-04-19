#include "RayTracer.hpp"

rt::RayTracer::RayTracer(const Resolution &screenRes, uint startingOptions)
    : Renderer(screenRes), _enabledOptions(startingOptions),
    _reflectionsDepth(DEFAULT_REFLECTIONS_DEPTH)
{

}

void rt::RayTracer::render(const Scene &scene, const Camera &camera)
{
    //std::cout << "Render begins..." << std::endl;
    render(scene, camera, _reflectionsDepth);
    //std::cout << "Render finished!" << std::endl;
}

void rt::RayTracer::render(const Scene &scene, const Camera &camera, uint reflectionsDepth)
{
    unsigned int width = _screenResolution.width;
    unsigned int height = _screenResolution.height;

    for (unsigned int x = 0; x < width; ++x)
    {
        for (unsigned int y = 0; y < height; ++y)
        {
            Ray primaryRay(camera.getPrimaryRay(x, y));
            Color pixelColor(computePixelColor(scene, primaryRay, reflectionsDepth, 1.0f, 1.0f, true));

            _frameBuffer.updatePixelColor(x, y, pixelColor);
        }
    }
}

rt::Color rt::RayTracer::computePixelColor(const Scene &scene, const Ray &ray, uint depth, float reflectionCoeff, float refractionCoeff, bool isPrimaryRay)
{
    Color pixelColor(scene.ambientLightCoefficient());

    auto closest = findClosestObject(scene, ray);
    auto closestObj = closest.first;
    auto t = closest.second;

    if (!closestObj)
        return (isPrimaryRay ? pixelColor : Color::Black);
    
    // Compute Lights and Shadows effects
    pixelColor *= closestObj->color();
    pixelColor += computeLightsAndShadows(scene, ray, closestObj, t);

    reflectionCoeff = closestObj->material().reflectivity;

    // Compute refractions
    refractionCoeff *= closestObj->material().transmittance;
    pixelColor += computeRefractions(scene, ray, closestObj, t, depth, reflectionCoeff, refractionCoeff);

    // Compute reflections
    //reflectionCoeff *= closestObj->material().reflectivity;
    //pixelColor *= (1.0f - reflectionCoeff);
    pixelColor += computeReflections(scene, ray, closestObj, t, depth, reflectionCoeff, refractionCoeff);

    return (pixelColor);
}

rt::Color rt::RayTracer::computeLightsAndShadows(const Scene &scene, const Ray &ray, std::shared_ptr<Object> object, float t)
{
    if (!(_enabledOptions & Illumination))
        return (Color::Black);

    return (computeGlobalIllumination(scene, ray, object, t));
}

rt::Color rt::RayTracer::computeGlobalIllumination(const Scene &scene, const Ray &ray, std::shared_ptr<Object> object, float t)
{
    Color pixelColor(Color::Black);
    float bias = DEFAULT_BIAS;

    auto V = ray.direction();

    // The intersection point
    auto P = ray.origin() + V * t;

    // The normal to the object surface
    auto N = object->normalSurface(P);

    for (auto &light : scene.lights())
    {
        auto distanceFromPtoLight = light->position() - P;
        maths::Vector3f shadowRayOrigin(P + N * bias);
        rt::Ray shadowRay(shadowRayOrigin, distanceFromPtoLight.normalize());
        float angle = shadowRay.direction() * N;

        // This part of the object isn't lit according to the Lambert law.
        if (angle < 0.0f)
            continue;

        if (!isShadowed(scene, shadowRay, distanceFromPtoLight))
        {
            auto k = object->material().diffuseCoefficient;
            auto d = 1; //std::pow(distanceFromPtoLight.norm(), 2);

            // Lambertian shading : diffuse shading
            pixelColor += (light->color() * k * (angle / d));
    
            // Blinn-Phong shading : specular shading
            auto H = (V + distanceFromPtoLight).normalize();
            k = object->material().specularCoefficient;
            auto n = object->material().shininess;

            pixelColor += (light->color() * k * (std::pow(std::max(0.0f, N * H), n) / d));
        }
    }
    return (pixelColor);
}

bool rt::RayTracer::isShadowed(const Scene &scene, const Ray &shadowRay, const maths::Vector3f &distanceFromPtoLight)
{
    if (!(_enabledOptions & Shadows))
        return (false);

    return (detectShadows(scene, shadowRay, distanceFromPtoLight));
}

bool rt::RayTracer::detectShadows(const Scene &scene, const Ray &shadowRay, const maths::Vector3f &distanceFromPtoLight)
{
    float t = std::numeric_limits<float>::max();

    for (auto &object : scene.objects())
    {
        if (object->intersect(shadowRay, &t))
        {            
            if (t < 0.001f)
                continue;

            auto distanceFromPtoObject(shadowRay.origin() - object->center());

            if (distanceFromPtoObject < distanceFromPtoLight)
            {
                return (true);
            }
        }
    }
    return (false);
}

rt::Color rt::RayTracer::computeReflections(
    const Scene &scene,
    const Ray &ray,
    std::shared_ptr<Object> object,
    float t,
    uint depth,
    float reflectionCoeff,
    float refractionCoeff)
{
    if (!(_enabledOptions & Reflections) || depth == 0 || reflectionCoeff <= 0.001f)
        return (Color::Black);

    auto V = ray.direction();

    // The intersection point
    auto P = ray.origin() + V * t;

    // The normal to the object surface
    auto N = object->normalSurface(P);

    // The reflected ray is perfectly symmetric to the original ray
    rt::Ray reflectedRay(P, V - (N * 2.f * (V * N)));

    return (computePixelColor(scene, reflectedRay, depth - 1, reflectionCoeff, refractionCoeff, false) * reflectionCoeff);
}

rt::Color rt::RayTracer::computeRefractions(
    const Scene &scene,
    const Ray &ray,
    std::shared_ptr<Object> object,
    float t,
    uint depth,
    float &reflexionCoeff,
    float refractionCoeff)
{
    if (!(_enabledOptions & Refractions) || depth == 0 || refractionCoeff <= 0.001f)
        return (Color::Black);

    
    auto V = ray.direction();

    // The intersection point
    auto P = ray.origin() + V * t;
    
    // The normal to the object surface
    auto N = object->normalSurface(P);
  
    auto kr = fresnel(V, N, object->material().refractiveIndex);

    reflexionCoeff = kr;

    if (kr >= 1.0f)
        return (Color::Black);

    auto eta_t = object->material().refractiveIndex;
    auto eta_i = 1.0f;

    auto incidenceAngle = N * V;

    if (incidenceAngle < 0.0f)
        incidenceAngle = -incidenceAngle;
    else
    {
        N = -N;
        std::swap(eta_t, eta_i);
    }
    
    auto eta = eta_i / eta_t;
    
    auto k = 1.0f - std::pow(eta, 2) * (1.0f - std::pow(incidenceAngle, 2));

    if (k < 0)
        return (Color::Black);

    auto T = (V + N * incidenceAngle) * eta - N * ::sqrtf(k);

    Ray refractedRay(P, T);

    return (computePixelColor(scene, refractedRay, depth - 1, reflexionCoeff, refractionCoeff, false) * (1.0f - kr) * object->material().transmittance);
}

std::pair<std::shared_ptr<rt::Object>, float> rt::RayTracer::findClosestObject(const Scene &scene, const Ray &ray)
{
    float t = std::numeric_limits<float>::max();
    std::shared_ptr<Object> closest = nullptr;

    for (auto &object : scene.objects())
    {
        if (object->intersect(ray, &t))
        {
            closest = object;
        }
    }

    return {closest, t};
}