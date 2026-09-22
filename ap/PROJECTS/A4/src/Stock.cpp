#include "Stock.hpp"

Stock::Stock(int count, const string &name, Company *base)
    : count(count), name(name), base(base)
{
}

bool Compare::operator()(const Stock *a, const Stock *b) const
{
    return a->name < b->name;
}