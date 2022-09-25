#include "View.h"
#include <wiringPi.h>

View::View(LCD *lcd)
{
    this->lcd = lcd;
    initDisplay();
}

View::~View()
{

}

void View::initDisplay()
{
    char buff[30];
    sprintf(buff, "GOLF MEMBERS");
    lcd->WriteStringXY(0,0, buff);
    sprintf(buff, "MANAGEMENT");
    lcd->WriteStringXY(1,0, buff);
}

void View::printModeDisplay(int managerState)
{
    char buff1[30];
    char buff2[30];

    if(managerState == 0)    //CARD_READER
    {
        printf("changed to card reader state\n");
        sprintf(buff1, "READ CARD    ");
    }
    else if(managerState == 1)    //CARD_REGISTER
    {
        printf("changed to card register state\n");
        sprintf(buff1, "REGISTER CARD");
    }
    else if(managerState == 2)    //CARD_DELETE
    {
        printf("changed to card delete state\n");
        sprintf(buff1, "DELETE CARD    ");
    }
    else if(managerState == 3)    //SEARCH
    {
        printf("changed to search information state\n");
        sprintf(buff1, "SEARCH INFO    ");
    }

    sprintf(buff2, "                ");

    lcd->WriteStringXY(0,0, buff1);
    lcd->WriteStringXY(1,0, buff2);
}

void View::printStateDisplay(int state)
{
    char buff[30];

    if(state == -1)    //CARD_REGISTER, SEARCH : input
    {
        sprintf(buff, "                ");
    }
    if(state == 0)    //CARD_REGISTER, SEARCH : input
    {
        sprintf(buff, "TYPING ...      ");
    }
    if(state == 1)    //CARD_READER : registered
    {
        printf("registered member!\n");
        sprintf(buff, "registered!     ");
    }
    if(state == 2)    //CARD_READER : not registered
    {
        printf("not registered member!\n");
        sprintf(buff, "not registered  ");
    }
    
    if(state == 5)    //CARD_SEARCH : not find
    {
        printf("not find member!\n");
        sprintf(buff, "not find member! ");
    }
    if(state == 6)    //CARD_DELETE : delete
    {
        printf("delete member!\n");
        sprintf(buff, "delete member! ");
    }
    if(state == 7)    //CARD_DELETE : not delete
    {
        printf("not find delete member!\n");
        sprintf(buff, "not find member! ");
    }

    lcd->WriteStringXY(1,0, buff);
}

void View::printCardRegistoredDisplay(std::string name)
{
    //CARD_REGISTER : register
    char buff[30];

    printf("register %s member!\n", name.c_str());
    sprintf(buff, "register %s", name.c_str());
    lcd->WriteStringXY(1,0, buff);
}

void View::printInfoDisplay(std::string searchData) //CARD_SEARCH : find
{
    char buff[30];

    printf("find member : %s \n", searchData.c_str());
    sprintf(buff, "%s           ", searchData.c_str());
    lcd->WriteStringXY(1,0, buff);
    delay(1000);
}

void View::updateTime(struct tm *timeData)
{
    char buff[30];
    printf("register time : %02d:%02d:%02d\n", timeData->tm_hour, timeData->tm_min, timeData->tm_sec);
    sprintf(buff, "%02d:%02d:%02d          ", 
        timeData->tm_hour, timeData->tm_min, timeData->tm_sec);
    lcd->WriteStringXY(1,0, buff);
    delay(1000);

    printStateDisplay(-1);

}
