#include <gtest/gtest.h>

#include "Scene.hpp"
#include "ObjParser.hpp"

TEST(ObjParser, badObj)
{
    rt::Scene s;
    rt::ObjParser p(s);
    p.parse("assets/band.obj");
}
