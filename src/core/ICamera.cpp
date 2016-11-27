//
// Created by lejonmcgowan on 9/4/16.
//

#include "ICamera.h"

ICamera::ICamera(Transform transform, Vec2 shutterRange, IFilm film):
transform(transform),
shutterRange(shutterRange),
film(film)
{

}
