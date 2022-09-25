#include "ComDev.h"
#include <thread>
/* 
void serverThread(tcpServer *server)
{
    char recvBuff[BUFSIZ];
    int recvLen;

    server->setClientState(true);
    while(server->waitAccept() > 0)
    {
        while((recvLen = server->recvData(recvBuff, sizeof(recvBuff))) >= 0)
        {
            recvBuff[recvLen] = '\0';
            server->sendData(recvBuff, recvLen);
            printf("receieved : %s\n", recvBuff);
        }
        server->closeSocket(server->getClientSocket());
        server->setClientState(false);

        printf("close client socket\n");
    }
} */

ComDev::ComDev(tcpServer *server)
{
    // cardTcpServer = new tcpServer(5100);
    // std::thread threadFunc(serverThread, cardTcpServer);
    cardTcpServer = server;
}

ComDev::~ComDev()
{
    delete cardTcpServer;
}

void ComDev::sendData(int *cardNum)
{
    char sendBuff[1000];
    sprintf(sendBuff, "%02x-%02x-%02x-%02x-%02x", 
        cardNum[0], cardNum[1], cardNum[2], cardNum[3], cardNum[4]);
    cardTcpServer->sendData(sendBuff, strlen(sendBuff));
}