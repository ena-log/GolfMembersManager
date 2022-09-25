#include "MembersEntity.h"
#include <string.h> // == <cstring>

MembersEntity::MembersEntity()
{
    loadMembersInfo();
}

MembersEntity::~MembersEntity()
{

}

void MembersEntity::loadMembersInfo()
{
    fpDBData = fopen("memberLists.bin", "r");

    if(fpDBData == NULL)
    {
        fprintf(stderr, "file open error\n");
        return;
    }

    while(fread(&membersInfo, sizeof(MembersInfo), 1, fpDBData))  
    // fread(&membersInfo, sizeof(membersInfo), 1, fpDBData) : read once
    {
        vecMembersList.push_back(membersInfo);   
    }

    fclose(fpDBData);
}

void MembersEntity::addMembersInfo(MembersInfo member)
{
    vecMembersList.push_back(member);
}

void MembersEntity::makeDBMembersInfo()
{
    // 1. file open
    // 2. vecMemberList의 배열을 하나씩 read
    // 3. vecMemberList값을 file에 vecMemberList 끝까지 write

    fpDBData = fopen("memberLists.bin", "a+");

    if(fpDBData == NULL)
    {
        fprintf(stderr, "file open error\n");
        return;
    }

    for (const auto &member : vecMembersList)
    {
        fwrite(&member, sizeof(member), 1, fpDBData);
    }

    fclose(fpDBData);
}



bool MembersEntity::delMembersInfo(int *cardNum)
{
    std::vector<MembersInfo>::iterator itrMember;

    // begin() : vector의 맨 처음 값의 주소를 줌
    // end() : vector의 맨 마지막 값의 주소를 줌
    for (itrMember = vecMembersList.begin(); itrMember != vecMembersList.end(); itrMember++)
    {
        if(memcmp(itrMember->cardNum, cardNum, sizeof(itrMember->cardNum)) == 0)
        {
            vecMembersList.erase(itrMember);
            return true;
        }
    }
    return false;
}



void MembersEntity::printMembersInfo(int index)
{
    if(index > (int)vecMembersList.size())
    {
        fprintf(stderr, "out of range index\n");
        return ;
    }

    printf("%04d %s %s %s %0x-%0x-%0x-%0x-%0x\n", 
        vecMembersList[index].id,
        vecMembersList[index].name,
        vecMembersList[index].address,
        vecMembersList[index].phoneNumber,
        vecMembersList[index].cardNum[0],
        vecMembersList[index].cardNum[1],
        vecMembersList[index].cardNum[2],
        vecMembersList[index].cardNum[3],
        vecMembersList[index].cardNum[4]);
}

void MembersEntity::printMembersInfo(std::string str_info)
{
    // &member : reference 변수
    for (const auto &member : vecMembersList)
    {
        // c_str() : string -> char
        //strcmp : string compare에서 일치하면 0을 return함
        if (strcmp(member.name, str_info.c_str()) == 0)
        {
            printMembersInfo(member.id);
            return ;
        }

        if (strcmp(member.phoneNumber, str_info.c_str()) == 0)
        {
            printMembersInfo(member.id);
            return ;
        }

        if (strcmp(member.address, str_info.c_str()) == 0)
        {
            printMembersInfo(member.id);
            return ;
        }
    }
}

void MembersEntity::printMembersInfo(int *cardNum)
{
    for (const auto &member : vecMembersList)
    {
        if (memcmp(member.cardNum, cardNum, sizeof(member.cardNum)) == 0)
        {
            printMembersInfo(member.id);
            return ;
        }
    }
}

bool MembersEntity::findMembersInfo(std::string str_info)
{
    for (const auto &member : vecMembersList)
    {
        if (strcmp(member.name, str_info.c_str()) == 0)
            return true;
        if (strcmp(member.phoneNumber, str_info.c_str()) == 0)
            return true;
        if (strcmp(member.address, str_info.c_str()) == 0)
            return true;
    }
    return false;
}

bool MembersEntity::findMembersInfo(int *cardNum)
{
    for (const auto &member : vecMembersList)
    {
        if (memcmp(member.cardNum, cardNum, sizeof(member.cardNum)) == 0)
            return true;
    }
    return false;
}