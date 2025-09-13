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
int main(int argc, char** argv) {
    WSADATA wsaData;
    int iResult;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL, * ptr = NULL, hints;
    char sendbuf[DEFAULT_BUFLEN];
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <server IP address>\n";
        return 1;
    }
    //Инициализация Winsock на стороне клиента и создание сокета
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }
    //Настройка параметров подключения. Заполнение структуры для настройки сокета.
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return 1;
    }
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return 1;
        }
        //Подключение к серверу.Клиент пытается подключиться к серверу через цикл поиска доступного адреса.
        iResult = connect(ConnectSocket, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);
    if (ConnectSocket == INVALID_SOCKET) {
        std::cerr << "Unable to connect to server! Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    //Отправка и получение данных.Клиент отправляет сообщение серверу и ожидает ответа.
    while (true) {
        // Get user input and send to the server
        std::cout << "Enter message to send to server: ";
        std::cin.getline(sendbuf, sizeof(sendbuf));
        iResult = send(ConnectSocket, sendbuf, strlen(sendbuf), 0);
        if (iResult == SOCKET_ERROR) {
            std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }
        // Receive message from the server
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            recvbuf[iResult] = '\0'; // Null-terminate the received data
            std::cout << "Received message from server: " << recvbuf << std::endl;
        }
        else if (iResult == 0) {
            std::cout << "Connection closed by server\n";
            break;
        }
        else {
            std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }
    };
    //Освобождение ресурсов клиента после завершения работы.
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}
