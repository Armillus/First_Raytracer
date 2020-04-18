#pragma once

namespace rt {

    struct Resolution {
        
        inline bool operator==(const Resolution &res)
        {
            return (res.width == width && res.height == height);
        }
        
        inline bool operator!=(const Resolution &res) const
        {
            return (res.width != width || res.height != height);
        }

        unsigned int width;
        unsigned int height;
    };

}