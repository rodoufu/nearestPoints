include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTests payment_check.cpp)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests nearestPoints)
