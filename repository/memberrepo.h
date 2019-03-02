#ifndef MEMBERREPO_H
#define MEMBERREPO_H

#include "repo.h"
#include "domain/member.h"

class MemberRepo:public Repo
{
public:
    MemberRepo();
    static Member* findByMemberID(int memberID);
    static void saveMember(Member* &member);
};

#endif // MEMBERREPO_H
