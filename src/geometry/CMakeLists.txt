add_library(geometry BBox.h BBox.cpp
        Ray.h Transform.cpp
        Transform.h
        GeomData.h
        shapes/Sphere.cpp shapes/Sphere.h
        shapes/Plane.cpp shapes/Plane.h
        shapes/Box.cpp shapes/Box.h
        shapes/Triangle.cpp shapes/Triangle.h)