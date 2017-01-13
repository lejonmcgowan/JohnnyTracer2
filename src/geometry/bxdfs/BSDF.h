//
// Created by lejonmcgowan on 1/5/17.
//

#ifndef JOHNNYRENDERER2_BSDF_H
#define JOHNNYRENDERER2_BSDF_H
#include <core/utils/UnitUtils.h>
#include <algorithm>
#include <core/utils/Constants.h>
#include "../SurfaceInteraction.h"
#include "BXDF.h"
/**
 * class that takes a set of BxDF's. BXDFs are defined in a reflection coordinate system with an othronormal axes
 * between two perpedicular tangent vectors (x,y axes) and the normal (z axis) on a surface
 */
class BSDF
{
public:
    /*
     * convienence math based on this reflection space
     */
    inline static Number cosTheta(const Vec3& w){return w.z;}
    inline static Number cos2Theta(const Vec3& w){return w.z * w.z;}
    //max in case of floating-point error
    inline static Number sin2Theta(const Vec3& w){return std::max(0.0f,1 - cos2Theta(w));}
    inline static Number sinTheta(const Vec3& w){return std::sqrt(sin2Theta(w));}
    inline static Number tan2Theta(const Vec3& w){return sin2Theta(w) / cos2Theta(w);}
    inline static Number tanTheta(const Vec3& w){return sinTheta(w) / cosTheta(w);}
    inline static Number sinPhi(const Vec3& w)
    {
        Number sTheta = sinTheta(w);
        return sTheta == 0 ? 1 : Constants::clamp(w.y / sTheta,-1,1);
    }
    inline static Number cosPhi(const Vec3& w)
    {
        Number sTheta = sinTheta(w);
        return sTheta == 0 ? 1 : Constants::clamp(w.x / sTheta,-1,1);
    }
    inline static Number sin2Phi(const Vec3& w){return sinPhi(w) * sinPhi(w);}
    inline static Number cos2Phi(const Vec3& w){return cosPhi(w) * cosPhi(w);}

    inline static Number cosDPhi(const Vec3& wa, const Vec3& wb)
    {
        return Constants::clamp(wa.x * wb.x + wa.y * wb.y /
        std::sqrt((wa.x * wa.x + wa.y * wa.y) + (wb.x * wb.x + wb.y * wb.y)),-1,1);
    }
private:
    //normal shading and normal geometry
    const Vec3 ns, ng;
    //two tangents for the othronormal bases in the reflection coordinate system. ns is the third.
    const Vec3 s,t;
    static constexpr  int reserveSize = 8;
    std::vector<std::shared_ptr<BXDF>> bxdfs;
public:
    const Number ior;
public:
    BSDF(const SurfaceInteraction& sInter, Number ior = 1);
    Color f(const Vec3& wiWorld, const Vec3& woWorld, BXDF::BXDFType type);
    Color rho(int numSamples, std::vector<const Point2D>& samples1, std::vector<const Point2D>& samples2,
    BXDF::BXDFType type = BXDF::BXDFType::ALL);
    Color rho(const Vec3& wo, int numSamples, std::vector<const Point2D>& samples,BXDF::BXDFType type = BXDF::BXDFType::ALL);
    inline Vec3 worldToLocal(const Vec3& v) const;
    inline Vec3 localToWorld(const Vec3& v) const;

    //basic CRUD operations for the vector
    void addBXDF(std::shared_ptr<BXDF> bxdf){bxdfs.push_back(bxdf);}
    long numBXDFs(){return bxdfs.size();}

};
#endif //JOHNNYRENDERER2_BSDF_H
