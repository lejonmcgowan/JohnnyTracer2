add_library(scene INTERFACE)
target_sources(scene INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/SceneElem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SceneElemMod.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SceneContext.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Scene.h)