#include <winsock2.h>
#include <iostream>

int main() {
    WSADATA wsaData;
    WSADATA* ptr = &wsaData;
    int wsaerr = 0;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, ptr);
    if (wsaerr!= 0) {
        std::cout << "The winsock dll not found!" << '\n';
    } else {
        std::cout << "The winsock dll is found!" << '\n';
        std::cout << "The status: " << wsaData.szSystemStatus << '\n';
    }
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "ERROR at socket " << WSAGetLastError() << '\n';
        WSACleanup();
        return 0;
    } else {
        std::cout << "socket is ok!\n";
    }
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "BIND FAILED!\n";
        return 1;
    }
    int err = listen(serverSocket, 5);
    if (err == SOCKET_ERROR) {
        std::cout << "Listen error!\n";
    } else {
        std::cout <<"No error on listen\n";
    }
    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, NULL, NULL); //the arguements should not be null if we want to
    // this step basically is that we want to accept connectiosn via this accept socket
    if (acceptSocket == INVALID_SOCKET) {
        std::cout << "accept socket error!" << WSAGetLastError() << '\n';
        WSACleanup();
        return -1;
    } else {
        std::cout << "successfully accepted a socket connection!\n";
    }
    char rcvBuffer[200]{};
    int byteCount = recv(acceptSocket, rcvBuffer, 200, 0);
    if (byteCount == SOCKET_ERROR) {
        std::cout << "ERROR RECEIVING!\n";
    } else {
        printf("Received %d bytes!\n", byteCount);
    }

    return 0;
}
