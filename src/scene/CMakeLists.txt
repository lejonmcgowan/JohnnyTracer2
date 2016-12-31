add_library(scene SceneCreator.cpp SceneCreator.h
        Scene.h
        ../utils/SceneContext.h
        SceneElem.h
        SceneElemMod.h)


target_link_libraries(scene fileparser)