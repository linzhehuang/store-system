#include "member.h"

Member::Member(int id)
{
    this->id = id;
}

double Member::discount(double amount)
{
    return amount*0.9;
}
