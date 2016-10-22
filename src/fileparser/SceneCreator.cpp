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
    return *this;
}

SceneCreator SceneCreator::addToScene(ICamera camera)
{
    cameras.push_back(std::make_shared<ICamera>(camera));
    return *this;
}

SceneCreator SceneCreator::addToScene(IShape shape)
{
    shapes.push_back(std::make_shared<IShape>(shape));
    return *this;
}

SceneCreator SceneCreator::addToScene(ILight light)
{
    lights.push_back(std::make_shared<ILight>(light));
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

