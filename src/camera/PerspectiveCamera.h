//
// Created by lejonmcgowan on 11/26/16.
//

#ifndef JOHNNYRENDERER2_PERSPECTIVECAMERA_H
#define JOHNNYRENDERER2_PERSPECTIVECAMERA_H


#include "ProjectionCamera.h"
class PerspectiveCamera: public ProjectionCamera
{
public:
    PerspectiveCamera(const Transform& transform,
                      const IFilm& film,
                      const Transform& projection,
                      const Vec4& screenWindow);

};


#endif //JOHNNYRENDERER2_PERSPECTIVECAMERA_H
