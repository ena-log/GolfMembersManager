#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Monitor.h"
#include "DeviceData.h"
#include "MembersManageService.h"

#pragma once

class Controller
{
private:
    Monitor *monitor;
    MembersManageService *membersManageService;

public:
    Controller(MembersManageService *membersManageService);
    virtual ~Controller();
    void updateEvent(DeviceData data);

};

#endif