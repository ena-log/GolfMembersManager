#ifndef MONITOR_H
#define MONITOR_H

#include <iostream>

#pragma once

class Monitor
{
private:

public:
    Monitor();
    ~Monitor();
    void print(uint8_t *data, int size);

};

#endif