add_library(camera
        ProjectionCamera.cpp ProjectionCamera.h
        OthoCamera.cpp OthoCamera.h
        PerspectiveCamera.cpp PerspectiveCamera.h
        BoxFilter.cpp BoxFilter.h)
target_link_libraries(camera core)