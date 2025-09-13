//реализация клиент-серверного общения с использованием сокетов на Windows.
#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h> // заголовок для работы с сокетами
#include <ws2tcpip.h> // вспомогательные функции для работы с IP
#pragma comment(lib, "Ws2_32.lib") // подключение библиотеки Windows Sockets
#define DEFAULT_BUFLEN 512 // размер буфера для передачи данных(для отправки и получения)
#define DEFAULT_PORT "5000" // порт, на котором сервер будет принимать подключение/соединение
int main() {
    //переменные для управления сокетами и для буфера передачи данных.
    WSADATA wsaData;
    int iResult;
    SOCKET ListenSocket = INVALID_SOCKET; //сокет для прослушивания
    SOCKET ClientSocket = INVALID_SOCKET; //сокет для клиента
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN];
    //инициализация Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }
    //настройка параметров сокета
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; //для использования IPv4.
    hints.ai_socktype = SOCK_STREAM; //для установления соединений по TCP.
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE; //для назначения адреса сокета, чтобы сервер мог принимать входящие соединения.
    //получение информации о сервере, для последующего использования в вызовах сокетных функций
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return 1;
    }
    //создание сокета для прослушивания входящих соединений.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    //привязка сокета к конкретному IP-адресу и порту
    iResult = bind(ListenSocket, result->ai_addr, static_cast<int>(result->ai_addrlen));
    if (iResult == SOCKET_ERROR) {
        std::cerr << "bind failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);
    //прослушивание входящих соединений
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "Server listening on port " << DEFAULT_PORT << "...\n";
    //сервер принимает входящее соединение от клиента и создает новый сокет для общения с ним.
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    closesocket(ListenSocket);
    //Обработка сообщений. Цикл для получения и отправки сообщений от/к клиенту.
    while (true) {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            recvbuf[iResult] = '\0'; // Null-terminate the received data
            std::cout << "Received message from client: " << recvbuf << std::endl;
            // Get user input and send to the client
            std::cout << "Enter message to send to client: ";
            std::cin.getline(recvbuf, sizeof(recvbuf));
            iResult = send(ClientSocket, recvbuf, strlen(recvbuf), 0);
            if (iResult == SOCKET_ERROR) {
                std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
        }
        else if (iResult == 0) {
            std::cout << "Connection closed by client\n";
            break;
        }
        else {
            std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
    };
    //Завершение соединения и передачи данных, освобождение ресурсов.
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "shutdown failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }
    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}
