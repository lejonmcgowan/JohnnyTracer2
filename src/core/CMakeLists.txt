add_library(core IRenderer.h SceneContext.h IParser.h nothing.cpp IPrimitive.cpp Iprimitive.h Scene.h ILight.h
        IVolumeRegion.h IVolumeRegion.cpp)
target_link_libraries(core geometry light)