//
// Created by lejonmcgowan on 12/28/16.
//

#ifndef JOHNNYRENDERER2_INTERSECTION_H
#define JOHNNYRENDERER2_INTERSECTION_H
#include <core/utils/Constants.h>
#include <geometry/Ray.h>

struct Interaction
{
    // Interaction Public Data
    Point hitPoint;
    //negative ray direction
    Vec3 wo;
    Vec3 normal;
    Vec3 pError;

    Interaction(){}

    Interaction(const Point HitPoint):
            hitPoint(hitPoint),normal(Vec3()),wo(Vec3()),pError(Vec3(0,0,0)){}

    Interaction(const Point HitPoint, const Vec3 normal, const Vec3 wo):
        hitPoint(hitPoint),normal(normal),wo(wo),pError(Vec3(0,0,0)){}

    inline Ray spawnRay(const Vec3 d){return Ray(Constants::offsetRayOrigin(hitPoint,pError,normal,d),d);}
    Ray spawnRayTo(const Point point)
    {
        Point origin = Constants::offsetRayOrigin(hitPoint,pError,normal,point - hitPoint);
        Vec3 direction = glm::normalize(point - origin);
        return Ray(origin,direction, 1 - Constants::shadowEpsilon);
    }
    Ray spawnRayTo(const Interaction &it) const
    {
        Point origin = Constants::offsetRayOrigin(hitPoint, pError, normal, it.hitPoint - hitPoint);
        Point target = Constants::offsetRayOrigin(it.hitPoint, it.pError, it.normal, origin - it.hitPoint);
        Vec3 d = target - origin;
        return Ray(origin, d, 1 - Constants::shadowEpsilon);
    }
};
#endif //JOHNNYRENDERER2_INTERSECTION_H
