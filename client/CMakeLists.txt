# GLFW + Vulkan + GLM
include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master
)
FetchContent_MakeAvailable(glm)

find_package(Vulkan REQUIRED)

add_executable(client_app
    src/Main.cpp
    src/VulkanApp.cpp
    src/VulkanApp.h
    src/input/Input.cpp
    src/input/Input.h
)

target_link_libraries(client_app PRIVATE common glfw Vulkan::Vulkan glm)
target_include_directories(client_app PRIVATE ${Vulkan_INCLUDE_DIRS})

add_custom_command(TARGET client_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/client/assets $<TARGET_FILE_DIR:client_app>/assets
)