#ifndef OBJPARSER_HPP_
#define OBJPARSER_HPP_

#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "tiny_obj_loader.h"

#include "Scene.hpp"

namespace rt
{
    class ObjParser
    {
    public:
        ObjParser(rt::Scene &);
        ~ObjParser() = default;

        void parse(const std::string &);

    private:
        void initTriangles(tinyobj::attrib_t &attrib, std::vector<tinyobj::shape_t> &shapes);
        void initTriangle();

        rt::Scene &_scene;
        std::string _tot;
        std::vector<std::array<float, 3>> _vertices;
    };
}

#endif /* !OBJPARSER_HPP_ */
