cmake_minimum_required(VERSION 3.10)
project(TribeTogether)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add subdirectories
add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)