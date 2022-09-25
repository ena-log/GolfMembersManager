#ifndef MEMBERSMANAGESERVICE_H
#define MEMBERSMANAGESERVICE_H

#include <time.h>

#include "MembersEntity.h"
#include "MembersInfo.h"
#include "ComDev.h"
#include "View.h"

#pragma once

// 카드 확인, 카드 등록, 카드 삭제, 정보 검색
enum {CARD_READER, CARD_REGISTER, CARD_DELETE, SEARCH};  

class MembersManageService
{
private:
    int membersManagerState;
    MembersEntity *membersEntity;
    ComDev *comDev;
    View *view;
    time_t curTime;

public:
    MembersManageService(ComDev *comDev, View *view);
    virtual ~MembersManageService();
    void setComDev(ComDev *comDev);
    void updateStateEvent(std::string devName);
    void checkCardNumber(int *cardNum);
    void searchMembersInfo();
    void updateEvent();
};

#endif