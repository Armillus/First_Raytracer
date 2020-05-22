/*
 * Created on Wed Apr 29 2020
 *
 * Copyright (c) raytracer 2020 Arthur Lang
 * UnitTest_Camera.cpp
 */

#include <gtest/gtest.h>

#include "Camera.hpp"
#include "Vector3.hpp"
#include "Resolution.hpp"
#include "Ray.hpp"

TEST(Camera, basicTest)
{
    rt::maths::Vector3f origin(0, 0, 0);
    rt::maths::Vector3f lookat(0, 0, 3);
    rt::Resolution res = { 1920, 1080 };
    rt::Camera c(origin, lookat, res, 45);

    rt::maths::Vector3f newOrigin(0, 3, 2);
    c.setOrigin(newOrigin);
    ASSERT_EQ(c.hasChangedSinceLastFrame(), true);

    rt::maths::Vector3f o = c.origin();
    ASSERT_FLOAT_EQ(o.x, newOrigin.x);
    ASSERT_FLOAT_EQ(o.y, newOrigin.y);
    ASSERT_FLOAT_EQ(o.z, newOrigin.z);
    ASSERT_EQ(c.hasChangedSinceLastFrame(), true);

    rt::maths::Vector3f d = c.direction();
    ASSERT_FLOAT_EQ(d.x, 0);
    ASSERT_FLOAT_EQ(d.y, 0);
    ASSERT_FLOAT_EQ(d.z, 1);
    ASSERT_EQ(c.hasChangedSinceLastFrame(), true);

    c.wasRendered();
    ASSERT_EQ(c.hasChangedSinceLastFrame(), false);
}

TEST(Camera, getRay)
{
    rt::maths::Vector3f origin(0, 0, 0);
    rt::maths::Vector3f lookat(0, 0, 3);
    rt::Resolution res = { 1920, 1080 };
    rt::Camera c(origin, lookat, res, 45);

    rt::Ray r = c.getPrimaryRay(1, 1);
    rt::maths::Vector3f rO = r.origin();
    rt::maths::Vector3f rD = r.direction();

    ASSERT_FLOAT_EQ(rO.x, 0);
    ASSERT_FLOAT_EQ(rO.y, 0);
    ASSERT_FLOAT_EQ(rO.z, 0);

    ASSERT_FLOAT_EQ(rD.x, -0.78253251);
    ASSERT_FLOAT_EQ(rD.y, 0.43963876);
    ASSERT_FLOAT_EQ(rD.z, -0.44086337);
}