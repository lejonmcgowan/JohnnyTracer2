//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_IMATERIAL_H
#define JOHNNYRENDERER2_IMATERIAL_H

class SurfaceInteraction;

class IMaterial
{
public:
    virtual void computeScatteringFunctions(SurfaceInteraction* isect, bool allowMultipleLobes) = 0;
};


#endif //JOHNNYRENDERER2_IMATERIAL_H
