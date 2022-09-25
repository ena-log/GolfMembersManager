#ifndef __VIEW_H__
#define __VIEW_H__

#include <string>
#include "LCD.h"


class View
{
private:
    struct tm timeDate;
    LCD *lcd;

public:
    View(LCD *lcd);
    virtual ~View();
    void initDisplay();
    void printModeDisplay(int managerState);
    void printStateDisplay(int state);
    void printCardRegistoredDisplay(std::string name);
    void printInfoDisplay(std::string searchData);
    void updateTime(struct tm *timeData);
};

#endif /* __VIEW_H__ */