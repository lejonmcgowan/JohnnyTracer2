//
// Created by lejonmcgowan on 11/24/16.
//

#include "Triangle.h"

Triangle::Triangle(Vec3 points, Transform transform): IShape(transform),
                                                      abc(points)
{

}
