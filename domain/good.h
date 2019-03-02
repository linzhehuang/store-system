#ifndef GOOD_H
#define GOOD_H

#include <string>
using namespace std;

class Good
{
public:
    Good(string id, string name, double price);
    string id, name;
    double price;
};

#endif // GOOD_H
