#ifndef CARDREADER_H
#define CARDREADER_H

#include <iostream>
#include "mfrc522.h"
#include "DeviceData.h"

#pragma once

class CardReader : public mfrc522
{
private:
    uint8_t rfidData[16];
    DeviceData cardData;

public:
    CardReader(SPI *spi);
    virtual ~CardReader();
    bool isCard();
    DeviceData getCardNumber();

};

#endif