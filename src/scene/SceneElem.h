//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_SCENEELEM_H
#define JOHNNYRENDERER2_SCENEELEM_H

#include <map>
#include <string>
#include <memory>
#include "SceneElemMod.h"

struct SceneElem
{
    std::string name;
    SceneElem(std::string name): name(name){}
    bool hasChildren(){return !modifiers.empty();}
    void addModifier(std::string name, SceneElemMod mod)
    {
        modifiers.emplace(name,mod);
    }
private:
    std::map<std::string, SceneElemMod> modifiers;
};
#endif //JOHNNYRENDERER2_SCENEELEM_H
