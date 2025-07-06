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

# Allow user-defined modules 
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Options for professional dev workflow
option(ENABLE_CLANG_FORMAT         "Run clang-format in build"                   OFF)
option(ENABLE_CLANG_TIDY           "Run clang-tidy analysis"                     OFF)
option(ENABLE_FIX_CLANG_TIDY       "Run clang-tidy with --fix option"            OFF)
option(ENABLE_DOXYGEN              "Build documentation with Doxygen"            OFF)
option(ENABLE_UNIT_TESTS           "Enable tests with GoogleTest"                OFF)

if(ENABLE_CLANG_FORMAT)
    include(clang-format)
    run_clang_format()
endif()

if(ENABLE_CLANG_TIDY)
    include(clang-tidy)
    run_clang_tidy(${ENABLE_FIX_CLANG_TIDY})
endif()

if(ENABLE_DOXYGEN)
    include(Doxygen)
    generate_doxygen_documentation()
endif()

if(ENABLE_UNIT_TESTS)
    enable_testing()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g" CACHE STRING "Compiler flags for tests" FORCE)

    add_subdirectory(external/googletest)
    add_subdirectory(tests)
endif()