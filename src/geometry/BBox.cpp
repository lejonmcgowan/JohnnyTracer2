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
