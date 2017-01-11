add_library(geometry
        ../core/BBox.h ../core/BBox.cpp
        ../core/IPrimitive.h
        Ray.h
        Interaction.h
        SurfaceInteraction.h
        shapes/Sphere.cpp shapes/Sphere.h
        shapes/Plane.cpp shapes/Plane.h
        shapes/Box.cpp shapes/Box.h
        shapes/Triangle.cpp shapes/Triangle.h IMaterial.h GeomPrimitive.cpp GeomPrimitive.h bxdfs/BXDF.h bxdfs/BSDF.h bxdfs/BSDF.cpp)

target_link_libraries(geometry core)