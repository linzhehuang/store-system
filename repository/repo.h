#ifndef REPO_H
#define REPO_H

#include <vector>
#include "global.h"
#include "util/dbutil.h"

class Repo
{
public:
    Repo();
protected:
    static DBUtil* dbUtil;
};

#endif // REPO_H
