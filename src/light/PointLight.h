//
// Created by lejonmcgowan on 11/24/16.
//

#ifndef JOHNNYRENDERER2_POINTLIGHT_H
#define JOHNNYRENDERER2_POINTLIGHT_H


#include <core/base/ILight.h>
#include <geometry/Interaction.h>

class PointLight: public ILight
{
private:
    Color color;
public:
    Color power() override;

    Color sample_li(const Interaction &interation, const Point2D point, Vec3 *wi, float *pdf,
                    VisibilityTest *visibilityTest) override;

public:
    PointLight(Transform transform, Color color, int numSamples = 1);
};


#endif //JOHNNYRENDERER2_POINTLIGHT_H
