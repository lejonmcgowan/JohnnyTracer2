//
// Created by lejonmcgowan on 8/2/16.
//

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

Transform::Transform():
        trans(mat4(1.0)),
        invTrans(mat4(1.0))
{

}

Transform::Transform(Mat4 transform):
trans(transform)
{
    invTrans = inverse(trans);
}

Transform::Transform(Mat4 transform, Mat4 inverse):
trans(transform),
invTrans(inverse)
{

}

void Transform::translateBy(Vec3 translation)
{
    trans = translate(trans,translation);
    invTrans = translate(invTrans,-translation);
}

void Transform::translateTo(Vec3 translation)
{
    trans[3][0] = 0.0;
    trans[3][1] = 0.0;
    trans[3][2] = 0.0;

    invTrans[3][0] = 0.0;
    invTrans[3][1] = 0.0;
    invTrans[3][2] = 0.0;
    translateBy(translation);
}

void Transform::rotateBy(Vec3 rotation)
{
    trans = rotate(trans,rotation.x,Vec3(1.0,0.0,0.0));
    trans = rotate(trans,rotation.y,Vec3(0.0,1.0,0.0));
    trans = rotate(trans,rotation.z,Vec3(0.0,0.0,1.0));

    //trans should be orthogonal, therefore this should work
    invTrans = transpose(trans);
}

void Transform::rotateTo(Vec3 rotation)
{
    //we need the original scale and translation
    Vec3 s,t,sk;
    Vec4 pro;
    glm::quat r;
    decompose(trans,s,r,t,sk,pro);

    //now make new matrix sans scale and re-rotate
    trans = Mat4(1.0f);
    trans *= Vec4(1.0f);
    rotateBy(rotation);
    //and scale it back properly
    scaleBy(s);
}

void Transform::scaleBy(Vec3 scaling)
{
    trans = scale(trans,scaling);
    invTrans = scale(trans,-scaling);
}

void Transform::scaleBy(Number scaling)
{
    trans = scale(trans,Vec3(scaling,scaling,scaling));
    invTrans = scale(trans,Vec3(-scaling,-scaling,-scaling));
}

void Transform::scaleTo(Vec3 scaling)
{
    //we need the original rotation and translation
    Vec3 s,t,sk;
    Vec4 pro;
    glm::quat r;
    decompose(trans,s,r,t,sk,pro);

    //now make new matrix and apply the transformations
    trans = Mat4(1.0f);
    trans *= Vec4(1.0f);
    trans *= mat4_cast(r);
    scaleBy(scaling);
}

bool Transform::isLeftHanded()
{

    return determinant(Mat3(trans)) < 0;
}

Mat4 Transform::getTransMatrix() const
{
    return trans;
}
Mat4 Transform::getInverseMatrix() const
{
    return invTrans;
}
