#include "GolfMembersManager.h"

GolfMembersManager::GolfMembersManager()
{
    //rfid = new mfrc522(new SPI(10, 3000000))
    // listener = new Listener();
}

GolfMembersManager::~GolfMembersManager()
{

}

void GolfMembersManager::run()
{
    while(1)
    {
        listener->checkEvent();
        delay(10);
    }
}