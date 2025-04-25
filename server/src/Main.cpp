#include "Socket.h"
#include <thread>

int main() {
    Socket sock(12345);

    std::thread listener([&sock]() {
        sock.start(); // start listening in separate thread
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::string msg = "Hello from OOP client!";
    sock.send(1, std::vector<uint8_t>(msg.begin(), msg.end()), "127.0.0.1", 12345);

    listener.join(); // keep the listener alive
    return 0;
}