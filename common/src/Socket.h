#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Packet.h"
#include <functional>

namespace TT {
    class Socket {
    public:
        explicit Socket(uint16_t port);
        ~Socket();

        void start();
        void const send(int32_t headerType, const std::vector<uint8_t>& data, const std::string& ip, uint16_t port);
        void setOnPacketReceived(std::function<void(const Socket&, const Packet&)> callback);

    private:
        SOCKET sock;
        uint16_t localPort;
        std::function<void(const Socket&, const Packet&)> onPacketReceived;

        void initWinsock();
    };
}
