//
// Created by lejonmcgowan on 11/26/16.
//

#ifndef JOHNNYRENDERER2_PROJECTIONCAMERA_H
#define JOHNNYRENDERER2_PROJECTIONCAMERA_H


#include <core/base/ICamera.h>
class ProjectionCamera: public ICamera
{
protected:
    Transform proj; //camera to screen
    Transform screenToRaster;
public:
    ProjectionCamera(
        const Transform& transform,
        const Film& film,
        const Transform& projection,
        Vec4 screenWindow);

};


#endif //JOHNNYRENDERER2_PROJECTIONCAMERA_H
