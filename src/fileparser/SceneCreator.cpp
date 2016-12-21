//
// Created by lejonmcgowan on 10/5/16.
//

#include <fstream>
#include "SceneCreator.h"
#include "POVParser.h"

SceneFileParser& SceneCreator::getParser(std::string fileName)
{
    static POVParser povParser;
    return povParser;
}

SceneCreator SceneCreator::addToScene(std::string fileName)
{
    std::filebuf filebuf;
    filebuf.open(fileName, std::ios::in);
    std::istream stream(&filebuf);
    return addToScene(getParser(fileName).getElems(stream));
}

SceneCreator SceneCreator::addToScene(SceneElem elemData)
{
    switch (elemData.elemType)
    {
        case SceneElem::SPHERE:
            break;
        case SceneElem::TRIANGLE:
            break;
        case SceneElem::BOX:
            break;
        case SceneElem::DIR_LIGHT:
            break;
        case SceneElem::POINT_LIGHT:
            break;
        case SceneElem::SPOT_LIGHT:
            break;
        case SceneElem::PIN_CAMERA:
            break;
        case SceneElem::PLANE:
            break;
    }
    return *this;
}

SceneCreator SceneCreator::addToScene(ICamera& camera)
{
    std::shared_ptr<ICamera> cameraPtr;
    cameraPtr.reset(&camera);
    cameras.push_back(cameraPtr);
    return *this;
}

SceneCreator SceneCreator::addToScene(IShape& shape)
{
    std::shared_ptr<IShape> shapePtr;
    shapePtr.reset(&shape);

    shapes.push_back(shapePtr);
    return *this;
}

SceneCreator SceneCreator::addToScene(ILight& light)
{
    std::shared_ptr<ILight> lightPtr;
    lightPtr.reset(&light);
    lights.push_back(lightPtr);
    return *this;
}

Scene SceneCreator::build()
{
    return Scene();
}

SceneCreator SceneCreator::addToScene(std::vector<SceneElem> elemData)
{
    for (SceneElem shape: elemData)
        addToScene(shape);
    return *this;
}

