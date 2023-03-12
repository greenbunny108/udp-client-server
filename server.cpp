#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <cstring>

int main(int argc, char const *argv[]) {
    char buffer[1024];
    const char *hello = "Hello from server";

    int port = atoi(argv[1]);

    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);


    struct sockaddr_in serverAddress, clientAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int bindStatus = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    socklen_t length;
    size_t n;
    length = sizeof(clientAddress);
    n = recvfrom(serverSocket, (char *)buffer, 1024,MSG_WAITALL, ( struct sockaddr *) &clientAddress,&length);
    buffer[n] = '\0';

    printf("Client : %s\n", buffer);
    sendto(serverSocket, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &clientAddress,length);
    std::cout<<"Hello message sent."<<std::endl;

    return 0;
}