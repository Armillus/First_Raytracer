#include "Plane.hpp"

rt::Plane::Plane(const maths::Vector3f &normal,
                 const maths::Vector3f &point,
                 const Material &mat)
    : Object  { mat, ObjectType::tPlane }
    , _normal { normal                  }
    , _point  { point                   }
{

}

rt::Plane::Plane(const maths::Vector3f &normal,
                 const maths::Vector3f &point,
                 const Material &mat,
                 const std::string &textureFilepath)
    : Object  { mat, textureFilepath, ObjectType::tPlane }
    , _normal { normal                                   }
    , _point  { point                                    }
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
        auto u = _normal.cross({0.f, 0.f, 1.f}).normalize();

        //If normal and (1,0,0) are parallel, change u
        if (u == maths::Vector3f(0.f, 0.f, 0.f))
        {
            u = _normal.cross({1.f, 0.f, 0.f}).normalize();
        }

        const auto v(_normal.cross(u).normalize());

        long int x = point * u;
        long int y = point * v;

        normalizeTextureCoordinates(x, y);
        return _texture->getTextureColor((uint) x, (uint) y);
    }
    return _material.color;
}

void rt::Plane::normalizeTextureCoordinates(long int &x, long int &y) const
{
    auto width = _texture->width();
    auto height = _texture->height();

    // std::cout << "BEFORE : x = " << x << " | y = " << y << " | hitPoint = " << point << std::endl;
    if (x < 0u)
    {
        x = -x % width;
        x = width - x - 1;
    }
    else if (x >= width)
    {
        x %= width;
    }
    
    if (y < 0u)
    {
        y = -y % height;
        y = height - y - 1;

    }
    else if (y >= height)
    {
        y %= height;
    }
}

