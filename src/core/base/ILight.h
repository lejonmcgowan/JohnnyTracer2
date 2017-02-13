// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_ILIGHT_H
#define JOHNNYRENDERER2_ILIGHT_H

#include <core/Transform.h>
#include <geometry/Interaction.h>

class Scene;
class ILight
{
public:
    class VisibilityTest
    {
        const Interaction p0,p1;
    public:
        VisibilityTest(const Interaction &p0, const Interaction &p1);
        const Interaction &getP0() const;
        const Interaction &getP1() const;
        bool isUnoccluded(const Scene& scene);
    };
private:
    //make protected later. for more fancy options to be enabled, like delta distributions
    int flags;
public:
    const int numSamples;
protected:
    Transform lightToWorld;

public:
    ILight(Transform lightToWorld, int numSamples = 1);
    virtual Color power() = 0;
    /**
     * sample and return a color at a given point given the interaction
     * @param interation the interaction point of the surface
     * @param point point of interest
     * @param wi incoming point
     * @param pdf time passed in?
     * @param visibilityTest interactino results that this funciton sets
     * @return final color of the sampled point
     */
    virtual Color sample_li(const Interaction& interation, const Point2D point, Vec3* wi,float* pdf, VisibilityTest* visibilityTest) = 0;
};
#endif //JOHNNYRENDERER2_ILIGHT_H
