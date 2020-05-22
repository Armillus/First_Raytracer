#include "Triangle.hpp"

rt::Triangle::Triangle(const maths::Vector3f &p1, const maths::Vector3f &p2, const maths::Vector3f &p3,
                       const Material &material)
    : Object  { material, ObjectType::tTriangle }
    , _v1     { p1                              }
    , _v2     { p2                              }
    , _v3     { p3                              }
    , _center { 0, 0, 0                         }
{
    computeNormal();
}

rt::Triangle::Triangle(const maths::Vector3f &p1, const maths::Vector3f &p2, const maths::Vector3f &p3,
                       const Material &material, const std::string &textureFilepath)
    : Object  { material, textureFilepath, ObjectType::tTriangle }
    , _v1     { p1                                               }
    , _v2     { p2                                               }
    , _v3     { p3                                               }
    , _center { 0, 0, 0                                          }
{
    computeNormal();
}

bool rt::Triangle::intersect(const Ray &ray, float *t) const
{
    auto v0v1 = _v2 - _v1; 
    auto v0v2 = _v3 - _v1; 
    auto pvec = ray.direction().cross(v0v2); 
    float det = v0v1 * pvec; 

    if (std::fabs(det) < 1e-8)
        return false; 

    float invDet = 1 / det; 
    auto tvec = ray.origin() - _v1; 

    float u = tvec * pvec * invDet; 
    if (u < 0 || u > 1)
        return false; 

    auto qvec = tvec.cross(v0v1); 

    float v = ray.direction() * qvec * invDet; 
    if (v < 0 || u + v > 1)
        return false;

    if (v0v2 * qvec * invDet < *t)
    {
        *t = v0v2 * qvec * invDet; 
        return true;
    }
 
    return false;
}

rt::Color rt::Triangle::color([[maybe_unused]] const maths::Vector3f &point) const
{
    // No textures for the time being.
    return _material.color;
}