#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Packet.h"

class Socket {
public:
    explicit Socket(uint16_t port);
    ~Socket();

    void start();
    void send(int32_t headerType, const std::vector<uint8_t>& data,
              const std::string& ip, uint16_t port);

private:
    SOCKET sock;
    uint16_t localPort;

    void initWinsock();
};