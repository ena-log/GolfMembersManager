#include <iostream>
#include <thread>
#include <cstring>
#include <wiringPi.h>

#include "Listener.h"
#include "Controller.h"
#include "MembersManageService.h"
#include "ComDev.h"
#include "tcpServer.h"
#include "I2C.h"
#include "LCD.h"
#include "View.h"

#include "GolfMembersManager.h"
#include "MembersEntity.h"


void serverThread(tcpServer *server)
{
    char recvBuff[BUFSIZ];
    int recvLen;

    while (server->waitAccept() > 0)
    {
        server->setClientState(true);
        while((recvLen = server->recvData(recvBuff, sizeof(recvBuff))) > 0)
        {
            recvBuff[recvLen] = '\0';
            server->sendData(recvBuff, recvLen);
            printf("received : %s\n", recvBuff);
        }
        server->closeSocket(server->getClientSocket());
        server->setClientState(false);
        printf("close client socket\n");
    }
}

int main(void)
{
    tcpServer *cardTcpServer = new tcpServer(5100);
    ComDev *comDev = new ComDev(cardTcpServer);
    LCD *lcd = new LCD(new I2C("/dev/i2c-1", 0x27));
    View *view = new View(lcd);
    MembersManageService *membersManagerService = new MembersManageService(comDev, view);
    Controller *controller = new Controller(membersManagerService);
    Listener *listener = new Listener(controller);
    
     std::thread threadFunc(serverThread, cardTcpServer);

    while(1)
    {
        listener->checkEvent();
        delay(50);
    }

    // GolfMembersManager golfMembersManger;

    // golfMembersManger.run();

    return 0;

    //file db test
    /*
    MembersEntity  membersEntity;

    printf("===== Test : print member =====\n");
    membersEntity.printMembersInfo(10);
    membersEntity.printMembersInfo(150);
    membersEntity.printMembersInfo(200);
    membersEntity.printMembersInfo(2000);
    printf("\n");


    printf("===== Test : find member =====\n");
    membersEntity.printMembersInfo("forijpsgu");
    if (membersEntity.findMembersInfo("forijpsgu"))     printf("forijpsgu : found the name\n");
    else                                                printf("forijpsgu : not found the name\n");
    
    if (membersEntity.findMembersInfo("gongongon"))    printf("gongongon : found the name\n");
    else                                               printf("gongongon : not found the name\n");

    int cardNumber1[5] = {0xba, 0x1a, 0x62, 0x3b, 0x75};
    int cardNumber2[5] = {0x11, 0x11, 0x11, 0x11, 011};
    membersEntity.printMembersInfo(cardNumber1);
    membersEntity.printMembersInfo(cardNumber2);
    if (membersEntity.findMembersInfo(cardNumber1))     printf("cardNumber1: found the card Number\n");
    else                                                printf("cardNumber1 : not found the card Number\n");
    if (membersEntity.findMembersInfo(cardNumber2))    printf("cardNumber2 : found the card Number\n");
    else                                               printf("cardNumber2 : not found the card Number\n");
    printf("\n");


    printf("===== Test : add member =====\n");
    MembersInfo member;
    member.id = 100000;
    strcpy(member.name, "HongGilDong");
    strcpy(member.address, "ABCapt. 101dong-123ho");
    strcpy(member.phoneNumber, "010-1234-1234");
    int num[5] = {0x12,0x12,0x12,0x12,0x12};
    memcpy(member.cardNum, num, sizeof(num));
    // MembersInfo member = {100000, "hahaha", "ABCapt. 101dong-123ho", "010-1234-1234", {0x12,0x12,0x12,0x12,0x12}};
    membersEntity.addMembersInfo(member);
    membersEntity.printMembersInfo(100000);
    membersEntity.printMembersInfo("HongGilDong");
    if (membersEntity.findMembersInfo("HongGilDong"))     printf("HongGilDong : found the name\n");
    else                                                  printf("HongGilDong : not found the name\n");
    membersEntity.printMembersInfo(num);
    if (membersEntity.findMembersInfo(num))     printf("num: found the card Number\n");
    else                                        printf("num : not found the card Number\n");
    printf("\n");


    printf("===== Test : delete member =====\n");
    membersEntity.printMembersInfo(200);
    if (membersEntity.delMembersInfo(cardNumber1))     printf("DELETE\n");
    else                                               printf("ERROR\n");
    membersEntity.p rintMembersInfo(200);
    */

    //rfid test
    /* 
    uint8_t byte;
    uint8_t str[MAX_LEN];
    byte = 0x55; // just to check that byte is getting loaded and printed
    delay(1500);

    // check version of the reader
    byte = rfid.mfrc522_read(VersionReg);

    printf("ver --> %0x\n", byte);
    if (byte == 0x92)
    {
        printf("MIFARE RC522v2\r\n");
        printf("Detected\r\n");
    }
    else if (byte == 0x91 || byte == 0x90)
    {
        printf("MIFARE RC522v1\r\n");
        printf("Detected\r\n");
    }
    else
    {
        printf("No reader found\r\n");
    }

    while (1)
    {
        byte = rfid.mfrc522_request(PICC_REQALL, str);
        printf("byte-->%d ", byte);
        if (byte == CARD_FOUND)
        {
            for (int i = 0; i < MAX_LEN; i++)
                str[i] = ' ';
            byte = rfid.mfrc522_get_card_serial(str);

            for (int i = 0; i < 5; i++)
                printf("%02x ", str[i]);
            printf("\n");
        }
        delay(1000);
        printf("hihi\n");
    } */
}
