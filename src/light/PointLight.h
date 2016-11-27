//
// Created by lejonmcgowan on 11/24/16.
//

#ifndef JOHNNYRENDERER2_POINTLIGHT_H
#define JOHNNYRENDERER2_POINTLIGHT_H


#include <core/ILight.h>

class PointLight: public ILight
{
private:
    Color color;
public:
    PointLight(Transform transform, Color color, int numSamples = 1);
};


#endif //JOHNNYRENDERER2_POINTLIGHT_H
