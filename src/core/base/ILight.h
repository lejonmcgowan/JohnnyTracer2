//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_ILIGHT_H
#define JOHNNYRENDERER2_ILIGHT_H

#include <core/Transform.h>

class ILight
{
public:
    const int numSamples;
protected:
    Transform transform;

public:
    ILight(Transform transform, int numSamples = 1);
};
#endif //JOHNNYRENDERER2_ILIGHT_H
