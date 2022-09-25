#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#pragma once

class tcpServer
{
private:

    int serverSock_fd;  //server socket file disk
    int clientSock_fd;  //client socket file disk
    int portNum;        //server port number
    bool clientState;
    
    // 제공되는 구조체 sockaddr_in 
    struct sockaddr_in serv_addr;    //server address
    struct sockaddr_in client_addr;  //client address
    socklen_t clnt_addr_size;


public:
    tcpServer(int port);
    ~tcpServer();
    int getClientSocket();
    int getServerSocket();
    bool getClientState();
    void setClientState(bool state);
    void createSocket();
    int waitAccept();
    int recvData(char *recvBuff, size_t size);
    int sendData(char *sendBuff, size_t size);
    void closeSocket(int socket);

};

#endif