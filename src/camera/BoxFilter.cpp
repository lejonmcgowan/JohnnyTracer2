//
// Created by lejonmcgowan on 12/29/16.
//

#include "BoxFilter.h"
BoxFilter::BoxFilter(const Vec2 radius)
    : IFilter(radius) {}

Number BoxFilter::evaluate(const Point2D point)
{
    return 1;
}
