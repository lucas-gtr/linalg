add_library(ModuleExample STATIC
    Example.cpp
)

target_include_directories(ModuleExample PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(ModuleExample
    PRIVATE
)

