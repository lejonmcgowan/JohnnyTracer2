//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_ICAMERA_H
#define JOHNNYRENDERER2_ICAMERA_H


#include <utils/UnitUtils.h>
#include <geometry/Transform.h>
#include "Film.h"

class ICamera
{
protected:
    const Film& film;
    Transform transform;
public:
    ICamera(Transform transform, const Film& film);
};


#endif //JOHNNYRENDERER2_ICAMERA_H
