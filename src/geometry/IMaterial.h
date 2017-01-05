//
// Created by lejonmcgowan on 1/3/17.
//

#ifndef JOHNNYRENDERER2_IMATERIAL_H
#define JOHNNYRENDERER2_IMATERIAL_H
#include "SurfaceInteraction.h"
class IMaterial
{
public:
    // Material Interface
    virtual void ComputeScatteringFunctions(SurfaceInteraction *si,
                                            bool allowMultipleLobes) const = 0;
    virtual ~Material(){};
};
#endif //JOHNNYRENDERER2_IMATERIAL_H
