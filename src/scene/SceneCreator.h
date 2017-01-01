//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_IPARSER_H
#define JOHNNYRENDERER2_IPARSER_H


#include <string>
#include <memory>

#include <core/ICamera.h>
#include <core/IShape.h>
#include <core/ILight.h>
#include <scene/Scene.h>
#include <fileparser/SceneElemParser.h>
#include <fileparser/SceneFileParser.h>

class SceneCreator {
private:
    std::pair<std::shared_ptr<SceneFileParser>,std::shared_ptr<SceneElemParser>> getParserAndMethod(std::string
                                                                                                    fileName);

public:
    std::vector<std::shared_ptr<IShape>> shapes;
    std::vector<std::shared_ptr<ILight>> lights;
    std::vector<std::shared_ptr<ICamera>> cameras;

    SceneCreator addToScene(std::string fileName);

    SceneCreator addToScene(SceneElem elemData,SceneElemParser& elemParser);

    SceneCreator addToScene(std::vector<SceneElem> elemData,SceneElemParser& elemParser);

    SceneCreator addToScene(ICamera& camera);

    SceneCreator addToScene(IShape& shape);

    SceneCreator addToScene(ILight& light);

    Scene build();
};


#endif //JOHNNYRENDERER2_IPARSER_H
