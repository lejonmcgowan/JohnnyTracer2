//
// Created by lejonmcgowan on 11/24/16.
//

#include "Plane.h"

Plane::Plane(Point point, Vec3 normal, Transform transform) : IShape(transform),
                                                              nor(normal),
                                                              p(point)
{

}
