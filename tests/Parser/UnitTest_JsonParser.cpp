#include <exception>
#include <gtest/gtest.h>

#include "JsonParser.hpp"
#include "Scene.hpp"

TEST(JsonParser, okFile)
{
    rt::Scene s;
    rt::JsonParser p(s);
    p.parse("assets/yeet.json");

    ASSERT_EQ(s.lights().size(), 2);
    ASSERT_EQ(s.objects().size(), 6);
}

TEST(JsonParser, emptyFile)
{
    rt::Scene s;
    rt::JsonParser p(s);
    p.parse("assets/empty.json");

    ASSERT_EQ(s.lights().size(), 0);
    ASSERT_EQ(s.objects().size(), 0);
}

TEST(JsonParser, notJson)
{
    rt::Scene s;
    rt::JsonParser p(s);

    ASSERT_THROW(p.parse("CMakeLists.txt"), std::exception);
}

TEST(JsonParser, noMaterials)
{
    rt::Scene s;
    rt::JsonParser p(s);

    ASSERT_THROW(p.parse("assets/noMaterial.json"), std::exception);
}

TEST(JsonParser, noObjects)
{
    rt::Scene s;
    rt::JsonParser p(s);

    ASSERT_NO_THROW(p.parse("assets/empty.json"));
}

TEST(JsonParser, lights)
{
    rt::Scene s;
    rt::JsonParser p(s);
    p.parse("assets/light_plane.json");

    ASSERT_EQ(s.lights().size(), 2);

    auto &l1 = s.lights().at(1);
    auto &l2 = s.lights().at(2);
    rt::Color white((uint) 255, 255, 255);

    ASSERT_EQ(l1->color().rgb(), white.rgb());
    ASSERT_EQ(l2->color().rgb(), white.rgb());

    ASSERT_EQ(l2->position().x, 0);
    ASSERT_EQ(l2->position().y, 400);
    ASSERT_EQ(l2->position().z, -300);
}

TEST(JsonParser, objects)
{
    rt::Scene s;
    rt::JsonParser p(s);
    p.parse("assets/light_plane.json");

    ASSERT_EQ(s.objects().size(), 2);

    auto &p1 = s.objects().at(3);
    auto &p2 = s.objects().at(4);

    ASSERT_EQ(p1->center().x, 0);
    ASSERT_EQ(p1->center().y, -200);
    ASSERT_EQ(p1->center().z, 0);

    ASSERT_EQ(p2->center().x, 0);
    ASSERT_EQ(p2->center().y, 0);
    ASSERT_EQ(p2->center().z, -1000);
}

TEST(JsonParser, badThings)
{
    rt::Scene s;
    rt::JsonParser p(s);
    p.parse("assets/bad.json");
}
