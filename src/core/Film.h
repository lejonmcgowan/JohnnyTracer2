//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_IFILM_H
#define JOHNNYRENDERER2_IFILM_H


#include "utils/UnitUtils.h"
#include <memory>
#include "IFilter.h"
class Film
{
protected:
    Vec2 res;
    std::unique_ptr<IFilter> filter;
    std::string filename;
public:
    Film(Vec2 resolution, IFilter& filter, std::string filename);
};


#endif //JOHNNYRENDERER2_IFILM_H
