//
// Created by lejonmcgowan on 3/27/17.
//

#ifndef JOHNNYRENDERER2_PRINTHELPER_H
#define JOHNNYRENDERER2_PRINTHELPER_H

#include <iostream>
#include <core/utils/UnitUtils.h>

std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
    os << "(" << v.x << "," << v.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
    os << "(" << v.x << "," << v.y << "," << v.z << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vec4& v)
{
    os << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Mat2& v)
{
    os << v[0][0] << " " << v[0][1] << std::endl
       << v[1][0] << " " << v[1][1];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Mat3& v)
{
    os << v[0][0] << " " << v[0][1] << " " << v[0][2] << std::endl
            << v[1][0] << " " << v[1][1] << " " << v[1][2] << std::endl
            << v[2][0] << " " << v[2][1] << " " << v[2][2];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Mat4& v)
{
    os << v[0][0] << " " << v[0][1] << " " << v[0][2] << " " << v[0][3] << std::endl
            << v[1][0] << " " << v[1][1] << " " << v[1][2] << " " << v[1][3] << std::endl
            << v[2][0] << " " << v[2][1] << " " << v[2][2] << " " << v[2][3] << std::endl
            << v[3][0] << " " << v[3][1] << " " << v[3][2] << " " << v[3][3];
    return os;
}

#endif //JOHNNYRENDERER2_PRINTHELPER_H
