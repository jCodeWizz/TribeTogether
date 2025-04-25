#include "Packet.h"
#include <iostream>

namespace TT {
    Packet::Packet(int32_t header, const std::vector<uint8_t>& data, const std::string& ip, uint16_t port)
        : headerType(header), content(data), senderIp(ip), senderPort(port) {
    }

    void Packet::print() const {
        std::cout << "Packet(" << headerType << "):" << std::endl;
        std::cout << "  From: " << senderIp << ":" << senderPort << std::endl;
        for (auto c : content) std::cout << c;
        std::cout << std::endl;
    }
}
