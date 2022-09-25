#ifndef COMDEV_H
#define COMDEV_H

#include "tcpServer.h"

#pragma once

class ComDev
{
private:
    tcpServer *cardTcpServer;

public:
    ComDev(tcpServer *server);
    virtual ~ComDev();
    void sendData(int *cardNum);

};

#endif