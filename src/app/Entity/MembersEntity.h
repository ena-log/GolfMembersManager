#ifndef MEMBERSENTITY_H
#define MEMBERSENTITY_H

#include <vector>
#include <iostream>
#include <string>
#include "MembersInfo.h"

#pragma once

class MembersEntity
{
private:
    std::vector<MembersInfo> vecMembersList;
    MembersInfo membersInfo;
    FILE *fpDBData; //file data의 point 변수

public:
    MembersEntity();
    virtual ~MembersEntity();
    
    void loadMembersInfo();
    void addMembersInfo(MembersInfo member);
    bool delMembersInfo(int *cardNum);
    void makeDBMembersInfo();

    void printMembersInfo(int index);
    void printMembersInfo(std::string str_info);
    void printMembersInfo(int *cardNum);
    bool findMembersInfo(std::string str_info);
    bool findMembersInfo(int *cardNum);
    
};

#endif