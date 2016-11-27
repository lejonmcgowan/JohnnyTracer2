//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_ICAMERA_H
#define JOHNNYRENDERER2_ICAMERA_H


#include <utils/UnitUtils.h>
#include <geometry/Transform.h>
#include "IFilm.h"

class ICamera
{
protected:
    Vec2 shutterRange;
    IFilm film;
    Transform transform;
public:
    ICamera(Transform transform, Vec2 shutterRange, IFilm film);
};


#endif //JOHNNYRENDERER2_ICAMERA_H
