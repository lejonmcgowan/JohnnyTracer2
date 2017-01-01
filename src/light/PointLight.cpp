//
// Created by lejonmcgowan on 11/24/16.
//

#include "PointLight.h"

PointLight::PointLight(Transform transform, Color color, int numSamples):ILight(transform,numSamples), color(color)
{

}
