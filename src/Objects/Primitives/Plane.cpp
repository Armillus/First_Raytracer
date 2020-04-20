#include "Plane.hpp"

rt::Plane::Plane(const maths::Vector3f &normal,
                 const maths::Vector3f &point,
                 const Material &mat)
    : Object(mat), _normal(normal), _point(point)
{

}

rt::Plane::Plane(const maths::Vector3f &normal,
                 const maths::Vector3f &point,
                 const Material &mat,
                 const std::string &textureFilepath)
    : Object(mat, textureFilepath), _normal(normal), _point(point)
{

}

bool rt::Plane::intersect(const Ray &ray, float *t) const
{
    float denominator = ray.direction() * _normal;

    if (std::abs(denominator) > 0.001f)
    {
        float res = ((_point - ray.origin()) * _normal) / denominator;

        if (res >= 0.001f && res < *t)
        {
            *t = res;
            return true;
        }
    }
    return false;
}

rt::Color rt::Plane::color(const maths::Vector3f &point) const
{
    if (_texture && _texture->isLoaded())
    {
        auto u = _normal.cross({0, 0, 1}).normalize();

        //If normal and (1,0,0) are parallel, change e1
        if (u == maths::Vector3f(0, 0, 0)) {
            u = _normal.cross({1, 0, 0}).normalize();
        }

        const auto v(_normal.cross(u).normalize());

        uint x = std::abs(std::floor(point * u));
        uint y = std::abs(std::floor(point * v));        

        return _texture->getTextureColor(x, y);
    }
    return _material.color;
}
