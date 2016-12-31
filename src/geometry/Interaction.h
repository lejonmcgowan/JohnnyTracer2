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
};
#endif //JOHNNYRENDERER2_INTERSECTION_H
