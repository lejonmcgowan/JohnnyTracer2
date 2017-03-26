//
// Created by lejonmcgowan on 11/24/16.
//

#include <geometry/Interaction.h>
#include <glm/gtx/norm.hpp>

#include "PointLight.h"

PointLight::PointLight(Transform transform, Color color, int numSamples):ILight(transform,numSamples),
                                                                         color(color),
                                                                         position(transform.transformPoint(Point(0,0,0)))
{

}

Color PointLight::power()
{
    Number factor = 4 * NumberPI;
    return color * factor;
}

Color PointLight::sample_li(const Interaction &interation, const Point2D point, Vec3 *wi, float *pdf,
                            ILight::VisibilityTest *visibilityTest)
{
    *wi = glm::normalize(position - interation.hitPoint);
    *pdf = 1;
    *visibilityTest = VisibilityTest(interation,Interaction(position));
    Number interactionDistance = glm::length2(interation.hitPoint - position);
    return color / interactionDistance;
}
