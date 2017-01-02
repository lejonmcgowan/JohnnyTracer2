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
            std::shared_ptr<IShape> shape = elemParser.parseShape(elemData);
            addToScene(std::move(shape));
            break;
        }
        case SceneElem::CAMERA:
        {
            std::shared_ptr<ICamera> camera = elemParser.parseCamera(elemData);
            addToScene(std::move(camera));
            break;
        }
        case SceneElem::LIGHT:
        {
            std::shared_ptr<ILight> light = elemParser.parseLight(elemData);
            addToScene(std::move(light));
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

SceneCreator SceneCreator::addToScene(std::shared_ptr<ICamera> camera)
{
    cameras.push_back(std::move(camera));
    return *this;
}

SceneCreator SceneCreator::addToScene(std::shared_ptr<IShape> shape)
{
    shapes.push_back(std::move(shape));
    return *this;
}

SceneCreator SceneCreator::addToScene(std::shared_ptr<ILight> light)
{
    lights.push_back(std::move(light));
    return *this;
}

Scene SceneCreator::build()
{
    return Scene();
}

SceneCreator SceneCreator::addToScene(std::vector<SceneElem> elems, SceneElemParser& elemParser)
{
    shapes.reserve(elems.size());
    for (SceneElem& elem: elems)
        addToScene(elem, elemParser);
    return *this;
}


