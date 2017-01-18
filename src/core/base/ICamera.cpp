//
// Created by lejonmcgowan on 9/4/16.
//

#include "ICamera.h"

ICamera::ICamera(Transform transform, const Film& film):
cameraToWorld(transform),
film(film)
{

}

float ICamera::generateRayDifferentials(const ICamera::CameraSample& sample, Ray *ray) const
{
    float weight = generateRay(sample,ray);
    //get camera stuff
    //x
    CameraSample shift = sample;
    shift.filmPoint.x++;
    Ray rx(Vec3(0,0,0));
    float weightX = generateRay(shift,&rx);
    if(!weightX)
        return 0;
    ray->originDiffX = rx.origin;
    ray->directionDiffX = rx.direction;
    //y
    shift.filmPoint.y++;
    Ray ry(Vec3(0,0,0));
    float weightY = generateRay(shift,&rx);
    if(!weightY)
        return 0;
    ray->originDiffY = rx.origin;
    ray->directionDiffY = rx.direction;

    ray->hasDifferentials = true;

    return weight;
}

