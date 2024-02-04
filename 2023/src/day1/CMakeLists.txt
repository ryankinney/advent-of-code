add_executable(d1-unit-tests CalibrationDocument.cpp UnitTests.cpp)
target_link_libraries(d1-unit-tests gtest gtest_main advent-of-code)

set(DATA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/p1-example.txt" "${CMAKE_CURRENT_SOURCE_DIR}/p2-example.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set(DEST_PATH "${CMAKE_CURRENT_BINARY_DIR}/")
add_custom_command(
    TARGET d1-unit-tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${DATA_FILES} ${DEST_PATH}
    COMMENT "Copying data files to build directory"
)