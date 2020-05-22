#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "Scene.hpp"
#include "JsonParser.hpp"
#include "ObjParser.hpp"

namespace rt
{
    class Parser
    {
    public:
        Parser(int, const char **, rt::Scene &);
        ~Parser() = default;

    private:
        rt::JsonParser _jsonParser;
        rt::ObjParser _objParser;
    };
}

#endif /* !PARSER_HPP_ */
