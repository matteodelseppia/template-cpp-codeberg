cmake_minimum_required(VERSION 3.24)

# Replace `template_project` with your project's CMake-safe name.
project(template_project VERSION 0.1.0 LANGUAGES CXX)

# doctest 2.4.11 supports CMake 4 but declares an older policy baseline.
if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.0)
  set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
endif()

option(TEMPLATE_PROJECT_BUILD_TESTING "Build the unit tests" ON)
option(TEMPLATE_PROJECT_ENABLE_CLANG_TIDY "Run clang-tidy while compiling" OFF)

function(template_project_set_warnings target)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 /permissive-)
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
endfunction()

function(template_project_enable_clang_tidy target)
  if(TEMPLATE_PROJECT_ENABLE_CLANG_TIDY)
    find_program(TEMPLATE_PROJECT_CLANG_TIDY NAMES clang-tidy REQUIRED)
    set_property(TARGET ${target} PROPERTY CXX_CLANG_TIDY
      "${TEMPLATE_PROJECT_CLANG_TIDY};--warnings-as-errors=*")
  endif()
endfunction()

# Replace this sample library with the targets for your project.
add_library(template_project_lib src/TemplateProject.cpp)
add_library(template_project::lib ALIAS template_project_lib)

target_include_directories(template_project_lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(template_project_lib PUBLIC cxx_std_20)
template_project_set_warnings(template_project_lib)
template_project_enable_clang_tidy(template_project_lib)

# Delete this executable target if the project is a library only.
add_executable(template_project src/Main.cpp)
target_link_libraries(template_project PRIVATE template_project::lib)
template_project_set_warnings(template_project)
template_project_enable_clang_tidy(template_project)

include(CTest)
if(BUILD_TESTING AND TEMPLATE_PROJECT_BUILD_TESTING)
  include(FetchContent)

  FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(doctest)

  add_executable(template_project_tests tests/TemplateProjectTest.cpp)
  target_link_libraries(template_project_tests
    PRIVATE template_project::lib doctest::doctest_with_main)
  template_project_set_warnings(template_project_tests)
  template_project_enable_clang_tidy(template_project_tests)

  add_test(NAME template_project_tests COMMAND template_project_tests)
endif()
