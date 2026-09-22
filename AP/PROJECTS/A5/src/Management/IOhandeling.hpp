#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "SystemManager.hpp"
#include "DataBase.hpp"

using namespace std;

void process_orders(System& managment);

vector<string> seperate_orders(const string& orders);

string find_line(vector<string>orders);