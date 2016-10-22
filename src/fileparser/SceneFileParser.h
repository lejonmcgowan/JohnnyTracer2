//
// Created by lejonmcgowan on 10/21/16.
//

#ifndef JOHNNYRENDERER2_SCENEFILEPARSER_H
#define JOHNNYRENDERER2_SCENEFILEPARSER_H


#include <vector>
#include <istream>
#include "scene/SceneElem.h"

class SceneFileParser
{
public:
    virtual std::vector<SceneElem> getElems(std::istream& stream) = 0;
};


#endif //JOHNNYRENDERER2_SCENEFILEPARSER_H
