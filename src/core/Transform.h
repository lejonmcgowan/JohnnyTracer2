//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_TRANSFORM_H
#define JOHNNYRENDERER2_TRANSFORM_H


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
    void scaleTo(Vec3 scale);

    bool isLeftHanded();

    Mat4 getTransMatrix();
    Mat4 getInverseMatrix();
};


#endif //JOHNNYRENDERER2_TRANSFORM_H
