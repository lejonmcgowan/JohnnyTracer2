//
// Created by lejonmcgowan on 1/5/17.
//

#ifndef JOHNNYRENDERER2_GEOMPRIMITIVE_H
#define JOHNNYRENDERER2_GEOMPRIMITIVE_H


#include <core/IPrimitive.h>
#include <core/base/IShape.h>
class GeomPrimitive: public IPrimitive
{
private:
    const std::shared_ptr<IShape> shape;
    const std::shared_ptr<IMaterial> material;
    std::shared_ptr<AreaLight> areaLight;
    //future feature: mediumInteface
public:
    GeomPrimitive(const std::shared_ptr<IShape> shape,
                  const std::shared_ptr<IMaterial> material,
                  const std::shared_ptr<AreaLight> areaLight = nullptr);
    BBox worldBound() override;
    bool intersect(Ray& r, SurfaceInteraction *interaction) override;
    bool intersectQuick(Ray& r) const override;
    const std::shared_ptr<AreaLight> getAreaLight() const override;
    const std::shared_ptr<IMaterial> getMaterial() const override;
    void computeScatteringFunctions(SurfaceInteraction *isect, bool allowMultipleLobes) const override;
};


#endif //JOHNNYRENDERER2_GEOMPRIMITIVE_H
