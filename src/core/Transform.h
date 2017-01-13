//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_TRANSFORM_H
#define JOHNNYRENDERER2_TRANSFORM_H


#include <geometry/Ray.h>
#include "utils/UnitUtils.h"

/**
 * basic implemtation for basic affine transforms, inluding translation, rotation, and scaling.
 * new additions to the transformations undergo the pattern of scale -> rotate -> translate
 * to ensure that the transformation works intuitively to the average users expectations.
 *
 * Transformations and its are stored as a Mat4, and are updated in tandem.
 * */
class Transform
{
private:
    Mat4 trans,invTrans;
public:
    Transform();
    Transform(Mat4 transform);
    Transform(Mat4 transform, Mat4 inverse);

    void translateBy(Vec3 translation);
    void translateTo(Vec3 translation);

    void rotateBy(Vec3 rotation);
    void rotateTo(Vec3 rotation);

    void scaleBy(Vec3 scale);
    void scaleBy(Number scaling);
    void scaleTo(Vec3 scale);

    bool isLeftHanded();

    Mat4 getTransMatrix();
    Mat4 getInverseMatrix();

    inline Ray transformRay(const Ray ray, bool inverseTrans = false)
    {
        return Ray(transformPoint(ray.origin, inverseTrans),
                     transformVec3(ray.direction, inverseTrans),ray.depth,ray.tMax);
    }

    inline Point transformPoint(const Point point, bool inverseTrans = false)
    {
        Vec4 point4(point.x,point.y,point.z,1);
        Mat4 transform = inverseTrans ? invTrans : trans;
        Vec4 finalPoint = transform * point4;
        return Vec3(finalPoint.x,finalPoint.y,finalPoint.z);
    }

    inline Vec3 transformVec3(const Vec3 vec, bool inverseTrans = false)
    {
        Vec4 tempVec4(vec.x,vec.y,vec.z,0);
        Mat4 transform = inverseTrans ? invTrans : trans;
        Vec4 finalVec = transform * tempVec4;
        return Vec3(finalVec.x,finalVec.y,finalVec.z);
    }
};


#endif //JOHNNYRENDERER2_TRANSFORM_H
