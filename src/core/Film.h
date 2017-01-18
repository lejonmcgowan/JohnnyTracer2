//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_IFILM_H
#define JOHNNYRENDERER2_IFILM_H


#include "utils/UnitUtils.h"
#include <memory>
#include "core/base/IFilter.h"
class Film
{
private:
    friend class ProjectionCamera;

    Vec2 res;
    std::unique_ptr<IFilter> filter;
    std::string filename;
public:
    Film(Vec2 resolution, std::unique_ptr<IFilter>& filter, std::string filename);
};


#endif //JOHNNYRENDERER2_IFILM_H
