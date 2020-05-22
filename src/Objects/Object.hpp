#pragma once

#include "IObject.hpp"

namespace rt {

    class Object : public IObject {
    public:

        Object(const Material &mat, ObjectType type)
            : _texture  { nullptr }
            , _material { mat     }
            , _type     { type    }
        {}
        Object(const Material &mat, const std::string &textureFilepath, ObjectType type)
            : _texture  { std::make_unique<SfmlTexture>(textureFilepath) }
            , _material { mat                                            }
            , _type     { type                                           }
        {}
        
        virtual ~Object() = default;

        inline Material const &material() const override
        {
            return _material;
        }

        inline void createTetxureFromFile(const std::string &filepath) override
        {
            _texture.reset(new SfmlTexture(filepath));
        }

        inline ObjectType type() const override
        {
            return _type;
        } 

    protected:
        std::unique_ptr<Texture> _texture;
        Material _material;
        ObjectType _type;
    };

}