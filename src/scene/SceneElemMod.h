//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_SCENEELEMMOD_H
#define JOHNNYRENDERER2_SCENEELEMMOD_H

#include <string>
#include <map>

struct SceneElemMod
{
    std::string name;
    SceneElemMod(const std::string& name): name(name){}
    union ModData
    {
        double dbl;
        double vec2[2];
        double vec3[3];
        double vec4[4];
        int integer;
        char letters[30];
    };
    void setData(ModData data)
    {
        this->data = data;
        hasData = true;
    }
    void unsetData()
    {
        hasData = false;
    }
    bool containsData(){return hasData;}
    bool hasChildren(){return !modifiers.empty();}
    void addModifier(std::string name, SceneElemMod mod)
    {
        modifiers.emplace(name,mod);
    }
private:
    std::map<std::string, SceneElemMod> modifiers;
    ModData data;
    bool hasData;

};
#endif //JOHNNYRENDERER2_SCENEELEMMOD_H
