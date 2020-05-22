#include <SFML/Graphics.hpp>

#include "Scene.hpp"

rt::Scene::Scene(float ambientLightCoeff)
    : _objects(), _lights(),
    _ambientLightCoeff(ambientLightCoeff), _hasChanged(true)
{

}

std::size_t rt::Scene::createObject(rt::ObjectType type)
{
    // Adding the object to memory if it exists.
    if (_objectFactory.find(type) == _objectFactory.end())
        return 0;
    auto id = addElementToList();
    _objects.emplace(id, _objectFactory[type]());

    return id;
}

std::vector<std::size_t> rt::Scene::createObjects(ObjectType type, std::size_t numberOfInstances)
{
    std::vector<std::size_t> ids;

    for (std::size_t it = 0; it != numberOfInstances; ++it)
    {
        std::size_t id = createObject(type);

        if (!id)
            continue; 
        
        ids.push_back(id);
    }
    return ids;
}

std::size_t rt::Scene::createLight(rt::LightType type)
{
    // Adding the object to memory if it exists.
    if (_lightFactory.find(type) == _lightFactory.end())
        return 0;

    auto id = addElementToList();
    _lights.emplace(id, _lightFactory[type]());

    return id;
}

std::vector<std::size_t> rt::Scene::createLights(rt::LightType type, std::size_t numberOfInstances)
{
    std::vector<std::size_t> ids;

    for (std::size_t it = 0; it != numberOfInstances; ++it)
    {
        std::size_t id = createLight(type);

        if (!id)
            continue; 
        
        ids.push_back(id);
    }
    return ids;
}

std::size_t rt::Scene::addElementToList()
{
    if (_elementIds.empty())
    {
        _elementIds.push_back(1);
    }
    else
    {
        _elementIds.push_back(_elementIds.back() + 1);
    }

    return _elementIds.back();
}

bool rt::Scene::hasObject(std::size_t id) const
{
    return _objects.find(id) != _objects.end();
}

bool rt::Scene::hasLight(std::size_t id) const
{
    return _lights.find(id) != _lights.end();
}

void rt::Scene::ochangeMaterial(std::size_t id, const rt::Material &material)
{
    if (!hasObject(id))
        return;

    ObjectType type = _objects[id]->type();

    // Trying to cast the object with its type.
    if (type == ObjectType::tSphere)
    {
        auto obj = static_cast<Sphere *>(_objects[id].get());

        obj->setMaterial(material);
    }
    else if (type == ObjectType::tPlane)
    {
        auto obj = static_cast<Plane *>(_objects[id].get());

        obj->setMaterial(material);
    }
    else if (type == ObjectType::tTriangle)
    {
        auto obj = static_cast<Triangle *>(_objects[id].get());

        obj->setMaterial(material);
    }
}

void rt::Scene::ochangeCenter(std::size_t id, const rt::maths::Vector3f &center)
{
    if (!hasObject(id))
        return;

    ObjectType type = _objects[id]->type();

    // Trying to cast the object with its type.
    if (type == ObjectType::tSphere)
    {
        auto obj = static_cast<Sphere *>(_objects[id].get());

        obj->setCenter(center);
    }
    else if (type == ObjectType::tPlane)
    {
        auto obj = static_cast<Plane *>(_objects[id].get());

        obj->setCenter(center);
    }
}

void rt::Scene::ochangeNormal(std::size_t id, const rt::maths::Vector3f &normal)
{
    if (!hasObject(id))
        return;

    ObjectType type = _objects[id]->type();

    // Trying to cast the object with its type.
    if (type == ObjectType::tPlane)
    {
        auto obj = static_cast<Plane *>(_objects[id].get());

        obj->setNormal(normal);
    }
}

void rt::Scene::ochangeRadius(std::size_t id, float radius)
{
    if (!hasObject(id))
        return;

    ObjectType type = _objects[id]->type();

    // Trying to cast the object with its type.
    if (type == ObjectType::tSphere)
    {
        auto obj = static_cast<Sphere *>(_objects[id].get());

        obj->setRadius(radius);
    }
}

void rt::Scene::ochangePoints(std::size_t id, const maths::Vector3f &p1, const maths::Vector3f &p2, const maths::Vector3f &p3)
{
    if (!hasObject(id))
        return;

    ObjectType type = _objects[id]->type();

    // Trying to cast the object with its type.
    if (type == ObjectType::tTriangle)
    {
        auto obj = static_cast<Triangle *>(_objects[id].get());

        obj->setVertices(p1, p2, p3);
    }
}

void rt::Scene::ochangeTexture(std::size_t id, const std::string &texture)
{
    if (!hasObject(id))
        return;

    _objects[id]->createTetxureFromFile(texture);
}

void rt::Scene::lchangePosition(std::size_t id, const maths::Vector3f &position)
{
    if (!hasLight(id))
        return;

    LightType type = _lights[id]->type();

    // Trying to cast the object with its type.
    if (type == LightType::Spherical)
    {
        auto obj = static_cast<SphericalLight *>(_lights[id].get());

        obj->setPosition(position);
    }
}

void rt::Scene::lchangeDirection(std::size_t id, const maths::Vector3f &direction)
{
    if (!hasLight(id))
        return;

    LightType type = _lights[id]->type();

    // Trying to cast the object with its type.
    if (type == LightType::Directional)
    {
        auto obj = static_cast<DirectionalLight *>(_lights[id].get());

        obj->setDirection(direction);
    }
}

void rt::Scene::lchangeColor(std::size_t id, const Color &color)
{
    if (!hasLight(id))
        return;

    _lights[id]->setColor(color);
}

void rt::Scene::lchangeIntensity(std::size_t id, float intensity)
{
    if (!hasLight(id))
        return;

    _lights[id]->setIntensity(intensity);
}