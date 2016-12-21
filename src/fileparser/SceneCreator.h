//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_IPARSER_H
#define JOHNNYRENDERER2_IPARSER_H


#include <string>
#include <core/ICamera.h>
#include <core/IShape.h>
#include <core/ILight.h>
#include <scene/Scene.h>
#include "SceneFileParser.h"

class SceneCreator {
private:
    SceneFileParser& getParser(std::string fileName);

    std::vector<std::shared_ptr<IShape>> shapes;
    std::vector<std::shared_ptr<ILight>> lights;
    std::vector<std::shared_ptr<ICamera>> cameras;
public:
    SceneCreator addToScene(std::string fileName);

    SceneCreator addToScene(SceneElem elemData);

    SceneCreator addToScene(std::vector<SceneElem> elemData);

    SceneCreator addToScene(ICamera& camera);

    SceneCreator addToScene(IShape& shape);

    SceneCreator addToScene(ILight& light);

    Scene build();
};


#endif //JOHNNYRENDERER2_IPARSER_H
