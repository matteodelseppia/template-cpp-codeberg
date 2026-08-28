cmake_minimum_required(VERSION 3.24)

project(mi VERSION 0.1.0 LANGUAGES CXX)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.0)
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
endif()

option(MI_BUILD_TESTING "Build the unit tests" ON)

add_library(mi_hello src/Hello.cpp)
add_library(mi::hello ALIAS mi_hello)

target_include_directories(mi_hello
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_compile_features(mi_hello PUBLIC cxx_std_20)

add_executable(mi src/Main.cpp)
target_link_libraries(mi PRIVATE mi::hello)

if(MSVC)
    target_compile_options(mi_hello PRIVATE /W4 /permissive-)
    target_compile_options(mi PRIVATE /W4 /permissive-)
else()
    target_compile_options(mi_hello PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(mi PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
if(BUILD_TESTING AND MI_BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(doctest)

    add_executable(mi_tests tests/HelloTest.cpp)
    target_link_libraries(mi_tests PRIVATE mi::hello doctest::doctest_with_main)

    if(MSVC)
        target_compile_options(mi_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(mi_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    add_test(NAME mi_tests COMMAND mi_tests)
endif()
