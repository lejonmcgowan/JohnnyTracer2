//
// Created by lejonmcgowan on 8/1/16.
//

#ifndef JOHNNYRENDERER2_IPRIMITIVE_H
#define JOHNNYRENDERER2_IPRIMITIVE_H
#include <memory>
#include <vector>
#include <core/base/IMaterial.h>

#include "geometry/Ray.h"
#include "core/BBox.h"

class AreaLight;
class SurfaceInteraction;

class IPrimitive
{
public:
    // Primitive Interface
    virtual ~IPrimitive(){};
    virtual BBox worldBound() = 0;
    virtual bool intersect(Ray &r, SurfaceInteraction *) = 0;
    virtual bool intersectQuick(Ray &r) const = 0;
    virtual const std::shared_ptr<AreaLight> getAreaLight() const = 0;
    virtual const std::shared_ptr<IMaterial> getMaterial() const = 0;

    //note: you may wanna look back into pg. 960 for adding a "Transport Mode" parameter
    virtual void computeScatteringFunctions(SurfaceInteraction *isect, bool allowMultipleLobes) const = 0;
};

/*virtually the same funcitionality (with error catching in pbrt), but I'd rather just keep it abstract.
 * Thi word will be used to deliniate between "node" primitives and "structure" primitives (accellerators)*/
class Aggregate: public IPrimitive{};

#endif //JOHNNYRENDERER2_IPRIMITIVE_H
