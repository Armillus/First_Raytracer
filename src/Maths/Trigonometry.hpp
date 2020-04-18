#pragma once

#define M_PI 3.14159265358979323846

namespace rt::maths {

    template<typename T>
    static constexpr inline T toRadians(const T &angleInDegrees)
    {
        return (angleInDegrees * M_PI / 180.0);
    }

    template<typename T>
    static constexpr inline T toDegrees(const T &angleInRadians)
    {
        return (angleInRadians * 180.0 / M_PI);
    }

}

#undef M_PI