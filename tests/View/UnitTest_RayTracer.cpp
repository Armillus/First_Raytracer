/*
 * Created on Wed Apr 29 2020
 *
 * Copyright (c) Raytracer 2020 Lucas Tabis
 * UnitTest_Renderer.cpp
 */

#include <gtest/gtest.h>

#include "RayTracer.hpp"
#include "Triangle.hpp"

TEST(Resolution, options)
{
    rt::Resolution r = {300, 200};
    rt::RayTracer tracer(r);
    rt::Scene scene;
    rt::Camera camera(0, 0, 10, r.width, r.height);

    tracer.disableOptions(rt::Options::Illumination);
    tracer.disableOptions(rt::Options::None);
    tracer.enableOptions(rt::Options::Illumination);
    tracer.enableOptions(rt::Options::Reflections);
    tracer.enableOptions(rt::Options::Refractions);
    tracer.enableOptions(rt::Options::Shadows);

    tracer.render(scene, camera);
}

TEST(Resolution, withObjects)
{
    rt::Resolution r = {300, 200};
    rt::RayTracer tracer(r);
    rt::Scene scene;
    rt::Camera camera(0, 0, 10, r.width, r.height);

    // Is the scene empty ?
    ASSERT_EQ(scene.hasObject(0), false);
    ASSERT_EQ(scene.hasLight(0), false);

    auto ids = scene.createObjects(rt::tTriangle, 10);

    for (std::size_t i = 0; i < ids.size(); ++i)
    {
        ASSERT_EQ(ids[i], i + 1);
    }

    tracer.disableOptions(rt::Options::Illumination);
    tracer.disableOptions(rt::Options::None);
    tracer.enableOptions(rt::Options::Illumination);
    tracer.enableOptions(rt::Options::Reflections);
    tracer.enableOptions(rt::Options::Refractions);
    tracer.enableOptions(rt::Options::Shadows);

    tracer.render(scene, camera);
}

TEST(Resolution, setScreenRes)
{
    rt::Resolution r = {300, 200};
    rt::Resolution r2 = {1920, 1080};
    rt::RayTracer tracer(r);
    rt::Scene scene;
    rt::Camera camera(0, 0, 10, r.width, r.height);

    tracer.setScreenResolution(r2);
}