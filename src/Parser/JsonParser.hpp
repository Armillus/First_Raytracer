/*
** EPITECH PROJECT, 2020
** YEP_project2_2019
** File description:
** JsonParser
*/

#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_

#include <exception>
#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "Scene.hpp"
#include "Material.hpp"
#include "Color/Color.hpp"

namespace rt
{
    using json = nlohmann::json;

    class JsonParser
    {
    public:
        JsonParser(rt::Scene &);
        ~JsonParser() = default;

        void parse(const std::string &);

    private:
        void parseMaterials();
        void parseObjects();
        void parseLights();
        void parseSpheres(json &, uint);
        void parsePlanes(json &, uint);
        void parseDirectional(json &, uint);
        void parseSpherical(json &, uint);

        rt::Scene &_scene;
        std::string _tot;
        json _j;
        json _lights;
        json _materials;
        json _objects;

        std::unordered_map<std::string, rt::Material> _mList;
    };
}

#endif /* !JSONPARSER_HPP_ */
