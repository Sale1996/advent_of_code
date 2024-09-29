find_package(OpenSSL REQUIRED)
add_executable(puzzle_4_1 4_1.cpp)
target_link_libraries(puzzle_4_1 OpenSSL::SSL)