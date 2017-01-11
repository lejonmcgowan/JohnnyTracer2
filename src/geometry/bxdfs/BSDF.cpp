//
// Created by lejonmcgowan on 1/6/17.
//
#include "BSDF.h"

Color BSDF::rho(int numSamples,
                std::vector<const Point2D>& samples1,
                std::vector<const Point2D>& samples2,
                BXDF::BXDFType type)
{
    return Color();
}

BSDF::BSDF(const SurfaceInteraction& sInter, Number ior):
ior(ior),ns(sInter.shading.normal),ng(sInter.normal),s(glm::normalize(sInter.shading.partialNormals.u)),
t(glm::cross(s,ns))
{

}

Color BSDF::f(const Vec3& wiWorld, const Vec3& woWorld, BXDF::BXDFType type)
{
    return Color();
}
Color BSDF::rho(const Vec3& wo, int numSamples, std::vector<const Point2D>& samples, BXDF::BXDFType type)
{
    return Color();
}
Vec3 BSDF::worldToLocal(const Vec3& v) const
{
    return Vec3();
}
Vec3 BSDF::localToWorld(const Vec3& v) const
{
    return Vec3();
}
