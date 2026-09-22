#pragma once

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Delet_management{
private:
    set<string> delet_method = {};
public:
    string find_mathod(vector<string>& orders);
};

