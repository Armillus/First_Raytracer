#include "RayTracer.hpp"

rt::RayTracer::RayTracer(const Resolution &screenRes, uint startingOptions)
    : Renderer(screenRes),
    _enabledOptions(startingOptions),
    _reflectionsDepth(DEFAULT_REFLECTIONS_DEPTH)
{
}

void rt::RayTracer::render(const Scene &scene, const Camera &camera)
{
    std::chrono::_V2::system_clock::time_point tStart = std::chrono::high_resolution_clock::now();
    if (TIME_DEBUG) {
        std::cout << "Render begins..." << std::endl;
    }
    render(scene, camera, _reflectionsDepth, DEFAULT_SAMPLES);
    if (TIME_DEBUG) {
        std::chrono::_V2::system_clock::time_point tEnd = std::chrono::high_resolution_clock::now();
        auto tDelta = tEnd - tStart;
        std::cout << "Render finished in :" << std::chrono::duration_cast<std::chrono::milliseconds>(tDelta).count() << "ms or μs"
            << std::chrono::duration_cast<std::chrono::microseconds>(tDelta).count() << std::endl;
    }
}

void rt::RayTracer::render(const Scene &scene, const Camera &camera, uint reflectionsDepth, int samples)
{
    volatile uint width = _screenResolution.width;
    volatile uint height = _screenResolution.height;
    bool aaIsDisabled = samples <= 1 || !(_enabledOptions & AntiAliasing);

    _reflectionsDepth = reflectionsDepth;

    #pragma omp parallel for // Open MP computation
    for (uint x = 0; x < width; ++x)
    {
        #pragma omp parallel for // Open MP computation
        for (uint y = 0; y < height; ++y)
        {
            renderPixel(scene, camera, samples, x, y, aaIsDisabled);
        }
    }
}

void rt::RayTracer::renderPixel(const Scene &scene, const Camera &camera, int samples, uint ix, uint iy, bool aaIsDisabled)
{
    Color pixelColor;
    uint r = 0, g = 0, b = 0;
    int counter = 0;

    float xStart = (float) ix - 5.0f;
    float yStart = (float) iy - 5.0f;

    float xEnd = ix + 5.0f;
    float yEnd = iy + 5.0f;

    float step = 1.0f;

    
    if (aaIsDisabled)
        pixelColor = getPixelColor(scene, camera, ix, iy);
    else
        pixelColor = getPixelColor(scene, camera, samples, ix, iy);

    if (_zBuffer < 550)
    {
        _frameBuffer.updatePixelColor(ix, iy, pixelColor);
        return;  
    }

    for (float x = xStart; x < xEnd; x += step)
    {
        if (x < 0.0f)
            continue;

        for (float y = yStart; y < yEnd; y += step)
        {
            if (y < 0.0f)
                continue;


            if (aaIsDisabled)
                pixelColor = getPixelColor(scene, camera, x, y);
            else
                pixelColor = getPixelColor(scene, camera, samples, x, y);

            r += pixelColor.r;
            g += pixelColor.g;
            b += pixelColor.b;

            counter++;
        }
    }

    r /= counter;
    b /= counter;
    g /= counter;


    _frameBuffer.updatePixelColor(ix, iy, Color(r, g, b));   
}


rt::Color rt::RayTracer::getPixelColor(const Scene &scene, const Camera &camera, int samples, uint ix, uint iy)
{
    uint r = 0, g = 0, b = 0;
    float step = 1.0f / (float) samples;
    int counter = 0;

    // #pragma omp parallel for // Open MP computation
    for (float dx = -0.5f; dx < 0.5f; dx += step)
    {

        //   #pragma omp parallel for // Open MP computation
        for (float dy = -0.5f; dy < 0.5f; dy += step)
        {
            float x = (float) ix + dx;
            float y = (float) iy + dy;

            Ray primaryRay(camera.getPrimaryRay(x, y));
            Color pixelColor = computePixelColor(scene, primaryRay, 0);
            
            r += pixelColor.r;
            g += pixelColor.g;
            b += pixelColor.b;

            counter++;
        }
    }

    r /= counter;
    b /= counter;
    g /= counter;

    return Color(r, g, b);
}


rt::Color rt::RayTracer::computePixelColor(const Scene &scene, const Ray &ray, uint depth)
{
    Color pixelColor(scene.ambientLightCoefficient());

    auto closest = findClosestObject(scene, ray);

    if (!closest.has_value())
        return (depth == 0 ? pixelColor : Color::Black);

    auto [closestObj, t] = closest.value();    
    auto P = ray.origin() + ray.direction() * t;

    // Compute Lights and Shadows effects
    pixelColor *= closestObj->color(P - closestObj->center());
    pixelColor += computeLightsAndShadows(scene, ray, closestObj, t);

    float reflectionCoeff = closestObj->material().reflectivity;
    float refractionCoeff = closestObj->material().transmittance;

    // Compute refractions
    pixelColor += computeRefractions(scene, ray, closestObj, t, depth, reflectionCoeff, refractionCoeff);

    // Compute reflections
    pixelColor += computeReflections(scene, ray, closestObj, t, depth, reflectionCoeff);

    _zBuffer = t;
    return (pixelColor);
}

rt::Color rt::RayTracer::computeLightsAndShadows(const Scene &scene, const Ray &ray, std::shared_ptr<IObject> object, float t)
{
    if (!(_enabledOptions & Illumination))
        return (Color::Black);

    return (computeGlobalIllumination(scene, ray, object, t));
}

rt::Color rt::RayTracer::computeGlobalIllumination(const Scene &scene, const Ray &ray, std::shared_ptr<IObject> object, float t)
{
    Color pixelColor(Color::Black);
    float bias = DEFAULT_BIAS;

    auto V = ray.direction();

    // The intersection point
    auto P = ray.origin() + V * t;

    // The normal to the object surface
    auto N = object->normalSurface(P);

    for (auto &[_, light] : scene.lights())
    {
        auto distanceFromPtoLight = light->directionFrom(P);
        maths::Vector3f shadowRayOrigin(P + N * bias);
        rt::Ray shadowRay(shadowRayOrigin, distanceFromPtoLight.normalize());
        float angle = shadowRay.direction() * N;

        // This part of the object isn't lit according to the Lambert law.
        if (angle < 0.0f)
            continue;

        float intensity = light->intensity(P);
     
        if (!isShadowed(scene, shadowRay, distanceFromPtoLight))
        {
            auto k = object->material().diffuseCoefficient;

            // if (_enabledOptions & SoftShadows)
            // {
            //     intensity *= getSoftShadowCoefficient(scene, P, N, light);
            // }

            // Lambertian shading : diffuse shading
            auto diffuseColor = (light->color() * k * angle * intensity);
 
            // Blinn-Phong shading : specular shading
            auto H = (V + distanceFromPtoLight).normalize();
            k = object->material().specularCoefficient;
            auto n = object->material().shininess;

            auto specularColor = (light->color() * k * intensity * std::pow(std::max(0.0f, N * H), n));

            pixelColor += specularColor + diffuseColor;
        }
        else if (_enabledOptions & SoftShadows)
        {
            intensity *= getSoftShadowCoefficient(scene, P, N, light);
            pixelColor += (light->color() * intensity);
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

    for (auto &[_, object] : scene.objects())
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

float rt::RayTracer::getSoftShadowCoefficient(
    const Scene &scene,
    const rt::maths::Vector3f &P,
    const rt::maths::Vector3f &N,
    const std::shared_ptr<rt::ILight> &light)
{
    maths::Vector3f shadowRayOrigin(P + N * DEFAULT_BIAS);
    int lowerLimit = -128;
    int upperLimit = 128;
    float shadowed = 0.0f;

    //#pragma omp parallel for // Open MP computation
    for (int i = lowerLimit; i < upperLimit + 1; ++i)
    // for (int x = lowerLimit; x < upperLimit + 1; ++x)
    {
    //     for (int y = lowerLimit; y < upperLimit + 1; ++y)
    //     {
            // if (i == 0)
            //     continue;

            auto distanceFromPtoLight = light->directionFrom(P, i); // Changed.
            rt::Ray shadowRay(shadowRayOrigin, distanceFromPtoLight.normalize());
            float angle = shadowRay.direction() * N;

            // This part of the object isn't lit according to the Lambert law.
            if (angle < 0.0f || isShadowed(scene, shadowRay, distanceFromPtoLight))
                shadowed++;
        // }

    }

    return 1.0f - (shadowed / (float)(std::abs(lowerLimit) + upperLimit + 1));
}

rt::Color rt::RayTracer::computeReflections(
    const Scene &scene,
    const Ray &ray,
    std::shared_ptr<IObject> object,
    float t,
    uint depth,
    float reflectionCoeff)
{
    if (!(_enabledOptions & Reflections) || depth == _reflectionsDepth || reflectionCoeff <= 0.001f)
        return (Color::Black);


    auto V = ray.direction();

    // The intersection point
    auto P = ray.origin() + V * t;

    // The normal to the object surface
    auto N = object->normalSurface(P);

    // The reflected ray is perfectly symmetric to the original ray
    rt::Ray reflectedRay(P, V - (N * 2.f * (V * N)));

    // return (Color::Black);
    return (computePixelColor(scene, reflectedRay, depth + 1) * reflectionCoeff);
}

rt::Color rt::RayTracer::computeRefractions(
    const Scene &scene,
    const Ray &ray,
    std::shared_ptr<IObject> object,
    float t,
    uint depth,
    float &reflexionCoeff,
    float refractionCoeff)
{
    if (!(_enabledOptions & Refractions) || depth == _reflectionsDepth || refractionCoeff <= 0.001f)
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

    // return (Color::Black);
    return (computePixelColor(scene, refractedRay, depth + 1) * (1.0f - kr) * object->material().transmittance);
}

std::optional<std::pair<std::shared_ptr<rt::IObject>, float>> rt::RayTracer::findClosestObject(const Scene &scene, const Ray &ray)
{
    float t = std::numeric_limits<float>::max();
    std::shared_ptr<IObject> closest = nullptr;

    for (auto &[_, object] : scene.objects())
    {
        //#pragma omp parallel // Open MP computation
        if (object->intersect(ray, &t))
        {
            closest = object;
        }
    }

    if (closest == nullptr)
        return std::nullopt;

    return std::optional<std::pair<std::shared_ptr<rt::IObject>, float>>{{closest, t}};
}