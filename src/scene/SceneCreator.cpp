//
// Created by lejonmcgowan on 10/5/16.
//

#include <fstream>
#include <fileparser/POVParser.h>
#include <fileparser/POVElemParser.h>
#include <iostream>
#include "SceneCreator.h"

std::pair<std::shared_ptr<SceneFileParser>, std::shared_ptr<SceneElemParser>>
SceneCreator::getParserAndMethod(std::string fileName)
{
    std::shared_ptr<POVParser> povParser = std::make_shared<POVParser>();
    std::shared_ptr<POVElemParser> elemParser = std::make_shared<POVElemParser>();
    return std::pair<std::shared_ptr<SceneFileParser>, std::shared_ptr<SceneElemParser>>(
        povParser,
        elemParser);
}

SceneCreator SceneCreator::addToScene(std::string fileName)
{
    std::ifstream stream;
    stream.open(fileName);

    char nextChar;
    if( stream.is_open() )
    {
        std::cout << "Using std::filebuf : Opened" << std::endl ;
    }
    else
    {
        std::cout << "Using std::filebuf : Not opened" << std::endl ;
        stream.close() ;
    }

    auto parsePair = getParserAndMethod(fileName);

    return addToScene(parsePair.first->getElems(stream), *(parsePair.second));
}

SceneCreator SceneCreator::addToScene(SceneElem elemData, SceneElemParser& elemParser)
{
    switch (elemData.type)
    {
        case SceneElem::SHAPE:
        {
            std::unique_ptr<IShape> shape = elemParser.parseShape(elemData);
            addToScene(*shape);
            break;
        }
        case SceneElem::CAMERA:
        {
            std::unique_ptr<ICamera> camera = elemParser.parseCamera(elemData);
            addToScene(*camera);
            break;
        }
        case SceneElem::LIGHT:
        {
            std::unique_ptr<ILight> light = elemParser.parseLight(elemData);
            addToScene(*light);
            break;
        }
        case SceneElem::CUSTOM:
        {
            elemParser.parseCustom(elemData, *this);
            break;
        }
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

SceneCreator SceneCreator::addToScene(std::vector<SceneElem> elems, SceneElemParser& elemParser)
{
    for (SceneElem& elem: elems)
        addToScene(elem, elemParser);
    return *this;
}


