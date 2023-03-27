#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <cstring>


#define MAX_BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {

    char buffer[MAX_BUFFER_SIZE];


    int port = atoi(argv[1]);
    std::string ip = argv[2];
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    struct sockaddr_in serverAddress;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddress.sin_addr);

    std::string message;

    while (getline(std::cin, message)) {
        if (sendto(clientSocket, message.c_str(), message.length(), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
            std::cerr << "Failed to send data" << std::endl;
            return 1;
        }
    }

    return 0;
}