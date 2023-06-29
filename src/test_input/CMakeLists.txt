set(chestnut_test_input_HEADERS
        include/chestnut/test/test_input.hpp
        )

set(chestnut_test_input_SOURCES
        source/test_input.cpp
        )

set(TARGET_NAME chestnut_test_input)
add_library(${TARGET_NAME} ${chestnut_test_input_SOURCES} ${chestnut_test_input_HEADERS})
add_library(${TARGET_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})
target_include_directories(${TARGET_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/export_header_includes/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

target_link_libraries(${TARGET_NAME} PUBLIC chestnut::chestnut)

set_target_properties(${TARGET_NAME}
        PROPERTIES
        LANGUAGE CXX
        DEBUG_POSTFIX d
        VERSION 0.1.0
        SOVERSION 0
        )

include(Warnings)
add_warnings_and_compile_options(${TARGET_NAME} ${${PROJECT_NAME}_WARNINGS_AS_ERRORS})

if (${PROJECT_NAME}_STATIC_ANALYSIS)
    include(static_analysis)
    enable_static_analysis(${TARGET_NAME} ${${PROJECT_NAME}_WARNINGS_AS_ERRORS})
endif ()
