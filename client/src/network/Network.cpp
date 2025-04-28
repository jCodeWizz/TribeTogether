#include "Network.h"
#include <thread>
#include "Protocol.h"

namespace TT::Network {
    static Socket socket(6767);

    void init() {
        socket.setOnPacketReceived(received);

        std::thread listener([]() {
            socket.start();
        });
        listener.detach();

        send(NW_INIT, std::vector<uint8_t>(), "127.0.0.1", 9696);
    }

    void send(int32_t headerType, const std::vector<uint8_t>& data, const std::string& ip, uint16_t port) {
        socket.send(headerType, data, ip, port);
    }

    void received(const Socket& s, const Packet& p) {
        p.print();
    }
}