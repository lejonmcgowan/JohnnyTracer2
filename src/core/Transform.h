//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_TRANSFORM_H
#define JOHNNYRENDERER2_TRANSFORM_H


#include <geometry/Ray.h>
#include "utils/UnitUtils.h"
#include <iostream>

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
    Transform(Mat4 transform, Mat4 inverse, bool fatal = true);

    void translateBy(Vec3 translation);
    void translateTo(Vec3 translation);

    void rotateBy(Vec3 rotation, bool degrees = true);
    void rotateTo(Vec3 rotation, bool degrees = true);

    void scaleBy(Vec3 scale);
    void scaleBy(Number scaling);
    void scaleTo(Vec3 scale);

    /**
     * used for compositng transformations
     * @param otherTransform  the transform to transform by, note that *this* transformation is done treated as the lhs
     * in this case
     * @return this Transform, composited with the parameter
     */
    Transform& operator*=(const Transform otherTransform)
    {
        trans *= otherTransform.trans;
        invTrans *= otherTransform.invTrans;

        return *this;
    }

    void reset();

    bool isLeftHanded();

    Mat4 getTransMatrix() const;
    Mat4 getInverseMatrix() const;

    inline Ray transformRay(const Ray ray, bool inverseTrans = false) const
    {
        return Ray(transformPoint(ray.origin, inverseTrans),
                     transformVec3(ray.direction, inverseTrans),ray.tMax);
    }

    inline Point transformPoint(const Point point, bool inverseTrans = false) const
    {
        Vec4 point4(point.x,point.y,point.z,1);
        Mat4 transform = inverseTrans ? invTrans : trans;
        Vec4 finalPoint = transform * point4;
        return Point(finalPoint.x,finalPoint.y,finalPoint.z);
    }

    inline Vec3 transformVec3(const Vec3 vec, bool inverseTrans = false) const
    {
        Vec4 tempVec4(vec.x,vec.y,vec.z,0);
        Mat4 transform = inverseTrans ? invTrans : trans;
        Vec4 finalVec = transform * tempVec4;
        return Vec3(finalVec.x,finalVec.y,finalVec.z);
    }

    friend Transform operator*(const Transform,const Transform);
    friend bool operator==(const Transform lhs, const Transform rhs);
    friend bool operator!=(const Transform lhs, const Transform rhs);
    friend std::ostream& operator<<(std::ostream& os,const Transform transform);
};


/**
 * for compositing two separate transformations
 * @param lhs the left part of the composition
 * @param rhs the right part of the composition
 * @return the composition of the two transforms.
 */
Transform operator*(const Transform lhs,const Transform rhs);

bool operator==(const Transform lhs, const Transform rhs);

bool operator!=(const Transform lhs, const Transform rhs);
std::ostream& operator<<(std::ostream& os,const Transform transform);



Transform makeTranslationTransform(Vec3 translate);

Transform makeScaleTransform(Vec3 scale);

Transform makeScaleTransform(Number scale);
/**
 *
 * @param rotationAngles the angles to rotate by. the 3 componenets are in the order of (yaw,pitch,roll)
 * @param degrees if the angles given are in degrees. conversion to radians will be performed if true
 * @return a rotation matrix, based on the yaw-pitch-roll order (naturally, the transformations will be perform in reverse in
 * implementation).
 */
Transform makeRotationTransform(Vec3 rotationAngles, bool degrees = true);

#endif //JOHNNYRENDERER2_TRANSFORM_H
