set(target_name "chestnut")
set(chestnut_TEST_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/${target_name}_test_install_dir")
set(chestnut_TEST_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/${target_name}_find_package_install_test")

set(PRESET "")
if (MSVC)
    set(PRESET "windows-msvc-debug-developer-mode")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(PRESET "unixlike-clang-debug")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(PRESET "unixlike-gcc-debug")
else ()
    message(AUTHOR_WARNING "Unsupported compiler")
endif ()

add_custom_target(test_install
        ${CMAKE_COMMAND} --install ${PROJECT_BINARY_DIR} --config ${CMAKE_BUILD_TYPE} --prefix ${chestnut_TEST_INSTALL_DIR}

        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/template_find_package_install_test
        ${chestnut_TEST_SOURCE_DIR}

        COMMAND ${CMAKE_COMMAND}
        -B ${chestnut_TEST_SOURCE_DIR}/build
        -S ${chestnut_TEST_SOURCE_DIR}
        --preset "${PRESET}"
        -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
        -DCMAKE_CXX_STANDARD=20
        -DCMAKE_PREFIX_PATH=${chestnut_TEST_INSTALL_DIR}

        COMMAND ${CMAKE_COMMAND}
        --build ${chestnut_TEST_SOURCE_DIR}/build
        --config ${CMAKE_BUILD_TYPE}
        --parallel

        COMMAND ${CMAKE_COMMAND}
        --install ${chestnut_TEST_SOURCE_DIR}/build
        --config ${CMAKE_BUILD_TYPE}
        --prefix ${chestnut_TEST_SOURCE_DIR}/install
        )

add_custom_target(clean_test_install
        ${CMAKE_COMMAND} -E rm -Rf ${example_library_TEST_INSTALL_DIR}
        COMMAND ${CMAKE_COMMAND} -E rm -Rf ${example_library_TEST_SOURCE_DIR}
        )