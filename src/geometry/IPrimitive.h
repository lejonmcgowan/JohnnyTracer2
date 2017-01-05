//
// Created by lejonmcgowan on 8/1/16.
//

#ifndef JOHNNYRENDERER2_IPRIMITIVE_H
#define JOHNNYRENDERER2_IPRIMITIVE_H
#include <memory>
#include <vector>
#include <core/base/IMaterial.h>

#include "Ray.h"
#include "core/BBox.h"
#include "SurfaceInteraction.h"

class AreaLight;

class IPrimitive
{
public:
    // Primitive Interface
    virtual ~IPrimitive(){};
    virtual BBox WorldBound() const = 0;
    virtual bool intersect(const Ray &r, SurfaceInteraction *) const = 0;
    virtual bool intersectQuick(const Ray &r) const = 0;
    virtual const AreaLight *GetAreaLight() const = 0;
    virtual const IMaterial *GetMaterial() const = 0;

    //note: you may wanna look back into pg. 960 for adding a "Transport Mode" parameter
    virtual void ComputeScatteringFunctions(SurfaceInteraction *isect, bool allowMultipleLobes) const = 0;
};

/*virtually the same funcitionality (with error catching in pbrt), but I'd rather just keep it abstract.
 * Thi word will be used to deliniate between "node" primitives and "structure" primitives (accellerators)*/
class Aggregate: public IPrimitive{};

#endif //JOHNNYRENDERER2_IPRIMITIVE_H
