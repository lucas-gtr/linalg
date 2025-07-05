add_executable(UnitTests main_tests.cpp)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*Tests.cpp")

target_sources(UnitTests PRIVATE ${TEST_SOURCES})

target_link_libraries(UnitTests PRIVATE 
    ModuleExample
    gtest
    gtest_main
    gmock
)

target_include_directories(UnitTests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/googletest/include
    ${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include
)

add_test(NAME UnitTests COMMAND UnitTests)
