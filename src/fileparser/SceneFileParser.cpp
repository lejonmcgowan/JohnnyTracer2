//
// Created by lejonmcgowan on 10/21/16.
//

#include "SceneFileParser.h"
std::vector<SceneElem> SceneFileParser::getElems(std::ifstream& stream)
{
    objects.clear();

    const std::vector<std::string> tokens = tokenize(stream);
    parseTokens(tokens);

    return objects;
}
