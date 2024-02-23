add_executable(d5-unit-tests Almanac.cpp AlmanacParser.cpp UnitTests.cpp)
target_link_libraries(d5-unit-tests gtest gtest_main advent-of-code)

set(DATA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set(DEST_PATH "${CMAKE_CURRENT_BINARY_DIR}/")
add_custom_command(
    TARGET d5-unit-tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${DATA_FILES} ${DEST_PATH}
    COMMENT "Copying data files to build directory"
)
