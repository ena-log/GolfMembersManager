#ifndef LISTENER_H
#define LISTENER_H

#include "Controller.h"
#include "CardReader.h"
#include "ManageButton.h"

#pragma once

class Listener
{
private:
    CardReader *rfid;
    ManageButton *modeButton;
    uint8_t rfidData[16];
    Controller *controller;

public:
    Listener(Controller *controller);
    virtual ~Listener();
    void checkEvent();
    bool checkRfid();
};

#endif