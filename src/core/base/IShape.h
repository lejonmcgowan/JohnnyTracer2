//
// Created by lejonmcgowan on 9/4/16.
//

#ifndef JOHNNYRENDERER2_ISHAPE_H
#define JOHNNYRENDERER2_ISHAPE_H


#include <core/Transform.h>
#include <core/BBox.h>
#include <geometry/Ray.h>
#include <memory>
#include <geometry/SurfaceInteraction.h>

class IShape {
public:
    struct HitPacket
    {
        Number tHit;
        SurfaceInteraction hitData;
        bool testAlphaTexture = true;
        bool successfulHit;
        HitPacket(Number tHit):
                tHit(tHit){}

    };
protected:
    //possible optimization: make a transform pool and draw from that via a pointer
    Transform worldtransform;
    bool leftHanded;
    BBox boundingBox;
public:
    IShape(Transform transform): worldtransform(transform),leftHanded(worldtransform.isLeftHanded()){}
    virtual BBox getObjectBounds() = 0;
    virtual BBox getWorldBounds();
    virtual Number surfaceArea() const = 0;
    /**
     * basic implementation of a "test hit" that uses the intersect implementation.
     * should be overriden for a faster implementation
     * @param ray the ray to test the intersection with
     * @param testAlphaTexture test on a stencil to determine if certain parts of the surface is "hittable"
     * @return whether or note the ray hit
     */
    virtual bool intersectQuick(const Ray& ray, bool testAlphaTexture = true);
    virtual bool intersect(const Ray& ray, HitPacket& results) = 0;
};


#endif //JOHNNYRENDERER2_ISHAPE_H
