//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_ISHAPE_H
#define JOHNNYRENDERER2_ISHAPE_H


#include <geometry/Transform.h>
#include <geometry/BBox.h>
#include <geometry/Ray.h>
#include <bits/shared_ptr.h>
#include <geometry/GeomData.h>

class IShape {
public:
    struct HitPacket
    {
        Number tHit;
        Number rayEpsilon;
        GeomData hitData;
        bool successfulHit;
        HitPacket(Number tHit, Number rayEpsilon = 0):
                tHit(tHit),
                rayEpsilon(rayEpsilon){}

    };
protected:
    Transform worldtransform;
    bool leftHanded;
    BBox boundingBox;
public:
    IShape(Transform transform): worldtransform(transform),leftHanded(worldtransform.isLeftHanded()){}
    virtual BBox getObjectBounds() = 0;
    virtual BBox getWorldBounds();
    virtual bool intersectQuick(const Ray& ray);
    virtual bool intersect(const Ray& ray, HitPacket& results);
};


#endif //JOHNNYRENDERER2_ISHAPE_H
