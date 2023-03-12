#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>



int main(int argc, char const *argv[]) {

    char buffer[1024];
    const char *hello = "Hello from client";
    int port = atoi(argv[1]);
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len;

    sendto(clientSocket, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &serverAddress,sizeof(serverAddress));
    std::cout<<"Hello message sent."<<std::endl;

    n = recvfrom(clientSocket, (char *)buffer, 1024,MSG_WAITALL, (struct sockaddr *) &serverAddress, &len);
    buffer[n] = '\0';
    std::cout << "Server :" << buffer << std::endl;

    close(clientSocket);
    return 0;

}