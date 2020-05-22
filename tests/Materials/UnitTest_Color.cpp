/*
 * Created on Fri Apr 24 2020
 *
 * raytracer 2020 Lucas Tabis
 * UnitTest_Color.cpp
 */

#include <gtest/gtest.h>

#include "Color.hpp"

TEST(color, ColorCreation)
{
    rt::Color white = rt::Color::White;
    rt::Color black = rt::Color::Black;

    ASSERT_EQ(white.r, 255);
    ASSERT_EQ(white.g, 255);
    ASSERT_EQ(white.b, 255);
    ASSERT_EQ(white.a, 255);

    ASSERT_EQ(black.r, 0);
    ASSERT_EQ(black.g, 0);
    ASSERT_EQ(black.b, 0);
    ASSERT_EQ(black.a, 255);

    rt::Color one_unit_unit((rt::uint)128, (rt::uint)255);

    ASSERT_EQ(one_unit_unit.r, 128);
    ASSERT_EQ(one_unit_unit.g, 128);
    ASSERT_EQ(one_unit_unit.b, 128);
    ASSERT_EQ(one_unit_unit.a, 255);

    rt::Color one_float_unit((float).5f, (float)1.f);

    ASSERT_EQ(one_float_unit.r, 127);
    ASSERT_EQ(one_float_unit.g, 127);
    ASSERT_EQ(one_float_unit.b, 127);
    ASSERT_EQ(one_float_unit.a, 255);

    rt::Color no_parameters;

    ASSERT_EQ(no_parameters.r, 0);
    ASSERT_EQ(no_parameters.g, 0);
    ASSERT_EQ(no_parameters.b, 0);
    ASSERT_EQ(no_parameters.a, 255);
}

TEST(color, ColorOperationsAdd)
{
    rt::Color one_unit_unit((rt::uint)128, (rt::uint)255);
    rt::Color one_float_unit((float).5f, (float)1.f);

    one_unit_unit += one_float_unit;

    ASSERT_EQ(one_unit_unit.r, 255);
    ASSERT_EQ(one_unit_unit.g, 255);
    ASSERT_EQ(one_unit_unit.b, 255);
    ASSERT_EQ(one_unit_unit.a, 255);
}

TEST(color, ColorOperationsMulScalar)
{
    rt::Color one_float_unit((float).5f, (float)1.f);

    one_float_unit = one_float_unit * 2;

    ASSERT_EQ(one_float_unit.r, 254);
    ASSERT_EQ(one_float_unit.g, 254);
    ASSERT_EQ(one_float_unit.b, 254);
    ASSERT_EQ(one_float_unit.a, 255);
}

TEST(color, ColorOperationsMulEqualColor)
{
    rt::Color one_float_unit((float).5f, (float)1.f);
    rt::Color white((float)1.f, (float)1.f);

    one_float_unit *= white;

    ASSERT_EQ(one_float_unit.r, 127);
    ASSERT_EQ(one_float_unit.g, 127);
    ASSERT_EQ(one_float_unit.b, 127);
    ASSERT_EQ(one_float_unit.a, 255);
}

TEST(color, ColorOperationsToInt)
{
    rt::Color white(rt::Color::White);

    // Bitwise operation for rendering.
    ASSERT_EQ(white.toInt(), 4294967295);
}