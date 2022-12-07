add_library(test_input INTERFACE)
target_include_directories(test_input INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/example_input.hpp"
        )
target_link_libraries(test_input INTERFACE chestnut::chestnut)

function(create_test testName)
    add_executable(${testName} ${testName}.cpp)
    target_link_libraries(${testName} PRIVATE gtest_main chestnut::chestnut test_input)
    add_test(NAME chestnut.${testName} COMMAND ${testName})
endfunction()

create_test(kdtree)
create_test(point)
