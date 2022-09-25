#include "ManageButton.h"

ManageButton::ManageButton(int pin, std::string name)
    : Button(pin)
{
    buttonData.devName = name;
}

ManageButton::~ManageButton()
{

}

bool ManageButton::checkButton()
{
    if (getState() == RELEASE_ACTIVE)
    {
        // printf("나와라 얏");
        return true;
    }
    
    return false;

}

DeviceData ManageButton::getButtonData()
{
    // buttonData.devName = "ModeButton";
    buttonData.devData.clear();
    buttonData.devData.push_back(1);    // nothing meaning

    return buttonData;
}