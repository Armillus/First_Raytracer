#pragma once

#include "Ray.hpp"
#include "Material.hpp"
#include "SfmlTexture.hpp"

namespace rt {

    class Object {
    public:
        Object(const Material &mat)
            : _texture(nullptr), _material(mat)
        {}
        Object(const Material &mat, const std::string &textureFilepath)
            : _texture(std::make_unique<SfmlTexture>(textureFilepath)),
              _material(mat)
        {}
        
        virtual ~Object() = default;

        virtual bool intersect(const Ray &ray, float *t) const = 0;
        virtual maths::Vector3f normalSurface(maths::Vector3f &p) const = 0;
        virtual maths::Vector3f const &center() const = 0;
        virtual Color color(const maths::Vector3f &point) const = 0;

        inline constexpr Material const &material() const
        {
            return _material;
        }

        inline void createTetxureFromFile(const std::string &filepath)
        {
            _texture.reset(new SfmlTexture(filepath));
        }

    protected:
        std::unique_ptr<Texture> _texture;
        Material _material;
    };

}