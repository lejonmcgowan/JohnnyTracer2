//
// Created by lejonmcgowan on 3/26/17.
//

#ifndef JOHNNYRENDERER2_TESTTRANSFORM_H
#define JOHNNYRENDERER2_TESTTRANSFORM_H
#include "common/printHelper.h"
#include "common/catch.hpp"
#include "common/veccompare.h"

#include <core/Transform.h>

void testApproxTransform(Transform a, Transform b, Number marginOfError = 1e-4)
{
    testApproxMat(a.getTransMatrix(),b.getTransMatrix(),marginOfError);
    testApproxMat(a.getInverseMatrix(),b.getInverseMatrix(),marginOfError);
}

TEST_CASE("test transforms for validity", "[transform]")
{
    Transform transform;
    SECTION("Make sure default construction makes an identity matrix")
    {
        REQUIRE(transform.getTransMatrix() == transform.getInverseMatrix());
        REQUIRE_FALSE(transform.isLeftHanded());
        Mat4 trans = transform.getTransMatrix();
        Mat4 inv = transform.getInverseMatrix();
        //check that the default elements are indeed componenets to an identity matrix
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                REQUIRE(trans[i][j] == (i == j ? 1 : 0));
                REQUIRE(inv[i][j] == (i == j ? 1 : 0));
            }
        }
    }
    SECTION("Test the scaling of matrices")
    {
        transform.scaleTo(Vec3(1.5,1.5,1.5));
        Vec3 trans,inv;

        trans = Vec3(transform.getTransMatrix()[0][0],transform.getTransMatrix()[1][1],transform.getTransMatrix()[2][2]);
        inv = Vec3(transform.getInverseMatrix()[0][0],transform.getInverseMatrix()[1][1],transform.getInverseMatrix()[2][2]);

        Number invScale = 1 / 1.5f;

        testApproxVec(Vec3(1.5,1.5,1.5),trans);
        testApproxVec(Vec3(invScale,invScale,invScale),inv);

        transform.scaleBy(2);

        trans = Vec3(transform.getTransMatrix()[0][0],transform.getTransMatrix()[1][1],transform.getTransMatrix()[2][2]);
        inv = Vec3(transform.getInverseMatrix()[0][0],transform.getInverseMatrix()[1][1],transform.getInverseMatrix()[2][2]);

        invScale = 1 / 3.0f;
        testApproxVec(Vec3(3,3,3),trans);
        testApproxVec(Vec3(invScale,invScale,invScale), inv);

        transform.scaleBy(Vec3(2,1 / 3.0f,1));

        trans = Vec3(transform.getTransMatrix()[0][0],transform.getTransMatrix()[1][1],transform.getTransMatrix()[2][2]);
        inv = Vec3(transform.getInverseMatrix()[0][0],transform.getInverseMatrix()[1][1],transform.getInverseMatrix()[2][2]);

        testApproxVec(Vec3(6,1,3),trans);
        testApproxVec(Vec3(1 / 6.0f,1, 1 / 3.0f),inv);

        transform = makeScaleTransform(Number(1.5));

        trans = Vec3(transform.getTransMatrix()[0][0],transform.getTransMatrix()[1][1],transform.getTransMatrix()[2][2]);
        inv = Vec3(transform.getInverseMatrix()[0][0],transform.getInverseMatrix()[1][1],transform.getInverseMatrix()[2][2]);

        invScale = 1 / 1.5f;

        testApproxVec(Vec3(1.5,1.5,1.5),trans);
        testApproxVec(Vec3(invScale,invScale,invScale),inv);

        transform = makeScaleTransform(Vec3(-1.5,1,0.3));

        trans = Vec3(transform.getTransMatrix()[0][0],transform.getTransMatrix()[1][1],transform.getTransMatrix()[2][2]);
        inv = Vec3(transform.getInverseMatrix()[0][0],transform.getInverseMatrix()[1][1],transform.getInverseMatrix()[2][2]);

        testApproxVec(Vec3(-1.5,1,0.3),trans);
        testApproxVec(Vec3(-2 / 3.0,1,10 / 3.0),inv);
    }

    SECTION("test translation of the transforms")
    {
        Transform transform;
        transform.translateTo(Vec3(1.5,1.5,1.5));
        Vec3 trans,inv;

        trans = Vec3(transform.getTransMatrix()[3][0],transform.getTransMatrix()[3][1],transform.getTransMatrix()[3][2]);
        inv = Vec3(transform.getInverseMatrix()[3][0],transform.getInverseMatrix()[3][1],transform.getInverseMatrix()[3][2]);

        testApproxVec(Vec3(1.5,1.5,1.5),trans);
        testApproxVec(Vec3(-1.5,-1.5,-1.5),inv);

        transform.translateBy(Vec3(0,1,-2));

        trans = Vec3(transform.getTransMatrix()[3][0],transform.getTransMatrix()[3][1],transform.getTransMatrix()[3][2]);
        inv = Vec3(transform.getInverseMatrix()[3][0],transform.getInverseMatrix()[3][1],transform.getInverseMatrix()[3][2]);

        testApproxVec(Vec3(1.5,2.5,-0.5),trans);
        testApproxVec(Vec3(-1.5,-2.5,0.5), inv);

        transform.translateTo(Vec3(-2,-2,-2));

        trans = Vec3(transform.getTransMatrix()[3][0],transform.getTransMatrix()[3][1],transform.getTransMatrix()[3][2]);
        inv = Vec3(transform.getInverseMatrix()[3][0],transform.getInverseMatrix()[3][1],transform.getInverseMatrix()[3][2]);

        testApproxVec(Vec3(-2,-2,-2),trans);
        testApproxVec(Vec3(2,2,2),inv);

        transform = makeTranslationTransform(Vec3(1.5,1.5,1.5));

        trans = Vec3(transform.getTransMatrix()[3][0],transform.getTransMatrix()[3][1],transform.getTransMatrix()[3][2]);
        inv = Vec3(transform.getInverseMatrix()[3][0],transform.getInverseMatrix()[3][1],transform.getInverseMatrix()[3][2]);

        testApproxVec(Vec3(1.5,1.5,1.5),trans);
        testApproxVec(Vec3(-1.5,-1.5,-1.5),inv);
    }

    SECTION("Test rotation of transform")
    {
        Transform rotTest = makeRotationTransform(Vec3(0,0,0));
        testApproxTransform(rotTest,Transform());

        Transform transform;
        transform.rotateBy(Vec3(20,10,1));

        testApproxTransform(transform,makeRotationTransform(Vec3(20,10,1)));
        testApproxTransform(makeRotationTransform(Vec3(0,60,90)),makeRotationTransform(Vec3(0,NumberPI / 3.0,NumberPI / 2.0),false));
    }
}



#endif //JOHNNYRENDERER2_TESTTRANSFORM_H
