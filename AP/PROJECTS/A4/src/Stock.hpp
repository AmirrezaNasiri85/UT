#pragma once

#include <iostream>
#include "Company.hpp"

using namespace std;

struct Stock
{
    int count;
    string name;
    Company *base;
    Stock(int count, const string &name, Company *base);
};

struct Compare
{
    bool operator()(const Stock *a, const Stock *b) const;
};
