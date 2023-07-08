#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <winsock2.h>
#include <string>
#include <thread>
#include "ChatClient.h"
#include "AccountPrompt.h"
#include <vector>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "json.hpp"


#pragma comment(lib, "ws2_32.lib") // Winsock Library

using namespace System::Windows::Forms;
using namespace System;
using json = nlohmann::json;

std::vector<std::string> messageVec;
std::string username;
SOCKET serverSocket;
struct sockaddr_in server;
bool authenticated = false;



    
    void setAuthenticated(bool value) {
        authenticated = true;
    }

    void sendMessage(std::string message) {
        json j;
        j["type"] = "message";
        j["user"] = username;
        j["content"] = message;

        if (send(serverSocket, j.dump().c_str(), j.dump().size(), 0) < 0) {
            puts("Send failed");
            return;
        }
    }

    void setName(std::string message) {
        json j;
        j["type"] = "nameupdate";
        j["content"] = message;
        username = message;

        if (send(serverSocket, j.dump().c_str(), j.dump().size(), 0) < 0) {
            puts("Send failed");
            return;
        }
    }

    void recieveMessage(std::string message) {
        messageVec.push_back(message);
    }

    std::vector<std::string> getMessageList() {
        std::vector<std::string> messages = messageVec;
        messageVec.clear();
        return messages;
    }

    void server_listen() {
        char server_reply[2000] = { 0 };

        while (1) {

            // Receive a reply from the server
            memset(server_reply, 0, 2000);
            if (recv(serverSocket, server_reply, 2000, 0) < 0) {
                puts("recv failed");
                break;
            }

            recieveMessage(server_reply);
        }
    }

    int initalizeConnection() {
        WSADATA wsa;
        char message[2000] = { 0 };

        printf("\nInitialising Winsock...");
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        {
            printf("Failed. Error Code : %d", WSAGetLastError());
            return 1;
        }

        printf("Initialised.\n");

        if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        {
            printf("Could not create socket : %d", WSAGetLastError());
        }

        printf("Socket created.\n");

        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_family = AF_INET;
        server.sin_port = htons(8080);

        if (connect(serverSocket, (struct sockaddr*)&server, sizeof(server)) < 0)
        {
            puts("connect error");
            return 1;
        }

        puts("Connected");

        server_listen();

        closesocket(serverSocket);
        WSACleanup();

        return 0;
    }


    int WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {


        std::thread connection_thread(initalizeConnection);

        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);
        Application::Run(gcnew ChatClient::AccountPromptGUI());
        if (authenticated) {
            Application::Run(gcnew ChatClient::ClientGUI());
        }
        return 0;
    }
