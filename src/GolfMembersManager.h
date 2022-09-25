#ifndef GOLFMEMBERSMANAGER_H
#define GOLFMEMBERSMANAGER_H

#include "Listener.h"

#pragma once

class GolfMembersManager
{
private:
    Listener *listener;

public:
    GolfMembersManager();
    ~GolfMembersManager();
    void run();

};

#endif