//
// Created by lejonmcgowan on 11/26/16.
//

#include "PerspectiveCamera.h"
PerspectiveCamera::PerspectiveCamera(const Transform& transform,
                                     const IFilm& film,
                                     const Transform& projection,
                                     const Vec4& screenWindow)
    : ProjectionCamera(transform, film, projection, screenWindow) {}
