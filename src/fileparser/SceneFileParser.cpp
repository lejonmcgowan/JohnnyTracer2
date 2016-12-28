//
// Created by lejonmcgowan on 10/21/16.
//

#include "SceneFileParser.h"
std::vector<SceneElem> SceneFileParser::getElems(std::istream& stream)
{
    objects.clear();

    parseTokens(tokenize(stream));

    return objects;
}
