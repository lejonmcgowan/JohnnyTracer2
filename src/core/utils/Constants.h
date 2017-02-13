//
// Created by lejonmcgowan on 12/28/16.
//

#ifndef JOHNNYRENDERER2_CONSTUTILS_H
#define JOHNNYRENDERER2_CONSTUTILS_H


#include <algorithm>
#include "UnitUtils.h"

namespace Constants
{
    const Number shadowEpsilon = 0.0001;

    //floating point error offset
    const float machineEpsilon = std::numeric_limits<float>::epsilon() * 0.5f;
    inline const float gamma(int n)
    {
        return (n * machineEpsilon) / (1 - n * machineEpsilon);
    }
    inline Number clamp (Number num, Number min, Number max)
    {
        return std::min(std::max(num,min),max);
    }
    inline Point offsetRayOrigin(const Point p, const Vec3 pError, const Vec3 normal, const Vec3 w)
    {
        Vec3 offset = dot(glm::abs(normal),pError) * normal;
        Point pOffset = p + offset;
        if(dot(offset,w) < 0)
            offset *= -1;

        return pOffset;
    }

}
#endif //JOHNNYRENDERER2_CONSTUTILS_H
