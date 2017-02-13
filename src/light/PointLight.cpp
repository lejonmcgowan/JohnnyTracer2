//
// Created by lejonmcgowan on 11/24/16.
//

#include <geometry/Interaction.h>
#include <core/utils/UnitUtils.h>
#include "PointLight.h"

PointLight::PointLight(Transform transform, Color color, int numSamples):ILight(transform,numSamples), color(color)
{

}

Color PointLight::power()
{
    return Color();
}

Color PointLight::sample_li(const Interaction &interation, const Point2D point, Vec3 *wi, float *pdf,
                            ILight::VisibilityTest *visibilityTest)
{
    return Color();
}
