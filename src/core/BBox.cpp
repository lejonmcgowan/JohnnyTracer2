//
// Created by lejonmcgowan on 8/1/16.
//

#include <algorithm>
#include "BBox.h"
void BBox::setMin(const glm::vec3& min)
{
    BBox::min = min;
}
void BBox::setMax(const glm::vec3& max)
{
    BBox::max = max;
}
Vec3 BBox::getMin() const
{
    return min;
}
Vec3 BBox::getMax() const
{
    return max;
}
BBox::BBox():BBox(Vec3(),Vec3())
{

}
BBox::BBox(Vec3 min, Vec3 max):min(min),max(max)
{

}

BBox BBox::operator*(Mat4 trans)
{
    Vec3 newMin, newMax;
    Vec4 tempNewMin = trans * Vec4(min,0.0);
    Vec4 tempNewMax = trans * Vec4(max,0.0);
    newMin = Vec3(tempNewMin[0],tempNewMin[1],tempNewMin[2]);
    newMax = Vec3(tempNewMax[0],tempNewMax[1],tempNewMax[2]);

    return BBox(newMin,newMax);
}

BBox BBox::operator*(Transform trans)
{
    return operator*(trans.getTransMatrix());
}
/**
 * as if we are intersecting with 3 pairs of axis-aligned planes, taking into account
 * the boxes limitations
 * @param ray the ray to test intersection with
 * @return whether or not the ray intersects the bounding box
 */
bool BBox::inersectQuick(const Ray& ray)
{
    Number t0 = 0, t1 = ULONG_MAX;
    for(int i = 0; i < 3; i++)
    {
        Number invRayDir = 1 / ray.direction[i];
        Number near = (min[i] - ray.origin[i]) * invRayDir;
        Number far = (max[i] - ray.origin[i]) * invRayDir;
        #ifdef DOUBLE_PRECISION
            //offset floating point error
            far *= 1 + 2 * gamma(3);
        #endif
        if(near > far)
            std::swap(near,far);

        t0 = near > t0 ? near : t0;
        t1 = far < t1 ? far : t1;

        if(t0 < t1)
            return false;
    }
    return true;
}
