#pragma once


#include <iostream>
#include <set>
#include <vector>
#include <string>


using namespace std;

class Put_management{
private:
    set<string>put_methods = {};
public:
    string find_mathod(vector<string>& orders);
};
