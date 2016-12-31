//
// Created by lejonmcgowan on 10/21/16.
//

#ifndef JOHNNYRENDERER2_SCENEFILEPARSER_H
#define JOHNNYRENDERER2_SCENEFILEPARSER_H


#include <vector>
#include <istream>
#include <string>
#include "scene/SceneElem.h"

/**
 * absrtact class responsible for converting a file format into a series of SceneElems
 * to be used for creating the Scene later. Implementaions override two methods, explained below
 */
class SceneFileParser
{
protected:
    /**
     * the class-level object that implemetations use to add to the middle-layer scene. these elems are later
     * used by the SceneCreator to convert to a ray-traceable scene. THis separates the file parsing structures
     * from the geometry and Scene implementation
     */
    std::vector<SceneElem> objects;
    /**
     * The second step step in parsing a file into the SceneElem Layer.
     * The implementation is responsible for taking the converted tokens and interpreting them
     * as SceneElems to add to the scene. SceneElems are to be added throgh the above objects vector.
     * @param tokens the tokens to be scanned and interpreted through
     */
    virtual void parseTokens(const std::vector<std::string>& tokens) = 0;
    /**
     * The first step in parsing a file into the SceneElem Layer.
     * The implementation is responsible for converting it's file structure
     * into a series of tokens to be scanned and iterated over
     * @param stream the stream used to iterate and parse into tokens
     * @return a vector of tokens represented by strings. This will be used by the implementation to
     * convert into SceneElems.
     */
    virtual std::vector<std::string> tokenize(std::istream& stream) = 0;

public:
    /**
     * the base step of this class, responsible for calling the implementation method
     * @param stream the stream to tokenize
     * @return objects, filled by the implementations
     */
    virtual std::vector<SceneElem> getElems(std::istream& stream) final;
};



#endif //JOHNNYRENDERER2_SCENEFILEPARSER_H
