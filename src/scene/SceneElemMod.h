//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_SCENEELEMMOD_H
#define JOHNNYRENDERER2_SCENEELEMMOD_H

#include <string>

struct SceneElemMod
{
    union ModData
    {
        double dbl;
        double vec2[2];
        double vec3[3];
        double vec4[4];
        int integer;
        char letters[30];
    };
    ModData data;
    std::string name;
    SceneElemMod(std::string name): name(name){}
};
#endif //JOHNNYRENDERER2_SCENEELEMMOD_H
