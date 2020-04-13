#pragma once

#include <cmath>

#include "Object.hpp"

namespace rt {

    class Sphere : public Object {
    public:
        Sphere(const maths::Vector3f &center, float radius) : Object({0u, 0u, 255u}), _center(center), _radius(radius) {}
        Sphere(const maths::Vector3f &center, float radius, const Color &color)
            : Object(color), _center(center), _radius(radius) {}
        ~Sphere() override = default;


        /*  Well, this part of the code needs some explanations.
            
            In order to know if the ray intersects a sphere, we must 
            find at least one common point between the ray and the sphere.

            To achieve that, we must have the equation of the sphere and the equation of the ray.
            In one hand, the equation of a sphere is:
                
            (x - a)2 - (y - b)2 - (z - c)2 = r2

            With a, b and c the coordinates of the center of the sphere, and r its radius.
            Now, we assume that we have a vector p(x, y, z) on a sphere of center c (which can be translated as a vector).
            We can then transform the equation, which becomes the following one:

            ->  ->    ->  ->            (or)         ->  ->
            (p - c) . (p - c) = r2      <==>        (p . c)2 = r2

            In the other hand, we have the ray equation, defined below:

            ->      ->  ->
            p = t * d + p0

            With p the current point, p0 the origin of the ray, d the direction (as a vector) of the ray,
            and finally t which is a parametric variable.

            Now, we can substitute the values of p in the sphere equation:

                  ->  ->    ->         ->  ->    ->         (or)          ->  ->    ->
            ((t * d + p0) - c) . ((t * d + p0) - c) = r2    <==>    ((t * d + p0) - c)2 = r2

            We can observe that we have a remarkable identity, (a + b)2. ---------------*
            hence, we can solve with ease the equation:                                 |
                                                                                        |
            ((t * d) + (p0 - c)) . ((t * d) + (p0 - c)) - r2 = 0    <==>    (a + b) * (a + b) - c  = 0 
            
            [d . d * t2] + [2 * (d * (p0 - c) * t)] + [(p0 - c)2 - r2] = 0
                  A      +            B             +         C        = 0

            Our equation looks like this now : at + bt + c = 0
            It means that it is a quadratic equation, or a second degree polynomial.
            The value of the discriminant delta will be the number of intersections between the ray and the sphere.
        */
        bool intersect(Ray &ray, float *t) override
        {
            // To determine if a ray intersects with the sphere, we don't need to know t.

            //     ->  ->
            // a = d . d
            float a = ray.direction() * ray.direction();

            // Now, we compute the distance between the origin of the ray and the position of the circle.
            //            ->   ->
            // distance = p0 - c
            maths::Vector3f distance = ray.origin() - _center;

            //         ->   ->   ->                      ->  ->
            // b = 2 * d * (p0 - c)     <==>     b = 2 * d * distance
            float b = 2 * (ray.direction() * distance);

            //      ->   ->    ->   ->                       ->         ->
            // c = (p0 - c) . (p0 - c) - r2     <==>     c = distance . distance - (_radius)2
            float c = distance.squarePower() - (_radius * _radius);

            // We are solving the discriminant of the second degree polynomial.
            float delta = b * b - 4 * a * c;

            // If delta < 0, there is no intersection. Otherwise, it means there are one or two intersections.
            if (delta < 0)
                return false;

            float deltaSquareRoot = ::sqrtf(delta);
            float t0 = (-b + deltaSquareRoot) / 2;
            float t1 = (-b - deltaSquareRoot) / 2;

            if (t0 > t1)
                t0 = t1;

            if (t0 > 0.001f && t0 < *t)
            {
                *t = t0;
                return true;
            }
            return false;
        }

        inline maths::Vector3f normalSurface(maths::Vector3f &p)
        {
            //return (p - _center) * (-1 / _radius);
            auto v = p - _center;

            return v.normalize();
        }

        inline maths::Vector3f &center()
        {
            return _center;
        }

    private:
        maths::Vector3f _center;
        float _radius; 
    };

}