# Need CMake 3.0
cmake_minimum_required (VERSION 3.28.0)

# This is the name of the repository
project ("geometry")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
    add_compile_options(-Wall -Wextra -Wpedantic -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-value)
endif ()

# Add the geometry project
if ( NOT "${HAS_GEOMETRY}")

    # Log
    message("[geometry] Adding geometry project")

    set(GEOMETRY_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the geometry project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_GEOMETRY true PARENT_SCOPE)
        set(GEOMETRY_INCLUDE_DIR ${GEOMETRY_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to this project's executable.
add_executable (geometry_example "main.c")
add_dependencies(geometry_example geometry)
target_include_directories(geometry_example PUBLIC ${GEOMETRY_INCLUDE_DIR})
target_link_libraries(geometry_example geometry)

# Add source to the tester
add_executable (geometry_test "geometry_test.c")
add_dependencies(geometry_test geometry log sync)
target_include_directories(geometry_test PUBLIC ${GEOMETRY_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(geometry_test geometry log sync)

# Add source to this project's library
add_library (geometry SHARED "geometry.c")
add_dependencies(geometry)
target_include_directories(geometry PUBLIC ${GEOMETRY_INCLUDE_DIR})
target_link_libraries(geometry)