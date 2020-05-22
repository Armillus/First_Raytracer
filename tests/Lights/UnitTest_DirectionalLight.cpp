/*
 * Created on Wed Apr 29 2020
 *
 * Copyright (c) Raytracer 2020 Lucas Tabis
 * UnitTest_DirectionalLight.cpp
 */

#include <gtest/gtest.h>

#include "DirectionalLight.hpp"

TEST(DirectionalLightTest, props)
{
    rt::DirectionalLight light(
        rt::maths::Vector3f(1.f, 0.f, 1.f),
        rt::Color(1.f, 1.f, 1.f, 1.f),
        10.f
    );

    ASSERT_EQ(light.color().r, 255);
    ASSERT_EQ(light.color().g, 255);
    ASSERT_EQ(light.color().b, 255);
    ASSERT_EQ(light.color().a, 255);
    ASSERT_EQ(light.intensity(rt::maths::Vector3f(0.f, 0.f, 0.f)), 10.f);
    ASSERT_EQ(light.distance(rt::maths::Vector3f(0.f, 0.f, 0.f)), INFINITY);

    auto dir = light.directionFrom(rt::maths::Vector3f(0.f, 0.f, 0.f));
    ASSERT_EQ(dir.x, -1.f);
    ASSERT_EQ(dir.y, 0.f);
    ASSERT_EQ(dir.z, -1.f);

    auto pos = light.position();
    ASSERT_EQ(pos.x, 1.f);
    ASSERT_EQ(pos.y, 0.f);
    ASSERT_EQ(pos.z, 1.f);
}