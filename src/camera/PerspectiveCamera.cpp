//
// Created by lejonmcgowan on 11/26/16.
//

#include "PerspectiveCamera.h"
PerspectiveCamera::PerspectiveCamera(Transform transform,
                                     const Film& film,
                                     Transform projection,
                                     Vec4 screenWindow)
    : ProjectionCamera(transform, film, projection, screenWindow) {}
