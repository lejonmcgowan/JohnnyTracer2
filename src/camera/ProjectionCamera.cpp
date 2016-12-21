//
// Created by lejonmcgowan on 11/26/16.
//

#include "ProjectionCamera.h"
ProjectionCamera::ProjectionCamera(
                                   const Transform& transform,
                                   const IFilm& film,
                                   const Transform& projection,
                                   Vec4 screenWindow)
    : ICamera(transform,film)
{

}
