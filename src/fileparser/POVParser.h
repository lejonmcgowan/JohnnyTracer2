//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_POVPARSER_H
#define JOHNNYRENDERER2_POVPARSER_H


#include "SceneFileParser.h"

/**
 * File Parser for the partial implemetation of the POV-Ray format. The idea in this implementation is to
 * iterate through the top-level objects and delegate the adding of SceneElems to the proper function, leaving the respo
 * nsibility of changing the iterator of the list to these functions.
 */
class POVParser: public SceneFileParser
{
protected:
    void parseTokens(const std::vector<std::string>& tokens);
    virtual std::vector<std::string> tokenize(std::ifstream& stream);
};


#endif //JOHNNYRENDERER2_POVPARSER_H
