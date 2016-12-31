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

};


#endif //JOHNNYRENDERER2_PERSPECTIVECAMERA_H
