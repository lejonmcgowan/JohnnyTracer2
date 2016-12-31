add_library(utils INTERFACE)
target_sources(utils INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/UnitUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SceneContext.h)