// udp_server.cpp
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 8888
#define BUFFER_LENGTH 512
//g++ -o udp_server  server.cpp -lws2_32
int main() {
    WSADATA wsa;
    SOCKET server_socket;
    struct sockaddr_in server, client;
    int client_len, recv_len;
    char buffer[BUFFER_LENGTH];

    // Winsock başlat
    std::cout << "Winsock Starting..." << std::endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup is failed. Error Code: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Socket oluştur
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creating is failed. Error Code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Sunucu adres ve port ayarları
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Socket'i bağla
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Bind Error. Error Code: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is ready , listening..." << std::endl;

    client_len = sizeof(struct sockaddr_in);

    // Gelen veriyi al
    while ((recv_len = recvfrom(server_socket, buffer, BUFFER_LENGTH, 0, (struct sockaddr*)&client, &client_len)) != SOCKET_ERROR) {
        buffer[recv_len] = '\0';  // Gelen veriyi null-terminator ile sonlandır
        std::cout << "Received message: " << buffer << std::endl;
    }

    if (recv_len == SOCKET_ERROR) {
        std::cerr << "recvfrom is failed. Error Code: " << WSAGetLastError() << std::endl;
    }

    // Temizle ve kapat
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
