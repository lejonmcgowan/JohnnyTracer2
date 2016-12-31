add_library(core IVolumeRegion.h IVolumeRegion.cpp
        IShape.cpp IShape.h
        IAggregate.cpp IAggregate.h
        ICamera.cpp ICamera.h
        ISampler.cpp ISampler.h
        IFilter.cpp IFilter.h
        Film.cpp Film.h
        IMaterial.cpp IMaterial.h
        ITexture.cpp ITexture.h
        ILight.cpp
        IRenderer.cpp
        ISurfaceIntegrator.cpp ISurfaceIntegrator.h
        IVolumeIntegrator.cpp IVolumeIntegrator.h NullCore.h)
target_link_libraries(core geometry light samplers)