//
// Created by lejonmcgowan on 8/1/16.
//

#ifndef JOHNNYRENDERER2_BBOX_H
#define JOHNNYRENDERER2_BBOX_H
#include "UnitUtils.h"

class BBox
{
private:
    Vec3 min,max;
public:
    BBox();
    BBox(glm::vec3 min,glm::vec3 max);
    void setMin(const glm::vec3& min);
    void setMax(const glm::vec3& max);
    Vec3 getMin() const;
    Vec3 getMax() const;

    /**
     * other useful utility functions. Ex. get the 8 points of the box,compute box volume, etc.
     */
};


#endif //JOHNNYRENDERER2_BBOX_H
