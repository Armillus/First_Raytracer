/*
 * Created on Fri Apr 24 2020
 *
 * raytracer 2020 Arthur Lang
 * UnitTest_Trigo.cpp
 */

#include <gtest/gtest.h>

#include "Trigonometry.hpp"

TEST(trigonometry, radianConversion)
{
    ASSERT_EQ(rt::maths::toDegrees(1), 57);
    ASSERT_EQ(rt::maths::toRadians(180), 3);
}