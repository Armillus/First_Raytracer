#include "JsonParser.hpp"

rt::JsonParser::JsonParser(rt::Scene &scene) : _scene(scene) {}

void rt::JsonParser::parse(const std::string &fileName)
{
    std::string line;
    std::ifstream file(fileName);
    while (getline(file, line))
        _tot += line;
    file.close();

    try
    {
        _j = json::parse(_tot);
    }
    catch (const nlohmann::detail::parse_error &e)
    {
        throw e;
    }

    _lights = _j["lights"];
    _materials = _j["materials"];
    _objects = _j["objects"];

    parseMaterials();
    if (!_mList.size())
        _mList.emplace(std::make_pair("default",
            Material(rt::Color((uint) 0, 0, 0), 0, 0, 0, 0, 0, 1)
        ));

    parseLights();
    parseObjects();
}

void rt::JsonParser::parseMaterials()
{
    uint materialNumber = 1;

    for (json &j : _materials)
    {
        std::string name = "";
        rt::Color color((uint) 0, 0, 0);
        std::array<float, 6> carac = {0, 0, 0, 0, 0, 1};
        std::array<std::string, 6> paramNames = {
            "diffuseCoeff",
            "specularCoeff",
            "shininess",
            "reflectivity",
            "transmittance",
            "refractiveIndex"
        };

        try
        {
            name = j["name"];
        }
        catch (const nlohmann::detail::type_error &)
        {
            std::cerr << "Material number " << materialNumber
            << " has no name. This material can't be used" << std::endl;
            continue;
        }

        try
        {
            color.r = j["color"][0];
            color.g = j["color"][1];
            color.b = j["color"][2];
        }
        catch (const nlohmann::detail::type_error &)
        {
            std::cerr << "Material named " << name
            << " has no 'color'. Default value set to [255, 255, 255]" << std::endl;
        }

        for (uint i = 0; i < 6; i++)
        {
            try
            {
                carac[i] = j[paramNames[i]];
            }
            catch (const nlohmann::detail::type_error &)
            {
                std::cerr << "Material named " << name
                << " has no '" << paramNames[i] << "'. Default value set to 0" << std::endl;
            }
        }

        /*for (auto &a : carac)
            std::cout << a << std::endl;*/

        _mList.emplace(std::make_pair(name, Material(
            color,
            carac[0],
            carac[1],
            carac[2],
            carac[3],
            carac[4],
            carac[5]
        )));
        materialNumber++;
    }
}

void rt::JsonParser::parseObjects()
{
    uint nb = 1;
    for (json &j : _objects)
    {
        try
        {
            if (j["type"] == "sphere")
                parseSpheres(j, nb);
            else if (j["type"] == "plane")
                parsePlanes(j, nb);
        }
        catch(const nlohmann::detail::type_error &) {}
        nb++;
    }
}

void rt::JsonParser::parseSpheres(json &j, uint nb)
{
    rt::maths::Vector3f center;
    float radius = 1;
    std::string materialName = (*(_mList.begin())).first;
    std::string texturePath;
    std::size_t id = _scene.createObject(tSphere);

    try
    {
        center = j["center"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Object number " << nb
        << " of type Sphere miss a center, a default one has been attributed" << std::endl;
    }

    try
    {
        radius = j["radius"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Object number " << nb
        << " of type Sphere miss a radius, a default one has been attributed" << std::endl;
    }

    try
    {
        materialName = j["material"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Object number " << nb << " of type Sphere miss a material, the material named "
        << materialName << " has been attributed" << std::endl;
    }

    try
    {
        texturePath = j["texturePath"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Object number " << nb <<
        " of type Sphere miss a texture path, no default texture has been attributed" << std::endl;
    }

    _scene.ochangeCenter(id, center);
    _scene.ochangeRadius(id, radius);
    _scene.ochangeMaterial(id, _mList.at(materialName));
    if (texturePath.size() > 0)
        _scene.ochangeTexture(id, texturePath);
}

void rt::JsonParser::parsePlanes(json &j, uint nb)
{
    rt::maths::Vector3f normal(0.f, 1.f, 0.f);
    rt::maths::Vector3f point;
    std::string materialName = (*(_mList.begin())).first;
    std::string texturePath;
    std::size_t id = _scene.createObject(tPlane);

    try
    {
        normal = j["normal"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Object number " << nb
        << " of type Plane miss a normal vector, a default one has been attributed" << std::endl;
    }

    try
    {
        point = j["point"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Object number " << nb
        << " of type Plane miss a point, a default one has been attributed" << std::endl;
    }

    try
    {
        materialName = j["material"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Object number " << nb << " of type Plane miss a material, the material named "
        << materialName << " has been attributed" << std::endl;
    }

    try
    {
        texturePath = j["texturePath"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Object number " << nb
        << " of type Plane miss a texture path, no default texture has been attributed" << std::endl;
    }

    _scene.ochangeNormal(id, normal);
    _scene.ochangeCenter(id, point);
    _scene.ochangeMaterial(id, _mList.at(materialName));
    if (texturePath.size() > 0)
        _scene.ochangeTexture(id, texturePath);
}

void rt::JsonParser::parseLights()
{
    uint nb = 1;
    for (json &j : _lights)
    {
        try
        {
            if (j["type"] == "directional")
                parseDirectional(j, nb);
            else if (j["type"] == "spherical")
                parseSpherical(j, nb);
        }
        catch(const nlohmann::detail::type_error &) {}
        nb++;
    }
}

void rt::JsonParser::parseDirectional(json &j, uint nb)
{
    rt::maths::Vector3f direction;
    rt::Color color((uint) 255, 255, 255);
    float intensity = 1;
    std::size_t id = _scene.createLight(Directional);

    try
    {
        direction = j["direction"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Light number " << nb
        << " of type Directional miss a direction, default one has been attributed" << std::endl;
    }

    try
    {
        color.r = j["color"][0];
        color.g = j["color"][1];
        color.b = j["color"][2];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Light number " << nb
        << " of type Directional miss a color, default one has been attributed" << std::endl;
    }

    try
    {
        intensity = j["intensity"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Light number " << nb
        << " of type Directional miss an intensity, default one has been attributed" << std::endl;
    }

    _scene.lchangeDirection(id, direction);
    _scene.lchangeColor(id, color);
    _scene.lchangeIntensity(id, intensity);
}

void rt::JsonParser::parseSpherical(json &j, uint nb)
{
    rt::maths::Vector3f position;
    rt::Color color((uint) 255, 255, 255);
    float intensity = 1;
    std::size_t id = _scene.createLight(Spherical);

    try
    {
        position = j["position"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Light number " << nb
        << " of type Directional miss a direction, default one has been attributed" << std::endl;
    }

    try
    {
        color.r = j["color"][0];
        color.g = j["color"][1];
        color.b = j["color"][2];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Light number " << nb
        << " of type Directional miss a color, default one has been attributed" << std::endl;
    }

    try
    {
        intensity = j["intensity"];
    }
    catch (const nlohmann::detail::type_error &)
    {
        std::cerr << "Light number " << nb
        << " of type Directional miss an intensity, default one has been attributed" << std::endl;
    }

    _scene.lchangePosition(id, position);
    _scene.lchangeColor(id, color);
    _scene.lchangeIntensity(id, intensity);
}
