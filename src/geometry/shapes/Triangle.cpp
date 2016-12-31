//
// Created by lejonmcgowan on 11/24/16.
//

#include "Triangle.h"

Triangle::Triangle(Point a, Point b, Point c, Transform transform)
    : IShape(transform),
      a(a),
      b(b),
      c(c)
{

}
BBox Triangle::getObjectBounds()
{
    return BBox();
}
Number Triangle::surfaceArea() const
{
    return 0;
}
bool Triangle::intersect(const Ray& ray, IShape::HitPacket& results)
{
    return false;
}
