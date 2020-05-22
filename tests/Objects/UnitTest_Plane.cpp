/*
 * Created on Fri Apr 28 2020
 *
 * raytracer 2020 Arthur Lang
 * UnitTest_Plane.cpp
 */

#include <gtest/gtest.h>

#include "Plane.hpp"
#include "Vector3.hpp"
#include "Material.hpp"
#include "Color.hpp"
#include "Ray.hpp"

TEST(PlanePrimitive, basic)
{
    const rt::maths::Vector3f origin(0.f, 0.f, 0.f);
    const rt::maths::Vector3f norm(0.f, 0.f, 1.f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);
    const std::string texture = "./texture/texture.png";

    rt::Plane p(norm, origin, mat);
    rt::Plane p2(norm, origin, mat, texture);

    rt::maths::Vector3f cen = p.center();

    ASSERT_EQ(cen.x, 0);
    ASSERT_EQ(cen.y, 0);
    ASSERT_EQ(cen.z, 0);

    rt::maths::Vector3f unused(3.f, 2.f, 3.f);
    rt::maths::Vector3f n = p.normalSurface(unused);

    ASSERT_EQ(norm.x, 0);
    ASSERT_EQ(norm.y, 0);
    ASSERT_EQ(norm.z, 1);
}

TEST(PlanePrimitive, intersect)
{
    const rt::maths::Vector3f origin(0.f, 0.f, 0.f);
    const rt::maths::Vector3f norm(0.f, 0.f, 1.f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);

    rt::Plane p(norm, origin, mat);

    float res = 2000;
    const rt::maths::Vector3 rayOrigin(1.0f, 0.0f, 1.0f);
    const rt::maths::Vector3 direction(0.0f, 0.0f, -3.0f);
    rt::Ray r1(rayOrigin, direction);

    const rt::maths::Vector3 direction2(2.0f, 1.0f, 0.0f);
    rt::Ray r2(rayOrigin, direction2);

    ASSERT_EQ(false, p.intersect(r2, &res));
    ASSERT_EQ(true, p.intersect(r1, &res));
}

TEST(PlanePrimitive, color)
{
    const rt::maths::Vector3f origin(0.f, 0.f, 0.f);
    const rt::maths::Vector3f norm(0.f, 0.f, 1.f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);

    rt::Plane p(norm, origin, mat);

    ASSERT_EQ(p.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).r, 0);
    ASSERT_EQ(p.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).g, 0);
    ASSERT_EQ(p.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).b, 0);
    ASSERT_EQ(p.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).a, 255);

    rt::Plane p2(norm, origin, mat, "./assets/textures/checkerboard.jpg");

    ASSERT_EQ(p2.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).r, 31);
    ASSERT_EQ(p2.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).g, 68);
    ASSERT_EQ(p2.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).b, 0);
    ASSERT_EQ(p2.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).a, 0);
}