//
// Created by lejonmcgowan on 12/28/16.
//

#ifndef JOHNNYRENDERER2_POVELEMPARSER_H
#define JOHNNYRENDERER2_POVELEMPARSER_H

#include "SceneElemParser.h"

class POVElemParser: public SceneElemParser
{
    std::shared_ptr<ICamera> parseCamera(SceneElem elem) override;
    std::shared_ptr<ILight> parseLight(SceneElem elem) override;
    std::shared_ptr<IShape> parseShape(SceneElem elem) override;
public:
    void parseCustom(SceneElem elem, SceneCreator& sceneCreator) override;
};


#endif //JOHNNYRENDERER2_POVELEMPARSER_H
