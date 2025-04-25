#include "Packet.h"

Packet::Packet(int32_t header, const std::vector<uint8_t>& data,
               const std::string& ip, uint16_t port)
    : headerType(header), content(data), senderIp(ip), senderPort(port) {}