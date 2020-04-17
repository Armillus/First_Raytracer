#include "RayTracer.hpp"

rt::RayTracer::RayTracer(const Resolution &screenRes, uint startingOptions)
    : Renderer(screenRes), _enabledOptions(startingOptions),
    _reflectionsDepth(DEFAULT_REFLECTIONS_DEPTH)
{

}

void rt::RayTracer::render(const Scene &scene, const Camera &camera)
{
    render(scene, camera, _reflectionsDepth);
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
            Color pixelColor(computePixelColor(scene, primaryRay, reflectionsDepth, 1.0f, true));

            _frameBuffer.updatePixelColor(x, y, pixelColor);
        }
    }
}

rt::Color rt::RayTracer::computePixelColor(const Scene &scene, const Ray &ray, uint depth, float reflectionCoeff, bool isPrimaryRay)
{
    static Color pixelColor(scene.ambientLightCoefficient());

    if (isPrimaryRay)
        pixelColor = Color(scene.ambientLightCoefficient());
    
    auto closest = findClosestObject(scene, ray);
    auto closestObj = closest.first;
    auto t = closest.second;

    if (!closestObj)
        return (isPrimaryRay ? pixelColor : Color::Black);
    
    // Compute Lights and Shadows effects
    pixelColor *= closestObj->color();
    pixelColor += computeLightsAndShadows(scene, ray, closestObj, t, reflectionCoeff);
    
    // Compute reflections
    reflectionCoeff *= closestObj->reflection();
    computeReflections(scene, ray, closestObj, t, depth, reflectionCoeff);

    return (pixelColor);
}

rt::Color rt::RayTracer::computeLightsAndShadows(const Scene &scene, const Ray &ray, std::shared_ptr<Object> object, float t, float reflectionCoeff)
{
    if (!(_enabledOptions & Illumination))
        return (Color::Black);

    return (computeGlobalIllumination(scene, ray, object, t, reflectionCoeff));
}

rt::Color rt::RayTracer::computeGlobalIllumination(const Scene &scene, const Ray &ray, std::shared_ptr<Object> object, float t, float reflectionCoeff)
{
    Color pixelColor(Color::Black);
    float bias = DEFAULT_BIAS;

    // The intersection point
    auto P = ray.origin() + ray.direction() * t;

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
            pixelColor += (light->color() * scene.diffuseLightCoefficient() * angle * reflectionCoeff);
        }
    }
    return (pixelColor);
}

bool rt::RayTracer::isShadowed(const Scene &scene, const Ray &shadowRay, const maths::Vector3f &distanceFromPtoLight)
{
    if (!(_enabledOptions & Shadows))
        return (false);

    return (computeDiffuseShadows(scene, shadowRay, distanceFromPtoLight));
}

bool rt::RayTracer::computeDiffuseShadows(const Scene &scene, const Ray &shadowRay, const maths::Vector3f &distanceFromPtoLight)
{
    float t = 20000.0f;

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
    float reflectionCoeff)
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

    return (computePixelColor(scene, reflectedRay, depth - 1, reflectionCoeff, false));
}

std::pair<std::shared_ptr<rt::Object>, float> rt::RayTracer::findClosestObject(const Scene &scene, const Ray &ray)
{
    float t = 20000.0f;
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