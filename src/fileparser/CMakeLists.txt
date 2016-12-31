add_library(fileparser
        POVParser.cpp POVParser.h
        SceneFileParser.cpp SceneFileParser.h
        SceneElemParser.cpp SceneElemParser.h
        POVElemParser.cpp POVElemParser.h)

target_link_libraries(fileparser core utils)