#include "MembersManageService.h"
#include <wiringPi.h>
#include <string.h>

MembersManageService::MembersManageService(ComDev *comDev,View *view)
{
    membersEntity = new MembersEntity();
    membersManagerState = SEARCH;
    this->comDev = comDev;
    this->view = view;
    curTime = 0;
}

MembersManageService::~MembersManageService()
{

}

void MembersManageService::setComDev(ComDev *comDev)
{
    this->comDev = comDev;
}

void MembersManageService::updateStateEvent(std::string devName)
{
    switch(membersManagerState)
    {
        case CARD_READER:
            if(devName == "modeButton")
            {
                membersManagerState = CARD_REGISTER;
                view->printModeDisplay(membersManagerState);
            }

        break;

        case CARD_REGISTER:
            if(devName == "modeButton")
            {
                membersManagerState = CARD_DELETE;
                view->printModeDisplay(membersManagerState);
            }
        break;

        case CARD_DELETE:
            if(devName == "modeButton")
            {
                membersManagerState = SEARCH;
                view->printModeDisplay(membersManagerState);
                searchMembersInfo();
            }
        break;

        case SEARCH:
            if(devName == "modeButton")
            {
                membersManagerState = CARD_READER;
                view->printModeDisplay(membersManagerState);
            }
        break;
    }
    // view->printModeDisplay(membersManagerState);
    
}

void MembersManageService::checkCardNumber(int *cardNum)
{
    
    switch(membersManagerState)
    {
        //note : id 자동 증가 , vector end() 값으로 가져오기
        static int id = 100000;
        char name[20];
        char address[40];
        char phoneNumber[15];

        case CARD_READER:
            if(membersEntity->findMembersInfo(cardNum))
            {
                view->printStateDisplay(1);
                membersEntity->printMembersInfo(cardNum);
                comDev->sendData(cardNum);
            }
            else
            {
                view->printStateDisplay(2);
            }
        break;

        case CARD_REGISTER:
            view->printStateDisplay(0);
            std::cout << "Name : ";
            std::cin.getline(name, 20);
            std::cout << "Address : ";
            std::cin.getline(address, 40);
            std::cout << "Phone Number : ";
            std::cin.getline(phoneNumber, 15);

            MembersInfo tempMember;
            tempMember.id = id;
            id++;

            strcpy(tempMember.name, name);
            strcpy(tempMember.address, address);
            strcpy(tempMember.phoneNumber, phoneNumber);
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
            
            membersEntity->addMembersInfo(tempMember);
            view->printCardRegistoredDisplay(tempMember.name);
            delay(1000);
            updateEvent();

        break;

        case CARD_DELETE:
            if(membersEntity->findMembersInfo(cardNum))
            {
                membersEntity->delMembersInfo(cardNum);
                view->printStateDisplay(6);
            }
            else
            {
                view->printStateDisplay(7);
            }
        break;
    }
}

void MembersManageService::searchMembersInfo()
{
    //이름, 전화번호, 주소
    char searchData[40];
    
    while(1)
    {
        view->printStateDisplay(0);
        std::cout << "Name, Phone Number, Address : ";
        std::cin.getline(searchData, 40);

        if (strcmp(searchData, "exit")==0)
        {
            view->printStateDisplay(-1);
            break ;
        }
        else
        {
            if(membersEntity->findMembersInfo(searchData))
            {
                view->printInfoDisplay(searchData);
                membersEntity->printMembersInfo(searchData);
            }
            else
            {
                view->printStateDisplay(5);
                delay(1000);
            }

        }

    }

}

void MembersManageService::updateEvent()
{
    curTime = time(NULL);
    struct tm *timeDate = localtime(&curTime);
    view->updateTime(timeDate);
}