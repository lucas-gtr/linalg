cmake_minimum_required(VERSION 3.16)

set(PROJECT_TARGET_NAME Template)

project(${PROJECT_TARGET_NAME}
    VERSION 0.0.1
    DESCRIPTION ""
    LANGUAGES C CXX
)

# Modern C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Allow user-defined modules 
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(src/ModuleExample)

add_executable(${PROJECT_TARGET_NAME} src/main.cpp 
    src/SanitizerTests.cpp
)

target_include_directories(${PROJECT_TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_TARGET_NAME}
    PRIVATE
        ModuleExample
)

# Options for professional dev workflow
option(ENABLE_WARNINGS             "Enable compiler warnings"                    ON)
option(ENABLE_SANITIZERS           "Enable runtime sanitizers"                   OFF)
option(ENABLE_LTO                  "Enable link-time optimization"               OFF)
option(ENABLE_CLANG_FORMAT         "Run clang-format in build"                   OFF)
option(ENABLE_CLANG_TIDY           "Run clang-tidy analysis"                     OFF)
option(ENABLE_FIX_CLANG_TIDY       "Run clang-tidy with --fix option"            OFF)
option(ENABLE_DOXYGEN              "Build documentation with Doxygen"            OFF)
option(ENABLE_TESTS                "Enable tests with GoogleTest"                OFF)
option(ENABLE_OPTIMIZATIONS        "Enable high-performance compile flags"       OFF)
option(ENABLE_UNIT_TESTS           "Enable tests with GoogleTest"                OFF)

target_include_directories(${PROJECT_TARGET_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

set(FILES_TO_CHECK "" CACHE STRING "Files to check with Clang-Tidy and Clang-Format. Set to 'all' to check all source files.")

if(ENABLE_OPTIMIZATIONS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${PROJECT_TARGET_NAME} PRIVATE -O3 -march=native)
endif()

if(ENABLE_OPTIMIZATIONS AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_TARGET_NAME} PRIVATE /O2)
endif()

if(ENABLE_COMPILE_WARNINGS)
    include(warnings)
    target_enable_warnings(${PROJECT_TARGET_NAME})
endif()

if(ENABLE_SANITIZERS)
    include(sanitizers)    
    target_enable_sanitizers(${PROJECT_TARGET_NAME})
endif()

if(ENABLE_LTO)
    include(lto)
    target_enable_lto(${PROJECT_TARGET_NAME})
endif()

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