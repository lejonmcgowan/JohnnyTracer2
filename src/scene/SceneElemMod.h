//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_SCENEELEMMOD_H
#define JOHNNYRENDERER2_SCENEELEMMOD_H

#include <string>
#include <map>

/**
 * Modifications of SceneElems meant to add more details to SceneElems. Can contain a hierarchy of various sub-mods.
 */
struct SceneElemMod
{
public:
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

    ModData getData() const
    {
        return data;
    }

    bool containsData(){return hasData;}
    bool hasChildren(){return !modifiers.empty();}
    void setModifier(std::string name, SceneElemMod mod)
    {
        modifiers.erase(name);
        modifiers.emplace(name,mod);
    }

    SceneElemMod getMod(std::string name)
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
    ModData data;

private:
    bool hasData = false;

};
#endif //JOHNNYRENDERER2_SCENEELEMMOD_H
