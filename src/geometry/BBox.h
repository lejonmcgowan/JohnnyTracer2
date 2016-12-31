//
// Created by lejonmcgowan on 8/1/16.
//

#ifndef JOHNNYRENDERER2_BBOX_H
#define JOHNNYRENDERER2_BBOX_H
#include "utils/UnitUtils.h"
#include "Transform.h"
#include "Ray.h"

class BBox
{
private:
    Vec3 min;
    Vec3 max;
public:
    BBox();
    BBox(glm::vec3 min,glm::vec3 max);
    void setMin(const glm::vec3& min);
    void setMax(const glm::vec3& max);
    Vec3 getMin() const;
    Vec3 getMax() const;

    bool inersectQuick(const Ray& ray);

    /**
     * other useful utility functions. Ex. get the 8 points of the box,compute box volume, etc.
     */

    /**
     * transforms this bounding boxes points and
     * returns a new, transformed
     * @param trans th transformatino to apply to the box
     * @return a new box transformed by the transformation matrix
     */
    BBox operator*(Mat4 trans);
    BBox operator*(Transform trans);
};


#endif //JOHNNYRENDERER2_BBOX_H
