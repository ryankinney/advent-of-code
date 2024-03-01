add_executable(unit-tests UnitTests.cpp)
target_link_libraries(unit-tests gtest gtest_main)

set(DATA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/example.txt" "${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
set(DEST_PATH "${CMAKE_CURRENT_BINARY_DIR}/")
add_custom_command(
    TARGET unit-tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${DATA_FILES} ${DEST_PATH}
    COMMENT "Copying data files to build directory"
)