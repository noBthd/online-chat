cmake_minimum_required(VERSION 3.15)
project(online_chat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_TOOLCHAIN_FILE "/Users/egorkirichenko/.vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(SFML CONFIG REQUIRED COMPONENTS graphics window system network)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system sfml-network)