function(create_test testName)
    add_executable(${testName} ${testName}.cpp)
    target_link_libraries(${testName} PRIVATE gtest_main chestnut::chestnut)
    add_test(NAME chestnut.${testName} COMMAND ${testName})
endfunction()

create_test(google_test_usage)
