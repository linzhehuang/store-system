#ifndef IDENTITYVALIDATOR_H
#define IDENTITYVALIDATOR_H

#include <string>
#include "dbutil.h"
#include "global.h"

class IdentityManager
{
public:
    static bool validate(int id, int password, int type);
    static void addNewUser(int id,int password,int type);
    static void deleteUser(int id,int type);
private:
    IdentityManager();
    static DBUtil* dbUtil;
};

#endif // IDENTITYVALIDATOR_H
