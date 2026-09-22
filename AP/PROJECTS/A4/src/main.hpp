#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Request.hpp"
#include "Stockholder.hpp"
#include "System.hpp"
#include "Company.hpp"
#include "Stock.hpp"


using namespace std;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string REST = "\033[0m";
const string PURPLE = "\033[35m";




struct Input{
    string user_name;
    int free_credit;
    int id;
};