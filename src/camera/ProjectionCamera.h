//
// Created by lejonmcgowan on 11/26/16.
//

#ifndef JOHNNYRENDERER2_PROJECTIONCAMERA_H
#define JOHNNYRENDERER2_PROJECTIONCAMERA_H


#include <core/base/ICamera.h>
class ProjectionCamera: public ICamera
{
protected:
    Vec4 screenWindow;
    Transform cameraToScreen;
    Transform screenToRaster;
    Transform rasterToCamera;
public:
    float generateRayDifferentials(const CameraSample &sample, Ray *ray) const override;

    ProjectionCamera(
        const Transform& cameraToWorld,
        const Film& film,
        const Transform& cameraToScreen,
        Vec4 screenWindow);

    float generateRay(const CameraSample& sample, Ray *ray) const override;

};


#endif //JOHNNYRENDERER2_PROJECTIONCAMERA_H
