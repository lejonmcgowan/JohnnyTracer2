add_library(integrators ISurfaceIntegrator.cpp ISurfaceIntegrator.h
                        IVolumeIntegrator.cpp IVolumeIntegrator.h
                        IVolumeRegion.cpp IVolumeRegion.h)

target_link_libraries(integrators core)