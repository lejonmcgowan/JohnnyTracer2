//
// Created by lejonmcgowan on 12/28/16.
//

#ifndef JOHNNYRENDERER2_SCENEELEMPARSER_H
#define JOHNNYRENDERER2_SCENEELEMPARSER_H


#include <core/base/ILight.h>
#include <core/base/ICamera.h>
#include <scene/SceneElem.h>
#include <core/base/IShape.h>
#include <scene/Scene.h>

class SceneCreator;
class SceneElemParser
{
public:
    virtual std::shared_ptr<ICamera> parseCamera(SceneElem elem) = 0;
    virtual std::shared_ptr<ILight> parseLight(SceneElem elem) = 0;
    virtual std::shared_ptr<IShape> parseShape(SceneElem elem) = 0;
    virtual void parseCustom(SceneElem elem, SceneCreator& sceneCreator){};
};


#endif //JOHNNYRENDERER2_SCENEELEMPARSER_H
