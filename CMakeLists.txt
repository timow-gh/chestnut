cmake_minimum_required(VERSION 3.21) # CMakePresets are supported since version 3.21

project(chestnut
        VERSION 0.1.0
        LANGUAGES CXX)

# Make all modules available to this project and other projects that consume this project by
# adding the cmake directory to the CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(project_preamble)
include(setup_export_set_installation)
include(warnings)
include(static_analysis)

include(cmake/CPM.cmake)
if (NOT CPM_SOURCE_CACHE AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/CPMSourceVariable.cmake")
    include(CPMSourceVariable.cmake)
endif ()

if (NOT CPM_SOURCE_CACHE)
    message(AUTHOR_WARNING "CPM_SOURCE_CACHE not set. The source files are downloaded for every build. This is not recommended.
        Set the CPM_SOURCE_CACHE variable to a directory of your choice to cache the cloned git repositories.
        Set the CPM_SOURCE_CACHE variable in CPMSourceVariable.cmake to keep your paths private.")
endif ()

# Set common properties for cross platform builds
project_preamble()

if ((CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR))
    set(IS_TOP_LEVEL_PROJECT TRUE)
else ()
    set(IS_TOP_LEVEL_PROJECT FALSE)
endif ()
message(STATUS "IS_TOP_LEVEL_PROJECT: ${IS_TOP_LEVEL_PROJECT}")

if (IS_TOP_LEVEL_PROJECT)
    option(${PROJECT_NAME}_USE_SCCACHE "Use sccache" ON)
    option(${PROJECT_NAME}_WARNINGS_AS_ERRORS "Treat compiler warnings as errors " ON)
    option(${PROJECT_NAME}_STATIC_ANALYSIS "" ON)
    option(${PROJECT_NAME}_TESTS "" ON)
    option(${PROJECT_NAME}_BENCHMARKS "" ON)
else ()
    option(${PROJECT_NAME}_USE_SCCACHE "Use sccache" OFF)
    option(${PROJECT_NAME}_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
    option(${PROJECT_NAME}_STATIC_ANALYSIS "" OFF)
    option(${PROJECT_NAME}_TESTS "" OFF)
    option(${PROJECT_NAME}_BENCHMARKS "" OFF)
endif ()
option(${PROJECT_NAME}_INSTALL "Install project targets" ON)

if (${PROJECT_NAME}_USE_SCCACHE)
    if (NOT "${CMAKE_GENERATOR}" STREQUAL "Ninja")
        message(AUTHOR_WARNING "sccache is only testet with the generator Ninja. Setting ${PROJECT_NAME}_USE_SCCACHE to OFF.")
        set(${PROJECT_NAME}_USE_SCCACHE OFF CACHE BOOL "" FORCE)
    else ()
        find_program(CCACHE_PROGRAM sccache)
        if (CCACHE_PROGRAM)
            # Makefile Generators and the Ninja generator prefix compiler commands with the given launcher command line.
            # This is intended to allow launchers to intercept build problems with high granularity. Other generators ignore
            # this property because their underlying build systems provide no hook to wrap individual commands with a launcher.
            set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
            set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")

            include(cmake/sccache_setup.cmake)
            fix_msvc_ninja_compile_flags()
        else ()
            message(AUTHOR_WARNING "sccache not found. Please install it or disable USE_SCCACHE")
        endif ()
    endif ()
endif ()

message(STATUS "${PROJECT_NAME}_USE_SCCACHE: ${${PROJECT_NAME}_USE_SCCACHE}")
message(STATUS "${PROJECT_NAME}_WARNINGS_AS_ERRORS: ${${PROJECT_NAME}_WARNINGS_AS_ERRORS}")
message(STATUS "${PROJECT_NAME}_STATIC_ANALYSIS: ${${PROJECT_NAME}_STATIC_ANALYSIS}")


add_subdirectory(dependencies)

add_subdirectory(src)

if (${PROJECT_NAME}_BENCHMARKS)
    add_subdirectory(benchmark)
endif ()

if (${PROJECT_NAME}_TESTS)
    include(CTest)
    # "This command should be in the source directory root because ctest expects to find a test
    # file in the build directory root.", CMake docs
    enable_testing()
    add_subdirectory(test)
endif ()

