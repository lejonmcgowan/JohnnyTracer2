//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_POVPARSER_H
#define JOHNNYRENDERER2_POVPARSER_H


#include "SceneFileParser.h"

class POVParser: public SceneFileParser
{
public:
    virtual std::vector<SceneElem> getElems(std::istream& stream) override;
};


#endif //JOHNNYRENDERER2_POVPARSER_H
