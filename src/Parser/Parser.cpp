#include "Parser.hpp"

rt::Parser::Parser(int ac, const char **av, rt::Scene &scene) : _jsonParser(scene), _objParser(scene)
{
    if (ac < 2)
        throw std::exception();

    for (int i = 1; i < ac; i++) {
        std::string file = av[i];
        if (file.substr(file.length() - 5) == ".json")
            _jsonParser.parse(file);
        else if (file.substr(file.length() - 4) == ".obj")
            _objParser.parse(file);
        else
            std::cerr << "This type of file is not recognized by our software" << std::endl;
    }
}
