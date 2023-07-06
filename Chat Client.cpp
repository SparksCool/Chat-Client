#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#include <iostream>
#include <winsock2.h>
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib") // Winsock Library

void server_listen(SOCKET s) {
    char server_reply[2000] = { 0 };

    while (1) {

        // Receive a reply from the server
        memset(server_reply, 0, 2000);
        if (recv(s, server_reply, 2000, 0) < 0) {
            puts("recv failed");
            break;
        }

        printf("%s\n", server_reply);
    }
}

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char message[2000] = { 0 };

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created.\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");

    printf("Enter username : ");
    std::cin.getline(message, 2000);

    if (std::string(message) == "exit") {
        return 0;
    }

    if (send(s, message, strlen(message), 0) < 0)
    {
        puts("Send failed");
        return 1;
    }

    std::thread client_thread(server_listen, s);

    // send some data
    while (1) {
        std::string input;
        std::getline(std::cin, input);
        printf("\033[A\033[2K");

        if (send(s, input.c_str(), input.size(), 0) < 0) {
            puts("Send failed");
            return 1;
        }

        Sleep(1);
    }


    closesocket(s);
    WSACleanup();

    return 0;
}