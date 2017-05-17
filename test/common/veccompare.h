//
// Created by lejonmcgowan on 5/17/17.
//

#ifndef JOHNNYRENDERER2_VECCOMPARE_H
#define JOHNNYRENDERER2_VECCOMPARE_H

#include "catch.hpp"
#include <glm/glm.hpp>

void testApproxVec(Vec2 a, Vec2 b, Number marginOfError = 1e-4)
{
    REQUIRE(a.x == Approx(b.x).margin(marginOfError));
    REQUIRE(a.y == Approx(b.y).margin(marginOfError));
}

void testApproxVec(Vec3 a, Vec3 b, Number marginOfError = 1e-4)
{
    REQUIRE(a.x == Approx(b.x).margin(marginOfError));
    REQUIRE(a.y == Approx(b.y).margin(marginOfError));
    REQUIRE(a.z == Approx(b.z).margin(marginOfError));
}

void testApproxVec(Vec4 a, Vec4 b, Number marginOfError = 1e-4)
{
    REQUIRE(a.x == Approx(b.x).margin(marginOfError));
    REQUIRE(a.y == Approx(b.y).margin(marginOfError));
    REQUIRE(a.z == Approx(b.z).margin(marginOfError));
    REQUIRE(a.w == Approx(b.w).margin(marginOfError));
}

void testApproxMat(Mat2 a, Mat2 b, Number marginOfError = 1e-4)
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            REQUIRE(a[i][j] == Approx(b[i][j]).margin(marginOfError));
        }
    }
}

void testApproxMat(Mat3 a, Mat3 b, Number marginOfError = 1e-4)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            REQUIRE(a[i][j] == Approx(b[i][j]).margin(marginOfError));
        }
    }
}

void testApproxMat(Mat4 a, Mat4 b, Number marginOfError = 1e-4)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            REQUIRE(a[i][j] == Approx(b[i][j]).margin(marginOfError));
        }
    }
}

#endif //JOHNNYRENDERER2_VECCOMPARE_H
