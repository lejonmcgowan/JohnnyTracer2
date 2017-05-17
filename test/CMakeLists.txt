find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/release-1.8.0.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        # Disable install step
        INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)
# Create a libgtest target to be used as a dependency by test programs
message(STATUS ${source_dir} " and " ${binary_dir})
add_library(libgtest INTERFACE)
add_dependencies(libgtest gtest)
target_link_libraries(libgtest INTERFACE "${binary_dir}/googlemock/gtest/libgtest.a" "${binary_dir}/googlemock/gtest/libgtest_main.a" Threads::Threads)
target_include_directories(libgtest INTERFACE "${source_dir}/googletest/include" "${source_dir}/googlemock/include")

add_executable(testcore testcore/coremain.cpp testcore/TestTransform.cpp common/printHelper.h)
target_link_libraries(testcore PUBLIC libgtest core)