add_executable(server_app
    src/Main.cpp
)

target_link_libraries(server_app PRIVATE common)
