//
// Created by lejonmcgowan on 9/4/16.
//

#include <geometry/Interaction.h>
#include "ILight.h"
#include <scene/Scene.h>

ILight::ILight(Transform lightToWorld, int numSamples) : lightToWorld(lightToWorld),
                                                         numSamples(numSamples)
{

}

ILight::VisibilityTest::VisibilityTest(const Interaction &p0, const Interaction &p1) : p0(p0), p1(p1)
{}

const Interaction &ILight::VisibilityTest::getP0() const
{
    return p0;
}

const Interaction &ILight::VisibilityTest::getP1() const
{
    return p1;
}

bool ILight::VisibilityTest::isUnoccluded(const Scene &scene)
{
    return scene.intersectQuick(p0.spawnRayTo(p1));
}
