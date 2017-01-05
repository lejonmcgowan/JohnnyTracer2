//
// Created by lejonmcgowan on 12/29/16.
//

#ifndef JOHNNYRENDERER2_BOXFILTER_H
#define JOHNNYRENDERER2_BOXFILTER_H


#include <core/base/IFilter.h>
class BoxFilter: public IFilter
{
public:
    BoxFilter(const Vec2 radius);

    Number evaluate(const Point2D point) override;

};


#endif //JOHNNYRENDERER2_BOXFILTER_H
