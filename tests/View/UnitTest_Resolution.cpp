/*
 * Created on Wed Apr 29 2020
 *
 * Copyright (c) Raytracer 2020 Arthur Lang
 * UnitTest_Resolution.cpp
 */

#include <gtest/gtest.h>

#include "Resolution.hpp"

TEST(Resolution, operator)
{
    rt::Resolution r1 = {300, 200};
    rt::Resolution r2 = {300, 200};
    rt::Resolution r3 = {1000, 500};

    ASSERT_EQ(r1 == r2, true);
    ASSERT_EQ(r1 == r3, false);
    ASSERT_EQ(r1 != r3, true);
}

TEST(Resolution, output)
{
    rt::Resolution r = {1000, 500};
    testing::internal::CaptureStdout();
    std::cout << r;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_STREQ("Resolution (1000, 500)", output.c_str());
}