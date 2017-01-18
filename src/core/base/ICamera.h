//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_ICAMERA_H
#define JOHNNYRENDERER2_ICAMERA_H


#include "core/utils/UnitUtils.h"
#include <core/Transform.h>
#include <geometry/Ray.h>
#include "core/Film.h"

class ICamera
{
public:
    struct CameraSample
    {
        Point2D lensPoitnt;
        Point2D filmPoint;
    };
protected:
    const Film& film;
    Transform cameraToWorld;
public:
    ICamera(Transform transform, const Film& film);
    virtual float generateRay(const CameraSample&, Ray* ray) const = 0;
    float generateRayDifferentials(const CameraSample& sample, Ray* ray) const;
};


#endif //JOHNNYRENDERER2_ICAMERA_H
