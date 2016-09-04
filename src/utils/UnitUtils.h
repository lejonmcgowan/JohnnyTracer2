//
// Created by lejonmcgowan on 8/2/16.
//

#ifndef JOHNNYRENDERER2_POINT_H
#define JOHNNYRENDERER2_POINT_H
#include <glm/glm.hpp>
#ifndef DOUBLE_PRECISION
    typedef float Number;
    typedef glm::vec2 Vec2;
    typedef glm::vec3 Vec3;
    typedef glm::vec4 Vec4;
    typedef glm::mat2 Mat2;
    typedef glm::mat3 Mat3;
    typedef glm::mat4 Mat4;
#else
    typedef double Number;
    typedef glm::dvec2 Vec2;
    typedef glm::dvec3 Vec3;
    typedef glm::dvec4 Vec4;
    typedef glm::dmat2 Mat2;
    typedef glm::dmat3 Mat3;
    typedef glm::dmat4 Mat4;
#endif

    typedef Vec3 Point;
    typedef Vec2 Point2D;
    typedef Vec4 Color;
#endif //JOHNNYRENDERER2_POINT_H
