add_library(sampler INTERFACE)
target_sources(sampler INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Sample.h ${CMAKE_CURRENT_SOURCE_DIR}/CameraSample.h)
target_link_libraries(sampler INTERFACE core)