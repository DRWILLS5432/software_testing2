cmake_minimum_required(VERSION 3.16.3)

project(Editor)
project(hello_test)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/text/move_cursor_left.c
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
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(Editor ${TextEditorSrc} editor.c)
enable_testing()

add_executable(
  hello_test
  tests/hello_tests.cc
  ${TextEditorSrc}
)
target_link_libraries(
  hello_test
  gtest_main
)

