/*
 * Created on Wed Apr 29 2020
 *
 * Copyright (c) raytracer 2020 Arthur Lang
 * UnitTest_Scene.cpp
 */

#include <gtest/gtest.h>

#include "Scene.hpp"

TEST(Scene, basicTest)
{
    rt::Scene s;
    ASSERT_FLOAT_EQ(s.ambientLightCoefficient(), 0.2);
}

TEST(Scene, rendering)
{
    rt::Scene s;
    s.wasRendered();
    ASSERT_EQ(s.hasChangedSinceLastFrame(), false);
}

TEST(Scene, invalidObjects)
{
    rt::Scene s;

    auto ids = s.createObjects((rt::ObjectType)500, 10);

    ASSERT_EQ(ids.empty(), true);
}

TEST(Scene, lights)
{
    rt::Scene s;

    auto idsD = s.createLights(rt::Directional, 10);
    auto idsS = s.createLights(rt::Spherical, 15);

    ASSERT_EQ(idsD.size(), 10);
    ASSERT_EQ(idsS.size(), 15);
}

TEST(Scene, invalidLights)
{
    rt::Scene s;

    auto ids = s.createLights((rt::LightType)500, 12);

    ASSERT_EQ(ids.empty(), true);
}

TEST(Scene, triangleMaterial)
{
    rt::Scene s;

    auto ids = s.createObjects(rt::tTriangle, 10);
    s.ochangeMaterial(ids[0], rt::Material(rt::Color::White, 0, 0, 0));

    ASSERT_EQ(ids.empty(), false);
}

TEST(Scene, trianglePoints)
{
    rt::Scene s;

    auto ids = s.createObjects(rt::tTriangle, 10);

    s.ochangePoints(ids[0],
        rt::maths::Vector3f(1, 1, 0),
        rt::maths::Vector3f(0, 1, 0),
        rt::maths::Vector3f(1, 0, 0)
    );

    ASSERT_EQ(ids.empty(), false);
}

TEST(Scene, invalidChanges)
{
    rt::Scene s;

    auto ids = s.createObjects(rt::tTriangle, 10);

    // The id 122 doesnt exists.
    s.ochangeMaterial(122, rt::Material(rt::Color::White, 0, 0, 0));
    s.ochangeCenter(122, rt::maths::Vector3f(0, 0, 0));
    s.ochangeNormal(122, rt::maths::Vector3f(0, 0, 0));
    s.ochangeRadius(122, 10.f);
    s.ochangePoints(122,
        rt::maths::Vector3f(0, 0, 0),
        rt::maths::Vector3f(0, 0, 0),
        rt::maths::Vector3f(0, 0, 0)
    );
    s.ochangeTexture(122, "invalid");

    s.lchangePosition(122, rt::maths::Vector3f(0, 0, 0));
    s.lchangeDirection(122, rt::maths::Vector3f(0, 0, 0));
    s.lchangeColor(122, rt::Color::White);
    s.lchangeIntensity(122, 10.f);

    ASSERT_EQ(ids.empty(), false);
}

