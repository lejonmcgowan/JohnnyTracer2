add_library(scene SceneCreator.cpp SceneCreator.h
        Scene.h
        ../core/utils/SceneContext.h
        SceneElem.h
        SceneElemMod.h Scene.cpp)


target_link_libraries(scene fileparser core)