add_library(geometry
        BBox.h BBox.cpp
        IPrimitive.cpp IPrimitive.h
        Ray.h
        Interaction.h
        SurfaceInteraction.h
        shapes/Sphere.cpp shapes/Sphere.h
        shapes/Plane.cpp shapes/Plane.h
        shapes/Box.cpp shapes/Box.h
        shapes/Triangle.cpp shapes/Triangle.h)

target_link_libraries(geometry core)