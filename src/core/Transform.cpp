//
// Created by lejonmcgowan on 8/2/16.
//

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

/**
 * note: try to use the x-by functions whenever possible. the to methods do an relatively inefficient decomposition in order
 * to meet properly transform (the 'simplest' way, but there is probably a more efficient way to do this)
 *
 * Transformation are expected to be done in the order of scaleBy,rotateBy, and then translateBy, so try to create transformations in this order for 'intuitive results'
 */


Transform::Transform() :
        trans(mat4(1.0)),
        invTrans(mat4(1.0))
{

}

Transform::Transform(Mat4 transform) :
        trans(transform)
{
    invTrans = inverse(trans);
}

/**
 * for if you want to give a more efficiently computer inverse. By default, the class will assert and exit if an invalid
 * inverse was given. use carefully
 * @param transform the transform
 * @param inverse the precomputed
 */
Transform::Transform(Mat4 transform, Mat4 inverse, bool fatal) :
        trans(transform),
        invTrans(inverse)
{
    Mat4 verify = transform * inverse;
    if (verify != Mat4() && fatal)
        std::runtime_error("Improper inverse given");
}

void Transform::translateBy(Vec3 translation)
{
    trans = translate(trans, translation);
    invTrans = translate(invTrans, -translation);
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

void Transform::rotateBy(Vec3 rotation, bool degrees)
{
    if (degrees)
        rotation = glm::radians(rotation);

    trans = rotate(trans, rotation.z, Vec3(0.0, 0.0, 1.0));
    trans = rotate(trans, rotation.y, Vec3(0.0, 1.0, 0.0));
    trans = rotate(trans, rotation.x, Vec3(1.0, 0.0, 0.0));

    //invert by using negative rotations (plz)
    invTrans = rotate(invTrans, -rotation.z, Vec3(0.0, 0.0, 1.0));
    invTrans = rotate(invTrans, -rotation.y, Vec3(0.0, 1.0, 0.0));
    invTrans = rotate(invTrans, -rotation.x, Vec3(1.0, 0.0, 0.0));

}

void Transform::rotateTo(Vec3 rotation, bool degrees)
{
    if (degrees)
        rotation = glm::radians(rotation);

    //we need the original scale and translation
    Vec3 s, t, sk;
    Vec4 pro;
    glm::quat r;
    decompose(trans, s, r, t, sk, pro);

    //now make new matrix sans scale and re-rotate
    trans = Mat4(1.0f);
    trans *= Vec4(1.0f);
    rotateBy(rotation);
    //and scale it back properly
    scaleBy(s);
}

/**
 * scales are assumed to start at 1. These scales are multiplicative. i.e. scaling [2,2,2] by 2 will result in [4,4,4]
 * for the diagonal
 *
 * @param scaling
 */
void Transform::scaleBy(Vec3 scaling)
{
    trans = scale(trans, scaling);
    invTrans = scale(invTrans, Vec3(1 / scaling.x, 1 / scaling.y, 1 / scaling.z));
}

void Transform::scaleBy(Number scaling)
{
    Number invScale = 1 / scaling;

    trans = scale(trans, Vec3(scaling, scaling, scaling));
    invTrans = scale(invTrans, Vec3(invScale, invScale, invScale));
}


void Transform::scaleTo(Vec3 scaling)
{
    //we need the original rotation and translation
    Vec3 s, t, sk;
    Vec4 pro;
    glm::quat r;
    decompose(trans, s, r, t, sk, pro);

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

void Transform::reset()
{
    trans = Mat4();
    invTrans = Mat4();
}

Transform operator*(const Transform lhs, const Transform rhs)
{
    return Transform(lhs.trans * rhs.trans,lhs.invTrans * rhs.invTrans);
}

Transform RotateX(Number theta)
{
    Number sinTheta = std::sin(theta);
    Number cosTheta = std::cos(theta);
    Mat4 m(1, 0, 0, 0,
           0, cosTheta, -sinTheta, 0,
           0, sinTheta, cosTheta, 0,
                0, 0, 0, 1);
    return Transform(m, glm::transpose(m));
}

Transform RotateY(Number theta)
{
    Number sinTheta = std::sin(theta);
    Number cosTheta = std::cos(theta);
    Mat4 m(cosTheta, 0, sinTheta, 0,
           0, 1, 0, 0,
           -sinTheta, 0, cosTheta, 0,
           0, 0, 0, 1);
    return Transform(m, glm::transpose(m));
}

Transform RotateZ(Number theta)
{
    Number sinTheta = std::sin(theta);
    Number cosTheta = std::cos(theta);
    Mat4 m(cosTheta, -sinTheta, 0, 0, sinTheta, cosTheta, 0, 0, 0, 0, 1, 0,
                0, 0, 0, 1);
    return Transform(m, glm::transpose(m));
}

Transform makeRotationTransform(Vec3 rotationAngles, bool degrees)
{
    if(degrees)
        rotationAngles = glm::radians(rotationAngles);

    return RotateZ(rotationAngles.z) * RotateY(rotationAngles.y) * RotateX(rotationAngles.x);
}

bool operator==(const Transform lhs, const Transform rhs)
{
    return lhs.trans == rhs.trans;
}

bool operator!=(const Transform lhs, const Transform rhs)
{
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &os, const Transform transform)
{
    Mat4 trans = transform.getTransMatrix();
    os << trans[0][0] << " " << trans[0][1] << " " << trans[0][2] << " " << trans[0][3] << std::endl
       << trans[1][0] << " " << trans[1][1] << " " << trans[1][2] << " " << trans[1][3] << std::endl
       << trans[2][0] << " " << trans[2][1] << " " << trans[2][2] << " " << trans[2][3] << std::endl
       << trans[3][0] << " " << trans[3][1] << " " << trans[3][2] << " " << trans[3][3];

    return os;
}

Transform makeTranslationTransform(Vec3 translate)
{
    Mat4 trans;
    Mat4 inv;

    trans[3] = Vec4(translate,1);
    inv[3] = Vec4(-translate,1);

    return Transform(trans,inv);
}

Transform makeScaleTransform(Vec3 scale)
{
    Mat4 trans;
    Mat4 inv;

    trans[0][0] = scale.x;
    trans[1][1] = scale.y;
    trans[2][2] = scale.z;

    inv[0][0] = 1 / scale.x;
    inv[1][1] = 1 / scale.y;
    inv[2][2] = 1 / scale.z;

    return Transform(trans,inv);
}

Transform makeScaleTransform(Number scale)
{
    return makeScaleTransform(Vec3(scale,scale,scale));
}
