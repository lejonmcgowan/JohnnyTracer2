//
// Created by lejonmcgowan on 11/24/16.
//

#include <core/IShape.h>
#include "Box.h"

Box::Box(Vec3 min, Vec3 max, Transform transform): IShape(transform),
                                                   min(min),
                                                   max(max)
{

}
