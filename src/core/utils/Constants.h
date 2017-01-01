//
// Created by lejonmcgowan on 12/28/16.
//

#ifndef JOHNNYRENDERER2_CONSTUTILS_H
#define JOHNNYRENDERER2_CONSTUTILS_H

namespace Constants
{
    const float machineEpsilon = std::numeric_limits<float>::epsilon() * 0.5f;
    inline const float gamma(int n)
    {
        return (n * machineEpsilon) / (1 - n * machineEpsilon);
    }

}
#endif //JOHNNYRENDERER2_CONSTUTILS_H
