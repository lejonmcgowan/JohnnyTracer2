//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_POVPARSER_H
#define JOHNNYRENDERER2_POVPARSER_H


#include "SceneFileParser.h"

class POVParser: public SceneFileParser
{
protected:
    void parseTokens(std::vector<std::string> tokens);
    virtual std::vector<std::string> tokenize(std::istream& stream);
};


#endif //JOHNNYRENDERER2_POVPARSER_H
