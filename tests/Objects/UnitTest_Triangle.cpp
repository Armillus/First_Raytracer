/*
 * Created on Fri Apr 28 2020
 *
 * raytracer 2020 Arthur Lang
 * UnitTest_Triangle.cpp
 */

#include <gtest/gtest.h>

#include "Triangle.hpp"
#include "Vector3.hpp"
#include "Material.hpp"
#include "Color.hpp"
#include "Ray.hpp"

TEST(TrianglePrimitive, basic)
{
    const rt::maths::Vector3f v1(1.f, 1.f, 0.f);
    const rt::maths::Vector3f v2(0.f, 1.f, 0.f);
    const rt::maths::Vector3f v3(1.f, 0.f, 0.f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);
    const std::string texture = "./texture/texture.png";

    rt::Triangle t(v1, v2, v3, mat);
    rt::Triangle t2(v1, v2, v3, mat, texture);

    rt::maths::Vector3f unused(0.f, 0.f, 0.f);
    rt::maths::Vector3f n = t.normalSurface(unused);

    ASSERT_FLOAT_EQ(n.x, 0);
    ASSERT_FLOAT_EQ(n.y, 0);
    ASSERT_FLOAT_EQ(n.z, 0.99999994);

    t.setVertices(
        rt::maths::Vector3f(2.f, 2.f, -3.f),
        rt::maths::Vector3f(0.f, 0.f, -3.f),
        rt::maths::Vector3f(100.f, 45.f, -10.f)
    );

    n = t.normalSurface(unused);

    ASSERT_FLOAT_EQ(n.x, -0.12525991);
    ASSERT_FLOAT_EQ(n.y, 0.12525991);
    ASSERT_FLOAT_EQ(n.z, 0.98418492);
}

TEST(TrianglePrimitive, intersect)
{
    const rt::maths::Vector3f v1(1.f, 1.f, 0.f);
    const rt::maths::Vector3f v2(0.f, 1.f, 0.f);
    const rt::maths::Vector3f v3(1.f, 0.f, 0.f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);

    rt::Triangle t(v1, v2, v3, mat);

    float res = 2000;
    const rt::maths::Vector3 rayOrigin(1.0f, 0.0f, 1.0f);
    const rt::maths::Vector3 direction(0.0f, 0.0f, -3.0f);
    rt::Ray r1(rayOrigin, direction);

    const rt::maths::Vector3 direction2(2.0f, 1.0f, 0.0f);
    rt::Ray r2(rayOrigin, direction2);

    ASSERT_EQ(false, t.intersect(r2, &res));
    ASSERT_EQ(true, t.intersect(r1, &res));
}

TEST(TrianglePrimitive, color)
{
    const rt::maths::Vector3f v1(1.f, 1.f, 0.f);
    const rt::maths::Vector3f v2(0.f, 1.f, 0.f);
    const rt::maths::Vector3f v3(1.f, 0.f, 0.f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);

    rt::Triangle t(v1, v2, v3, mat);

    ASSERT_EQ(t.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).r, 0);
    ASSERT_EQ(t.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).g, 0);
    ASSERT_EQ(t.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).b, 0);
    ASSERT_EQ(t.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).a, 255);

    const rt::Material redWhite(rt::Color::White, 0, 0, 2, 3);

    t.setMaterial(redWhite);

    ASSERT_EQ(t.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).r, 255);
    ASSERT_EQ(t.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).g, 255);
    ASSERT_EQ(t.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).b, 255);
    ASSERT_EQ(t.color(rt::maths::Vector3f(0.f, 0.f, 0.f)).a, 255);
}

TEST(TrianglePrimitive, props)
{
    const rt::maths::Vector3f v1(1.f, 1.f, 0.f);
    const rt::maths::Vector3f v2(0.f, 1.f, 0.f);
    const rt::maths::Vector3f v3(1.f, 0.f, 0.f);
    const rt::Material mat(rt::Color::Black, 0, 0, 2, 3);

    rt::Triangle t(v1, v2, v3, mat);

    ASSERT_FLOAT_EQ(t.center().x, 0.66666669);
    ASSERT_FLOAT_EQ(t.center().y, 0.66666669);
    ASSERT_FLOAT_EQ(t.center().z, 0);
}