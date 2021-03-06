//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_POINT_H
#define JOHNNYRENDERER2_POINT_H
#include <glm/glm.hpp>
#include <limits>
#include <glm/gtc/constants.hpp>

typedef glm::ivec2 IVec2;
typedef glm::ivec3 IVec3;
typedef glm::ivec4 IVec4;

#ifndef DOUBLE_PRECISION
typedef float Number;
const float NumberInfinity = std::numeric_limits<float>::max();
const Number NumberPI = 3.14159265358979323846f;
#else
typedef double Number;
const double NumberInfinity  = std::numeric_limits<double>::max();
const Number NumberPI = 3.14159265358979323846;
#endif



typedef glm::tvec2<Number, glm::highp> Vec2;
typedef glm::tvec3<Number, glm::highp> Vec3;
typedef glm::tvec4<Number, glm::highp> Vec4;

typedef glm::tmat2x2<Number, glm::highp> Mat2;
typedef glm::tmat3x3<Number, glm::highp> Mat3;
typedef glm::tmat4x4<Number, glm::highp> Mat4;

typedef Vec3 Point;

typedef Vec2 Point2D;

typedef Vec4 Color;

inline Number dot(Vec2 a, Vec2 b){return a.x * b.x + a.y * b.y;}
inline Number dot(Vec3 a, Vec3 b){return a.x * b.x + a.y * b.y + a.z * b.z;}
inline Number dot(Vec4 a, Vec4 b){return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;}

#endif //JOHNNYRENDERER2_POINT_H
