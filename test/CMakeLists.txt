include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_FILES *.cpp)
add_executable("${CMAKE_PROJECT_NAME}_test" ${TEST_FILES})

target_link_libraries("${CMAKE_PROJECT_NAME}_test" gtest gtest_main ${CMAKE_PROJECT_NAME})

include(GoogleTest)
add_test(NAME "${CMAKE_PROJECT_NAME}_test" COMMAND "${CMAKE_PROJECT_NAME}_test")

add_custom_target(
	test
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/RunUnitTests.touch "${CMAKE_PROJECT_NAME}_test")

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/RunUnitTests.touch
	COMMAND "${CMAKE_PROJECT_NAME}_test")