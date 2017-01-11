//
// Created by lejonmcgowan on 1/5/17.
//

#include "GeomPrimitive.h"

BBox GeomPrimitive::worldBound()
{
    return shape->getWorldBounds();
}

bool GeomPrimitive::intersect(Ray& r, SurfaceInteraction *interaction)
{
    IShape::HitPacket packet(*interaction);
    if (!shape->intersect(r,packet))
        return false;

    //if you make it here, it hit successfully and, due to the previous tMax, it is the closest object
    r.tMax = packet.tHit;
    interaction->primitive = this;
    return true;
}
bool GeomPrimitive::intersectQuick(Ray& r) const
{
    return shape->intersectQuick(r);
}
const std::shared_ptr<AreaLight> GeomPrimitive::getAreaLight() const
{
    return areaLight;
}
const std::shared_ptr<IMaterial> GeomPrimitive::getMaterial() const
{
    return material;
}

void GeomPrimitive::computeScatteringFunctions(SurfaceInteraction *isect, bool allowMultipleLobes) const
{
    if(material)
        material->computeScatteringFunctions(isect, allowMultipleLobes);
}

GeomPrimitive::GeomPrimitive(const std::shared_ptr<IShape> shape,
                             const std::shared_ptr<IMaterial> material,
                             const std::shared_ptr<AreaLight> areaLight)
    : shape(shape), material(material), areaLight(areaLight) {}
