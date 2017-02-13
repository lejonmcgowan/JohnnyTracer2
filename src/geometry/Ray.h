//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_RAY_H_H
#define JOHNNYRENDERER2_RAY_H_H

#include <core/utils/UnitUtils.h>

//todo: keep in mind the differential directions for more fancy stuff later on
struct Ray
{
    Point origin;
    Vec3 direction;
    Number tMax;

    //for camera stuff
    bool hasDifferentials = false;
    Vec3 originDiffX, originDiffY;
    Vec3 directionDiffX, directionDiffY;

    /**
     * constructor for all fields
     */
    Ray(Point origin, Vec3 direction, Number tMax = NumberInfinity):origin(origin),direction(direction),tMax(tMax){}

    /**
     * constructor for a base ray (0 depth, 0 time) at the origin
     */
    Ray(Vec3 direction):Ray(Point(0,0,0),direction,0){}

    /**
     * calculates a point along the ray based on the given time
     *
     * @return a Number representing the point along the ray at the givent time t
     */
    Point calcPoint(float t) const {return origin + direction * t;}


    void scaleDifferentials(Number s)
    {
        originDiffX = s * (originDiffX - origin) + origin;
        originDiffY = s * (originDiffY - origin) + origin;
        directionDiffX = s * (directionDiffX - direction) + direction;
        directionDiffY = s * (directionDiffY - direction) + direction;
    }
};
#endif //JOHNNYRENDERER2_RAY_H_H
