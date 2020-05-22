/*
 * Created on Fri Apr 24 2020
 *
 * raytracer 2020 Arthur Lang
 * UnitTest_Sphere.cpp
 */

#include <gtest/gtest.h>

#include "Sphere.hpp"
#include "Vector3.hpp"
#include "Material.hpp"
#include "Color.hpp"
#include "Ray.hpp"

TEST(SpherePrimitive, basic)
{
    const rt::maths::Vector3 center(1.0f, 4.0f, 0.0f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);
    rt::Sphere s(center, 1.0f, mat);
    rt::Sphere s2(center, 1.0f, mat, "texture");

    rt::maths::Vector3<float> cen = s.center();
    ASSERT_EQ(cen.x, 1);
    ASSERT_EQ(cen.y, 4);
    ASSERT_EQ(cen.z, 0);

    rt::Color col = s.color({center});
    ASSERT_EQ(col.r, rt::Color::Black.r);
    ASSERT_EQ(col.g, rt::Color::Black.g);
    ASSERT_EQ(col.b, rt::Color::Black.b);
}

TEST(SpherePrimitive, intersect)
{
    const rt::maths::Vector3 center(0.0f, 0.0f, 4.0f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);
    rt::Sphere s(center, 2.0f, mat);

    float res = 2000;
    const rt::maths::Vector3 rayOrigin(0.0f, 0.0f, 0.0f);
    const rt::maths::Vector3 direction(0.0f, 0.0f, 1.0f);
    rt::Ray r1(rayOrigin, direction);

    rt::Ray r2(rayOrigin, direction * 3);

    ASSERT_EQ(true, s.intersect(r1, &res));
    ASSERT_EQ(false, s.intersect(r2, &res));
}

TEST(SpherePrimitive, normalize)
{
    const rt::maths::Vector3 center(1.0f, 0.0f, 1.0f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);
    rt::Sphere s(center, 0.5f, mat);

    rt::maths::Vector3 v(1.0f, 0.0f, 1.0f);

    rt::maths::Vector3 res = s.normalSurface(v);

    ASSERT_EQ(res.x, 0);
    ASSERT_EQ(res.y, 0);
    ASSERT_EQ(res.z, 1);
}