#pragma once

#include <iostream>

using namespace std;

struct Request{
    string username;
    string company_name;
    int shares_count;
    int price;
    int request_id;
    bool is_selling;
};

bool sort_request_greater(const Request* a, const Request* b);

bool sort_request_lesser(const Request* a, const Request* b);