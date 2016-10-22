//
// Created by lejonmcgowan on 8/1/16.
//

#ifndef JOHNNYRENDERER2_IPRIMITIVE_H
#define JOHNNYRENDERER2_IPRIMITIVE_H
#include <memory>
#include <vector>

#include "light/AreaLight.h"
#include "geometry/Ray.h"
#include "geometry/BBox.h"
#include "geometry/HitData.h"
class IPrimitive
{
private:
    static int idIter;
protected:
    int id;
public:
    IPrimitive(): id(++idIter){}
    virtual BBox getBounds() const = 0;
    virtual bool canIntersect();
    virtual std::shared_ptr<HitData> queryIntersect(const Ray ray);
    virtual bool checkIntersect(const Ray ray);
    /**
     * something to do with ensuring that every geometry in the prinmitive is intersectable. don't fully get it atm
     */
    virtual void refine(std::vector<std::shared_ptr<IPrimitive>> primitives) = 0;
    /**
     *  utility function to refine an entire list for you. calls each primitive's refine() method to do so
     */
    virtual void fullRefine(std::vector<std::shared_ptr<IPrimitive>> primitives);
    /**
     * in case any primitive is a light or can otherwise emit energy from it for illumination
     */
    virtual const std::shared_ptr<AreaLight> getAreaLight() const = 0;
    /**
     * other methods to keep in mind (pg. 187): getBSDF and getBSSRDF for light and surface scattering.
     * outside of the current impl. scope
     */
};
#endif //JOHNNYRENDERER2_IPRIMITIVE_H
