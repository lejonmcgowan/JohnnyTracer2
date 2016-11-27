//
// Created by lejonmcgowan on 8/1/16.
//

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
BBox::BBox():BBox(glm::vec3(),glm::vec3())
{

}
BBox::BBox(glm::vec3 min, glm::vec3 max):min(min),max(max)
{

}

BBox BBox::operator*(Mat4 trans)
{
    Vec3 newMin, newMax;
    Vec4 tempNewMin = trans * Vec4(min,0.0);
    Vec4 tempNewMax = trans * Vec4(max,0.0);
    newMin << tempNewMin[0],tempNewMin[1],tempNewMin[2];
    newMax << tempNewMax[0],tempNewMax[1],tempNewMax[2];

    return BBox(newMin,newMax);
}

BBox BBox::operator*(Transform trans)
{
    return operator*(trans.getTransMatrix());
}
