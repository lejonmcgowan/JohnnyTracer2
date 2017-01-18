//
// Created by lejonmcgowan on 11/26/16.
//

#include "ProjectionCamera.h"

/**
 *
 * @param cameraToWorld transform from world to camera space (view matrix)
 * @param film the film to write to
 * @param cameraToScreen the transform from camera to screen (projection matrix)
 * @param screenWindow 2d window coordinates for the viewport to write to. is formatted (xmin,ymin,xmax,ymax)
 */
ProjectionCamera::ProjectionCamera(
                                   const Transform& cameraToWorld,
                                   const Film& film,
                                   const Transform& cameraToScreen,
                                   Vec4 screenWindow)
    : ICamera(cameraToWorld,film),cameraToScreen(cameraToScreen),
      screenWindow(screenWindow)
{
    rasterToCamera = Transform(cameraToScreen.getInverseMatrix() * screenToRaster.getInverseMatrix());
    //now for scaleToRaster. note that these are in reverse order from the explained process becasue matrices.
    //scale by the window resolution
    screenToRaster.scaleBy(Vec3(film.res,1));
    //then inversely scale by the screenwindow coordinate. Be sure to flip Y
    screenToRaster.scaleBy(Vec3(1 / (screenWindow.z - screenWindow.x),
                                1 / (screenWindow.y - screenWindow.w),
                                1));
    //then move by half the viewport, such that the origin is in the upper left corner
    screenToRaster.translateBy(Vec3(-screenWindow.x,-screenWindow.w,0));
}

float ProjectionCamera::generateRay(const ICamera::CameraSample& sample, Ray *ray) const
{
    return 1;
}
