cmake_minimum_required(VERSION 3.16)

project(linalg
    VERSION 1.0.0
    DESCRIPTION "Header-only linear algebra library"
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(linalg INTERFACE)

target_include_directories(linalg INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(linalg INTERFACE cxx_std_11)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
endif()

option(LINALG_ENABLE_CLANG_FORMAT   "Run clang-format in build"                   OFF)
option(LINALG_ENABLE_CLANG_TIDY     "Run clang-tidy analysis"                     OFF)
option(LINALG_ENABLE_FIX_CLANG_TIDY "Run clang-tidy with --fix option"            OFF)
option(LINALG_ENABLE_DOXYGEN        "Build documentation with Doxygen"            OFF)
option(LINALG_ENABLE_UNIT_TESTS     "Enable tests with GoogleTest"                OFF)

if(LINALG_ENABLE_CLANG_FORMAT AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    include(cmake/clang-format.cmake)
    run_clang_format()
endif()

if(LINALG_ENABLE_CLANG_TIDY AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    include(cmake/clang-tidy.cmake)
    run_clang_tidy(${LINALG_ENABLE_FIX_CLANG_TIDY})
endif()

if(LINALG_ENABLE_DOXYGEN AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    include(cmake/Doxygen.cmake)
    generate_doxygen_documentation()
endif()

if(LINALG_ENABLE_UNIT_TESTS AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    enable_testing()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g" CACHE STRING "Compiler flags for tests" FORCE)

    add_subdirectory(external/googletest)
    add_subdirectory(tests)
endif()
