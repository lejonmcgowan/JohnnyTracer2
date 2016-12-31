//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_GEOMDATA_H
#define JOHNNYRENDERER2_GEOMDATA_H

#include "Interaction.h"

class IShape;

struct SurfaceInteraction: public Interaction
{
    struct Partials
    {
        Vec3 u;
        Vec3 v;
    };
    Point2D uv;
    Partials partialPoints;
    Partials partialNormals;
    std::shared_ptr<IShape> shape;
};
#endif //JOHNNYRENDERER2_GEOMDATA_H
