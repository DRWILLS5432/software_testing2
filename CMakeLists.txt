cmake_minimum_required(VERSION 3.16.3)

project(Editor)
project(hello_test)

add_definitions(-w)
SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")

set(TextEditorSrc 
    ${CMAKE_CURRENT_SOURCE_DIR}/load.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mcb.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/save.c
    ${CMAKE_CURRENT_SOURCE_DIR}/show.c
    ${CMAKE_CURRENT_SOURCE_DIR}/showrev.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/text/append_line.c
    ${CMAKE_CURRENT_SOURCE_DIR}/text/create_text.c
    ${CMAKE_CURRENT_SOURCE_DIR}/text/move_cursor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/text/process_backward.c
    ${CMAKE_CURRENT_SOURCE_DIR}/text/process_forward.c
    ${CMAKE_CURRENT_SOURCE_DIR}/text/remove_all.c
    ${CMAKE_CURRENT_SOURCE_DIR}/text/remove_last_line.c
    ${CMAKE_CURRENT_SOURCE_DIR}/text/text.h
)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(Editor ${TextEditorSrc} editor.c)
enable_testing()

add_executable(
  hello_test
  tests/mcb_tests.cc
  tests/rt_tests.cc
  tests/misc_tests.cc 
  tests/save_tests.cc
  ${TextEditorSrc}
)

target_link_libraries(
  hello_test
  gtest_main
  gcov
)

include(GoogleTest)
gtest_discover_tests(hello_test)
