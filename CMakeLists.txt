cmake_minimum_required(VERSION 3.16.3)

project(editor)
project(hello_test)

add_definitions(-w)
SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")

set(TextEditorSrc 
    ${CMAKE_SOURCE_DIR}/src/load.c
    ${CMAKE_SOURCE_DIR}/src/mcb.c
    ${CMAKE_SOURCE_DIR}/src/rt.c
    ${CMAKE_SOURCE_DIR}/src/save.c
    ${CMAKE_SOURCE_DIR}/src/show.c
    ${CMAKE_SOURCE_DIR}/src/showrev.c
    ${CMAKE_SOURCE_DIR}/src/common.h
    ${CMAKE_SOURCE_DIR}/src/text/append_line.c
    ${CMAKE_SOURCE_DIR}/src/text/create_text.c
    ${CMAKE_SOURCE_DIR}/src/text/move_cursor.c
    ${CMAKE_SOURCE_DIR}/src/text/process_backward.c
    ${CMAKE_SOURCE_DIR}/src/text/process_forward.c
    ${CMAKE_SOURCE_DIR}/src/text/remove_all.c
    ${CMAKE_SOURCE_DIR}/src/text/remove_last_line.c
    ${CMAKE_SOURCE_DIR}/src/text/text.h
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


add_executable(editor ${TextEditorSrc} ${CMAKE_SOURCE_DIR}/src/editor.c)
enable_testing()

add_executable(
  hello_test
  ${CMAKE_SOURCE_DIR}/tests/mcb_tests.cc
  ${CMAKE_SOURCE_DIR}/tests/rt_tests.cc
  ${CMAKE_SOURCE_DIR}/tests/misc_tests.cc 
  ${CMAKE_SOURCE_DIR}/tests/save_tests.cc
  ${TextEditorSrc}
)

target_link_libraries(
  hello_test
  gtest_main
  gcov
)

include(GoogleTest)
gtest_discover_tests(hello_test)
