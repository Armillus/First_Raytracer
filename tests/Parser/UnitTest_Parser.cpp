#include <gtest/gtest.h>

#include "Parser.hpp"
#include "Scene.hpp"

TEST(Parser, noFile)
{
    const char **av = new const char *[2];
    av[0] = "./unit_tests";
    av[1] = nullptr;

    rt::Scene s;

    ASSERT_THROW(rt::Parser p(1, av, s), std::exception);

    delete[] av;
}

TEST(Parser, multipleFile)
{
    const char **av = new const char *[4];
    av[0] = "./unit_tests";
    av[1] = "assets/test_cube.obj";
    av[2] = "assets/test_light_plane.json";
    av[3] = nullptr;

    rt::Scene s;
    rt::Parser p(3, av, s);

    ASSERT_EQ(s.lights().size(), 2);
    ASSERT_EQ(s.objects().size(), 8);

    delete[] av;
}
