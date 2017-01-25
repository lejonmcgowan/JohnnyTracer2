//
// Created by lejonmcgowan on 11/26/16.
//

#include <glm/gtc/matrix_transform.hpp>
#include "PerspectiveCamera.h"
PerspectiveCamera::PerspectiveCamera(Transform transform,
                                     const Film& film,
                                     Transform projection,
                                     Vec4 screenWindow)
    : ProjectionCamera(transform, film, projection, screenWindow)
{
    dxCamera = rasterToCamera.transformPoint(Vec3(1,0,0)) - rasterToCamera.transformPoint(Vec3(0,0,0));
    dyCamera = rasterToCamera.transformPoint(Vec3(0,1,0)) - rasterToCamera.transformPoint(Vec3(0,0,0));
}

float PerspectiveCamera::generateRayDifferentials(const ICamera::CameraSample &sample, Ray *ray) const
{
    return ProjectionCamera::generateRayDifferentials(sample, ray);
}

PerspectiveCamera::PerspectiveCamera(const Transform &cameraToWorld, const Film &film, const Transform &cameraToScreen,
                                     Vec4 screenWindow) : ProjectionCamera(cameraToWorld, film, cameraToScreen,
                                                                           screenWindow)
{

}

float PerspectiveCamera::generateRay(const ICamera::CameraSample &sample, Ray *ray) const
{

    return ProjectionCamera::generateRay(sample, ray);
}

Transform PerspectiveCamera::persprctive(float fov, float n, float f)
{
    Mat4 projection = glm::perspective(fov,film.res.y / film.res.x,n,f);
    return Transform(projection);
}
