add_library(common STATIC
        src/Protocol.h
        src/Packet.cpp
        src/Packet.h
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)