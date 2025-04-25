#include <iostream>

#include "Socket.h"
#include <thread>

void received(TT::Packet p) {
    std::cout << "Received!" << std::endl;
    p.print();
}

int main() {
    TT::Socket sock(12345);
    sock.setOnPacketReceived(received);

    std::thread listener([&sock]() {
        sock.start();
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::string msg = "Hello from OOP client!";
    sock.send(1, std::vector<uint8_t>(msg.begin(), msg.end()), "127.0.0.1", 12345);

    listener.join();
    return 0;
}
