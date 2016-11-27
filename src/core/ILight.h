//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_ILIGHT_H
#define JOHNNYRENDERER2_ILIGHT_H

#include <geometry/Transform.h>

class ILight
{
protected:
    Transform transform;
    int numSamples;
public:
    ILight(Transform transform, int numSamples = 1);
};
#endif //JOHNNYRENDERER2_ILIGHT_H
