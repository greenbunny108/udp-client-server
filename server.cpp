#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {
    char buffer[MAX_BUFFER_SIZE];
    int port = atoi(argv[1]);

    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    struct sockaddr_in serverAddress, clientAddress;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    int bindStatus = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if(bindStatus < 0) {
        std::cerr<<"Failed to bind socket to port "<< port <<std::endl;
        return 1;
    }

    std::cout<<"UDP server listening on port "<< port <<std::endl;

    size_t len = sizeof(clientAddress);
    while(true){
        int recvBytes = recvfrom(serverSocket, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&clientAddress, (socklen_t *)&len);
        if(recvBytes < 0){
            std::cerr<<"Failed to receive data"<<std::endl;
            return 1;
        }
        buffer[recvBytes] = '\0';
        std::cout << "Received data from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << ": " << buffer << std::endl;

        std::string response = "Server response";
        if(sendto(serverSocket, response.c_str(), response.length(), 0, (struct sockaddr *)&clientAddress, len) < 0){
            std::cerr<<"Failed to send data"<<std::endl;
            return 1;
        }
    }

    close(serverSocket);
    return 0;
}