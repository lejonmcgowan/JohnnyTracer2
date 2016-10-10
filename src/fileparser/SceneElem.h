//
// Created by lejonmcgowan on 10/5/16.
//

#ifndef JOHNNYRENDERER2_SCENEELEM_H
#define JOHNNYRENDERER2_SCENEELEM_H

#include <map>
#include <string>

struct SceneElem
{
    enum ElemType
    {
        SPHERE,
        TRIANGLE,
        BOX,
        DIR_LIGHT,
        POINR_LIGHT,
        SPOT_LIGHT,
        PLANE,
        CAMERA
    };
    ElemType elemType;
    std::map<std::string, SceneElemMod> modifiers;
};
#endif //JOHNNYRENDERER2_SCENEELEM_H
