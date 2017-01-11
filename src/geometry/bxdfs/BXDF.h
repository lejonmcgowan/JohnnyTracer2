//
// Created by lejonmcgowan on 1/5/17.
//

#ifndef JOHNNYRENDERER2_BXDF_H
#define JOHNNYRENDERER2_BXDF_H
#include <core/utils/UnitUtils.h>
class BXDF
{
public:
    enum BXDFType
    {
        REFLECTION =   1 << 0,
        TRANSMISSION = 1 << 1,
        DIFFUSE =      1 << 2,
        SPECULAR =     1 << 3,
        GLOSSY =       1 << 4,
        ALL = REFLECTION | TRANSMISSION | DIFFUSE | SPECULAR | GLOSSY,
    };
    BXDFType type;
    BXDF(BXDFType type) : type(type) {}
    bool isType(BXDFType otherType){return (type & otherType) == type;}
    virtual Color f(const Vec3& wo, const Vec3& wi) = 0;
    //implemented in the Monte Carlo Chapter, when explaining nonspecular reflections
    virtual Color sample_f(const Vec3& wo, Vec3& wi, const Point2D& sample,
                           Number* pdf, BXDFType* sampleTye = nullptr){return Color();}
    //will properly implement when doinf Monte Carlo Integrator
    virtual Color rho(const Vec3& wo, int numSamples, const Point2D& samplePoint){return Color();}
};
#endif //JOHNNYRENDERER2_BXDF_H
