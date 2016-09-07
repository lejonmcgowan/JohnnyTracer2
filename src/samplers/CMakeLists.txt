add_library(samplers INTERFACE)
target_sources(samplers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Sample.h ${CMAKE_CURRENT_SOURCE_DIR}/CameraSample.h)