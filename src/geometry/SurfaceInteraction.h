//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_GEOMDATA_H
#define JOHNNYRENDERER2_GEOMDATA_H

#include <core/IPrimitive.h>
#include "Interaction.h"

#include <iostream>
class IShape;

struct SurfaceInteraction: public Interaction
{
    //todo need to refer back to pg. 116 for further implementation
    struct Partials
    {
        Vec3 u;
        Vec3 v;

        Partials& operator=(const Partials other)
        {
            u = other.u;
            v = other.v;
            return *this;
        }
    };

    struct Shading
    {
        Vec3 normal;
        Partials partialPoints;
        Partials partialNormals;
    };

    IPrimitive* primitive;
    Point2D uv;
    Partials partialPoints;
    Partials partialNormals;
    const std::shared_ptr<IShape> shape;

    Shading shading;

    SurfaceInteraction(const Point& HitPoint, const Vec3& normal, const Vec3& wo, Number time,
    Partials partialPoints, Partials partiialNormals, std::shared_ptr<IShape> shape)
        : Interaction(HitPoint, normal, wo, time),partialPoints(partialPoints),partialNormals(partiialNormals),
    shape(shape)
    {
        //set the shaidng copies for use in BSDFs later
        shading.n = normal;
        shading.partialPoints = partialPoints;
        shading.partialNormals = partiialNormals;
    }
    void computeScatteringFunctions(SurfaceInteraction* isect, bool allowMultipleNodes)
    {
        //todo for textures: implement computeDifferentials
        if(primitive)
            primitive->computeScatteringFunctions(isect,allowMultipleNodes);
        else
            std::cerr << "Warning: primitive in surfaceinteraction is null" << std::endl;
    }
};
#endif //JOHNNYRENDERER2_GEOMDATA_H
