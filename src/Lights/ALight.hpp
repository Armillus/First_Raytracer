#pragma once

#include "ILight.hpp"

namespace rt {

    class ALight : public ILight {
    public:
        ALight(const Color &color, float intensity, LightType type)
            : _color     { color     }
            , _intensity { intensity }
            , _type      { type      }
        {
        }

        ~ALight() override = default;

        inline const Color &color() const override
        {
            return _color;
        }

        inline const LightType &type() const override
        {
            return _type;
        }

        inline void setIntensity(float intensity) override
        {
            _intensity = intensity;
        }

        inline void setColor(const Color &color) override
        {
            _color = color;
        }

    protected:
        Color _color;
        float _intensity;
        LightType _type;
    };
}