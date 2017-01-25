//
// Created by lejonmcgowan on 11/26/16.
//

#ifndef JOHNNYRENDERER2_PERSPECTIVECAMERA_H
#define JOHNNYRENDERER2_PERSPECTIVECAMERA_H


#include "ProjectionCamera.h"
class PerspectiveCamera: public ProjectionCamera
{
public:
    PerspectiveCamera(Transform transform,
                      const Film& film,
                      Transform projection,
                      Vec4 screenWindow);

    float generateRayDifferentials(const CameraSample &sample, Ray *ray) const override;

    PerspectiveCamera(const Transform &cameraToWorld, const Film &film, const Transform &cameraToScreen,
                      Vec4 screenWindow);

    float generateRay(const CameraSample &sample, Ray *ray) const override;

private:
    Vec3 dxCamera, dyCamera;
    Transform persprctive(float fov, float n, float f);

};


#endif //JOHNNYRENDERER2_PERSPECTIVECAMERA_H
