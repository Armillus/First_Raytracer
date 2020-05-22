/*
 * Created on Fri Apr 24 2020
 *
 * raytracer 2020 Arthur Lang
 * test_vector3.cpp
 */

#include <gtest/gtest.h>

#include "Vector3.hpp"

TEST(vector3, basicOperation)
{
    std::array<float, 3> arr = {1.f, 2.f, -1.f};
    rt::maths::Vector3<float> defaultVec;
    rt::maths::Vector3 vec(1.0f, 2.0f, -1.0f);
    rt::maths::Vector3 copyVec(vec);
    rt::maths::Vector3 add(vec + copyVec);
    rt::maths::Vector3 min(vec - copyVec);
    rt::maths::Vector3 mul(vec * 3);
    rt::maths::Vector3 neg(-vec);
    rt::maths::Vector3f vecArr(arr);

    ASSERT_EQ(vec == copyVec, true);
    ASSERT_EQ(vec == vecArr, true);
    ASSERT_EQ(vec == rt::maths::Vector3f(0.f, 0.f, 0.f), false);
    ASSERT_EQ(vec != copyVec, false);
    ASSERT_FLOAT_EQ(add.x, 2.0f);
    ASSERT_FLOAT_EQ(add.y, 4.0f);
    ASSERT_FLOAT_EQ(add.z, -2.0f);

    ASSERT_FLOAT_EQ(min.x, 0.0f);
    ASSERT_FLOAT_EQ(min.y, 0.0f);
    ASSERT_FLOAT_EQ(min.z, 0.0f);

    ASSERT_FLOAT_EQ(mul.x, 3.0f);
    ASSERT_FLOAT_EQ(mul.y, 6.0f);
    ASSERT_FLOAT_EQ(mul.z, -3.0f);

    ASSERT_FLOAT_EQ(neg.x, -1.0f);
    ASSERT_FLOAT_EQ(neg.y, -2.0f);
    ASSERT_FLOAT_EQ(neg.z, 1.0f);

    std::cout << neg << std::endl;
}

TEST(vector3, vectOperation)
{
    rt::maths::Vector3 vec(1.0f, 2.0f, -1.0f);
    rt::maths::Vector3 vec2(-3.0f, 1.0f, 0.0f);

    ASSERT_EQ(vec.norm(), static_cast<float>(std::sqrt(6)));
    ASSERT_EQ(vec * vec2, -1);
}