add_executable(linalg_UnitTests main_tests.cpp)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*Tests.cpp")

target_sources(linalg_UnitTests PRIVATE ${TEST_SOURCES})

target_link_libraries(linalg_UnitTests PRIVATE 
    gtest
    gtest_main
    gmock
)

target_include_directories(linalg_UnitTests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/googletest/include
    ${CMAKE_SOURCE_DIR}/external/googletest/googlemock/include
)

add_test(NAME linalg_UnitTests COMMAND linalg_UnitTests)
