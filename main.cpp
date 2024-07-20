// udp_client.cpp
#include <iostream>
#include <winsock2.h>
#include<windows.h>  
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
#define SERVER "127.0.0.1"
#define PORT 8888
#define BUFFER_LENGTH 512
//g++ -o udp_client  main.cpp -lws2_32
using namespace std;



  WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char message[BUFFER_LENGTH];

int init()
{
  
    
    cout << "Winsock starting..." << endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cerr << "WSAStartup Error. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }

    
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        cerr << "Socket creating is  failed . Error Code: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER);
    server.sin_port = htons(PORT);
}

int main() {
  

    init();
    cout << "Enter Message: ";
    cin.getline(message, BUFFER_LENGTH);
    while(client_socket!=INVALID_SOCKET)

   { 
      if (_kbhit()) {  // Bir tuşa basıldığını kontrol et
            char ch = _getch();  // Basılan tuşu al
            if (ch == 27) {  // ESC tuşunun ASCII kodu 27'dir
                std::cout << "ESC tuşuna basıldı, döngüden çıkılıyor." << std::endl;
                break;
            }
        }
    
    if (sendto(client_socket, message, strlen(message), 0, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cerr << "sendto is failed. Error Code: " << WSAGetLastError() << endl;
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }
    Sleep(1);
    }

    cout << "Sended Message is : " << message << endl;

    
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
