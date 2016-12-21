#get all the other sources
macro(MACRO_SUBDIRLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

set(src_libraries "")
MACRO_SUBDIRLIST(src_libraries ${CMAKE_CURRENT_SOURCE_DIR})
foreach(src_library ${src_libraries})
    add_subdirectory(${src_library})
endforeach()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${src_libraries})