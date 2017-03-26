//
// Created by lejonmcgowan on 3/26/17.
//

#ifndef JOHNNYRENDERER2_TESTTRANSFORM_H
#define JOHNNYRENDERER2_TESTTRANSFORM_H
#include <gtest/gtest.h>
#include <core/Transform.h>

TEST(TransformTest, constructor)
{
    Transform transform;
    EXPECT_EQ(transform.getTransMatrix(),transform.getInverseMatrix());
    EXPECT_FALSE(transform.isLeftHanded());
    Mat4 trans = transform.getTransMatrix();
    Mat4 inv = transform.getInverseMatrix();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            trans[i][j] == i == j ? 1 : 0;
            inv[i][j] == i == j ? 1 : 0;
        }
    }
}
#endif //JOHNNYRENDERER2_TESTTRANSFORM_H
