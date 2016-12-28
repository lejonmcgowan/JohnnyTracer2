//
// Created by lejonmcgowan on 10/21/16.
//

#ifndef JOHNNYRENDERER2_SCENEFILEPARSER_H
#define JOHNNYRENDERER2_SCENEFILEPARSER_H


#include <vector>
#include <istream>
#include <string>
#include "scene/SceneElem.h"

class SceneFileParser
{
protected:
    std::vector<SceneElem> objects;
    virtual void parseTokens(std::vector<std::string> tokens) = 0;
    virtual std::vector<std::string> tokenize(std::istream& stream) = 0;

public:
    std::vector<SceneElem> getElems(std::istream& stream) final;
};



#endif //JOHNNYRENDERER2_SCENEFILEPARSER_H
