#include <iostream>

#include "Socket.h"
#include <thread>
#include "Protocol.h"


void received(const TT::Socket& s, const TT::Packet& p) {

    if (p.headerType == NW_INIT) {
        std::cout << "New client connected!" << "\n";
        s.send(NW_CONFIRM_INIT, std::vector<uint8_t>(), p.senderIp, p.senderPort);
    }
}

int main() {
    TT::Socket sock(9696);
    sock.setOnPacketReceived(received);

    std::thread listener([&sock]() {
        sock.start();
    });

    //std::string msg = "Hello from OOP client!";
    //sock.send(1, std::vector<uint8_t>(msg.begin(), msg.end()), "127.0.0.1", 12345);

    listener.join();
    return 0;
}
