//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_SCENEELEM_H
#define JOHNNYRENDERER2_SCENEELEM_H

#include <map>
#include <string>
#include <memory>
#include "SceneElemMod.h"

/**
 * Top-level, generic scene objects to be used when generating a scene. Intended to unite the parsing of different
 * file formats into a unified data structure. For extensibility, the SceneElem can include a map of SceneElemMods to
 * add further properties to the Scene Object (materials, transforms, texture handles, etc). These Mods an have another
 * sub-map of these mods, and so forth. For simplicity in debugging, SceneElems are purposefully made to NOT be a super
 * nor subset of the SceneElemMods, despite the similarities in data
 */
struct SceneElem
{
    enum ElemType
    {
        CAMERA,
        LIGHT,
        SHAPE,
        CUSTOM
    };
    const std::string name;
    const ElemType type;
    SceneElem(std::string name,ElemType type): name(name),type(type){}
    bool hasChildren(){return !modifiers.empty();}
    void setModifier(std::string name, SceneElemMod mod)
    {
        modifiers.erase(name);
        modifiers.emplace(name,mod);
    }
    SceneElemMod& getMod(std::string name)
    {
        if(!hasMod(name))
        {
            std::runtime_error("Mod " + name + " does not exsist. Please check using hasMod() before trying to access"
                " scene elem");
            exit(2);
        }

        return modifiers.at(name);
    }

    bool hasMod(std::string name)
    {
        return modifiers.find(name) != modifiers.end();
    }
private:
    std::map<std::string, SceneElemMod> modifiers;
};
#endif //JOHNNYRENDERER2_SCENEELEM_H
