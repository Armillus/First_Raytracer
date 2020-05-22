/*
 * Created on Wed Apr 29 2020
 *
 * Copyright (c) Raytracer 2020 Lucas Tabis
 * UnitTest_SphericalLight.cpp
 */

#include <gtest/gtest.h>

#include "SphericalLight.hpp"

TEST(SphericalLightTest, props)
{
    rt::SphericalLight light(
        rt::maths::Vector3f(100.f, 0.f, -200.f),
        rt::Color(1.f, 1.f, 1.f, 1.f),
        5.f
    );

    ASSERT_EQ(light.color().r, 255);
    ASSERT_EQ(light.color().g, 255);
    ASSERT_EQ(light.color().b, 255);
    ASSERT_EQ(light.color().a, 255);

    ASSERT_FLOAT_EQ(light.intensity(rt::maths::Vector3f(0.f, 0.f, 0.f)), 0.0017794064);
    ASSERT_FLOAT_EQ(light.distance(rt::maths::Vector3f(0.f, 0.f, 0.f)), 14.953487);

    auto dir = light.directionFrom(rt::maths::Vector3f(0.f, 0.f, 0.f));
    ASSERT_EQ(dir.x, 100);
    ASSERT_EQ(dir.y, 0.f);
    ASSERT_EQ(dir.z, -200.f);

    auto pos = light.position();
    ASSERT_EQ(pos.x, 100.f);
    ASSERT_EQ(pos.y, 0.f);
    ASSERT_EQ(pos.z, -200.f);
}