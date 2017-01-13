//
// Created by lejonmcgowan on 11/23/16.
//

#include "Sphere.h"
#include <core/utils/Constants.h>

Sphere::Sphere(Number radius, Transform transform) : IShape(transform),
                                                     radius(radius)
{

}

BBox Sphere::getObjectBounds()
{
    return BBox(Vec3(-radius, -radius, -radius), Vec3(radius, radius, radius));
}

Number Sphere::surfaceArea() const
{
    return 4 * NumberPI * radius * radius;
}

bool Sphere::intersect(const Ray &ray, IShape::HitPacket &results)
{
    Ray localRay = worldtransform.transformRay(ray, true);
    Number a, b, c;

    //calculate a,b,c
    //HACK: CLion's IDE isn't quite good with some glm template stuff atm. ignore this squiggly
    a = glm::dot(localRay.direction, localRay.direction);
    b = 2 * glm::dot(ray.origin, ray.direction);
    c = glm::dot(ray.origin, ray.origin) - radius * radius;

    //check near quadric. 
    Number determinant = std::sqrt(b * b - 4 * a * c);
    Number tNear = b - determinant;
    Number tFar = b + determinant;
    bool near = tNear > -.001f && tNear < ray.tMax;
    bool far = tFar > -.001f && tFar < ray.tMax;
    if (near || far)
    {
        Number tFinal = near ? tNear : tFar;
        results.tHit = tFinal;
        const Point contactPoint = ray.calcPoint(tNear);
        results.hitData.hitPoint = contactPoint;
        results.hitData.normal = results.hitData.hitPoint;
        results.successfulHit = true;
        //now for uvs and partials
        Number phi = std::atan2(contactPoint.y,contactPoint.x);
        Number theta = std::acos(Constants::clamp(contactPoint.z / radius,-1,1));

        if(phi < 0)
            phi += 2 * NumberPI;
        //todo VERIFY: a full circle in sphereical coordinates is (r,2*pi,2*pi), right?
        Number u = phi / (2 * NumberPI);
        Number v = theta / (2 * NumberPI);
        //todo the partials are annoying. do later
        return true;
    }

    return false;
}

bool Sphere::intersectQuick(const Ray &ray, bool testAlphaTexture)
{
    Ray localRay = worldtransform.transformRay(ray, true);
    Number a, b, c;

    //calculate a,b,c
    //HACK: CLion's IDE isn't quite good with some glm template stuff atm. ignore this squiggly
    a = glm::dot(localRay.direction, localRay.direction);
    b = 2 * glm::dot(ray.origin, ray.direction);
    c = glm::dot(ray.origin, ray.origin) - radius * radius;

    //check near quadric.
    Number determinant = std::sqrt(b * b - 4 * a * c);
    Number tNear = b - determinant;
    Number tFar = b + determinant;
    bool near = tNear > -.001f && tNear < ray.tMax;
    bool far = tFar > -.001f && tFar < ray.tMax;
    return near || far;
}
