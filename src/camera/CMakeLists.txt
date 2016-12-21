add_library(camera ProjectionCamera.cpp ProjectionCamera.h OrthroCamera.cpp OrthroCamera.h PerspectiveCamera.cpp
        PerspectiveCamera.h ImageFilm.cpp ImageFilm.h)
target_link_libraries(camera core)