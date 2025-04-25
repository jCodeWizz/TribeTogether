#include <iostream>

#include "Socket.h"
#include <thread>



void received(TT::Socket s, TT::Packet p) {
    s.send(p.headerType, p.content, p.senderIp, p.senderPort);
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
