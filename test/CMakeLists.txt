find_package(Threads REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR on)

add_executable(testtransform testcore/testcore.cpp testcore/TestTransform.cpp common/printHelper.h common/catch.hpp common/veccompare.h)
target_link_libraries(testtransform core)