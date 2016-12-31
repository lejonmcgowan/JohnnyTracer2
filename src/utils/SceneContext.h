//
// Created by lejonmcgowan on 8/1/16.
//

#ifndef JOHNNYRENDERER2_SCENECONTEXT_H
#define JOHNNYRENDERER2_SCENECONTEXT_H

#include <string>
/**
 * "Global" setting of various parameters and metadata the entire ray-tracer may need to know. Placed here for
 * simplicity in
 * lieu of having half the implementation pass around these universal parameters
 */
struct SceneContext
{
    int width, height;
    std::string outputFilePath;
    std::string sceneFilePath;
};
#endif //JOHNNYRENDERER2_SCENECONTEXT_H
