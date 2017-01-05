add_library(geometry
        ../core/BBox.h ../core/BBox.cpp
        IPrimitive.h
        Ray.h
        Interaction.h
        SurfaceInteraction.h
        shapes/Sphere.cpp shapes/Sphere.h
        shapes/Plane.cpp shapes/Plane.h
        shapes/Box.cpp shapes/Box.h
        shapes/Triangle.cpp shapes/Triangle.h IMaterial.h)

target_link_libraries(geometry core)