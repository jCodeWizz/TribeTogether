#pragma once
#include "Socket.h"
#include "Packet.h"
#include "Protocol.h"

namespace TT::Network {

    void init();
    void send(int32_t headerType, const std::vector<uint8_t>& data, const std::string& ip, uint16_t port);
    void received(const Socket& s, const Packet& p);

}