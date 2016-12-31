//
// Created by lejonmcgowan on 12/28/16.
//

#ifndef JOHNNYRENDERER2_SCENEELEMPARSER_H
#define JOHNNYRENDERER2_SCENEELEMPARSER_H


#include <core/ILight.h>
#include <core/ICamera.h>
#include <scene/SceneElem.h>
#include <core/IShape.h>
#include <scene/Scene.h>

class SceneCreator;
class SceneElemParser
{
public:
    virtual std::unique_ptr<ICamera> parseCamera(SceneElem elem) = 0;
    virtual std::unique_ptr<ILight> parseLight(SceneElem elem) = 0;
    virtual std::unique_ptr<IShape> parseShape(SceneElem elem) = 0;
    virtual void parseCustom(SceneElem elem, SceneCreator& sceneCreator){};
};


#endif //JOHNNYRENDERER2_SCENEELEMPARSER_H
