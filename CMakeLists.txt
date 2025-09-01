cmake_minimum_required(VERSION 3.16)
project(asan_demo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)

option(ENABLE_ASAN  "Enable AddressSanitizer" ON)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)

add_library(demo STATIC src/lib.cpp)
add_executable(run_tests tests/test_overflow.cpp)
target_link_libraries(run_tests PRIVATE demo)

# Debug-Symbole & bessere Stacks
target_compile_options(demo      PRIVATE -g -fno-omit-frame-pointer)
target_compile_options(run_tests PRIVATE -g -fno-omit-frame-pointer)

if(ENABLE_ASAN)
  message(STATUS "Building with AddressSanitizer")
  target_compile_options(demo      PRIVATE -fsanitize=address)
  target_compile_options(run_tests PRIVATE -fsanitize=address)
  target_link_options  (run_tests PRIVATE -fsanitize=address)
endif()

if(ENABLE_UBSAN)
  message(STATUS "Building with UndefinedBehaviorSanitizer")
  target_compile_options(demo      PRIVATE -fsanitize=undefined)
  target_compile_options(run_tests PRIVATE -fsanitize=undefined)
  target_link_options  (run_tests PRIVATE -fsanitize=undefined)
endif()

add_test(NAME overflow_test COMMAND run_tests)
#set_tests_properties(overflow_test PROPERTIES
#  FAIL_REGULAR_EXPRESSION "AddressSanitizer:|heap-buffer-overflow|ERROR: .*Sanitizer"
#)


enable_testing()