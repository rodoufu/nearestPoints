include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_FILES *.cpp)
add_executable(runTests ${TEST_FILES})

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests nearestPoints)
