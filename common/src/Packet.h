#pragma once

#include <string>
#include <vector>
#include <cstdint>

class Packet {
public:
    int32_t headerType;
    std::vector<uint8_t> content;
    std::string senderIp;
    uint16_t senderPort;

    Packet(int32_t header, const std::vector<uint8_t>& data,
           const std::string& ip, uint16_t port);
};