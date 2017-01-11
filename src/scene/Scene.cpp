//
// Created by lejonmcgowan on 1/3/17.
//
#include "Scene.h"

Scene::Scene(std::shared_ptr<IPrimitive> aggregate, const std::vector<std::shared_ptr<ILight>>& lights)
    : lights(lights), aggregate(aggregate) {
    // Scene Constructor Implementation
    worldBound = aggregate->worldBound();
    //todo add lights to the scene
}