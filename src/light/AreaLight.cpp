//
// Created by lejonmcgowan on 8/2/16.
//

#include <geometry/Interaction.h>
#include <core/utils/UnitUtils.h>
#include "AreaLight.h"

AreaLight::AreaLight(Transform lightToWorld, int numSamples) : ILight(lightToWorld, numSamples)
{

}

Color AreaLight::power()
{
    return Color();
}

Color AreaLight::sample_li(const Interaction &interation, const Point2D point, Vec3 *wi, float *pdf,
                           ILight::VisibilityTest *visibilityTest)
{
    return Color();
}
