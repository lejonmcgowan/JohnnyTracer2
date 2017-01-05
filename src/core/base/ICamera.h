//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_ICAMERA_H
#define JOHNNYRENDERER2_ICAMERA_H


#include "core/utils/UnitUtils.h"
#include <core/Transform.h>
#include "core/Film.h"

class ICamera
{
protected:
    const Film& film;
    Transform transform;
public:
    ICamera(Transform transform, const Film& film);
};


#endif //JOHNNYRENDERER2_ICAMERA_H
