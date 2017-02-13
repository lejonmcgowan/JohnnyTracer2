//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_AREALIGHT_H
#define JOHNNYRENDERER2_AREALIGHT_H

#include <core/base/ILight.h>
#include <geometry/Interaction.h>

class AreaLight: public ILight
{
public:
    AreaLight(Transform lightToWorld, int numSamples);

    Color power() override;

    Color sample_li(const Interaction &interation, const Point2D point, Vec3 *wi, float *pdf,
                    VisibilityTest *visibilityTest) override;

};

#endif //JOHNNYRENDERER2_AREALIGHT_H
