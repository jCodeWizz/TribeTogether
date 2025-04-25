#include "Socket.h"
#include <iostream>

namespace TT {
    Socket::Socket(uint16_t port) : localPort(port) {
        initWinsock();

        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock == INVALID_SOCKET) {
            std::cerr << "Socket creation failed.\n";
            exit(1);
        }

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(localPort);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
            std::cerr << "Bind failed.\n";
            closesocket(sock);
            WSACleanup();
            exit(1);
        }
    }

    Socket::~Socket() {
        closesocket(sock);
        WSACleanup();
    }

    void Socket::initWinsock() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
            std::cerr << "WSAStartup failed.\n";
            exit(1);
        }
    }

    void Socket::setOnPacketReceived(std::function<void(const Packet&)> callback) {
        onPacketReceived = std::move(callback);
    }

    void Socket::start() {
        char buffer[1024];
        sockaddr_in from{};
        int fromLen = sizeof(from);

        while (true) {
            int recvLen = recvfrom(sock, buffer, sizeof(buffer), 0,
                                   (sockaddr*)&from, &fromLen);
            if (recvLen == SOCKET_ERROR) {
                std::cerr << "recvfrom failed.\n";
                continue;
            }

            if (recvLen < sizeof(int32_t)) continue;

            int32_t headerType;
            memcpy(&headerType, buffer, sizeof(int32_t));

            std::vector<uint8_t> content(buffer + sizeof(int32_t),
                                         buffer + recvLen);

            char ipStr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(from.sin_addr), ipStr, INET_ADDRSTRLEN);

            Packet packet(headerType, content, ipStr, ntohs(from.sin_port));

            if (onPacketReceived) {
                onPacketReceived(packet);
            } else {
                packet.print();
            }
        }
    }


    void Socket::send(int32_t headerType, const std::vector<uint8_t>& data,
                      const std::string& ip, uint16_t port) {
        sockaddr_in to{};
        to.sin_family = AF_INET;
        to.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &to.sin_addr);

        std::vector<uint8_t> buffer(sizeof(int32_t) + data.size());
        memcpy(buffer.data(), &headerType, sizeof(int32_t));
        memcpy(buffer.data() + sizeof(int32_t), data.data(), data.size());

        sendto(sock, reinterpret_cast<const char*>(buffer.data()), buffer.size(), 0,
               (sockaddr*)&to, sizeof(to));
    }
}