//
// Created by lejonmcgowan on 12/28/16.
//

#ifndef JOHNNYRENDERER2_INTERSECTION_H
#define JOHNNYRENDERER2_INTERSECTION_H
struct Interaction
{
    // Interaction Public Data
    Point hitPoint;
    Number time;
    //negative ray direction
    Vec3 wo;
    Vec3 normal;

    Interaction(const Point HitPoint, const Vec3 normal, const Vec3 wo, Number time):
        hitPoint(hitPoint),normal(normal),wo(wo),time(time){}
};
#endif //JOHNNYRENDERER2_INTERSECTION_H
