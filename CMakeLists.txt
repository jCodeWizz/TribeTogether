cmake_minimum_required(VERSION 3.10)
project(TribeTogether)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Vulkan
find_package(Vulkan REQUIRED)

# GLFW (Using FetchContent to avoid installation issues)
include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

# GLM (Header-only library)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glm)

# Add the executable
add_executable(TribeTogether src/Main.cpp src/Main.cpp
        src/VulkanApp.h
        src/VulkanApp.cpp)

# Link libraries
target_link_libraries(TribeTogether PRIVATE Vulkan::Vulkan glfw glm)

# Include directories
target_include_directories(TribeTogether PRIVATE ${Vulkan_INCLUDE_DIRS})

