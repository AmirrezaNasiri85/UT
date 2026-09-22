#pragma once

#include <iostream>
#include <string>
#include <list>
#include "Request.hpp"



using namespace std;

class Company{
private:
    string name;
    int price;
    list<Request*>buys;
    list<Request*>sells;

public:
    Company(const string& name, int price);
    int get_price();
    void print_company_info();
    void print_sells();
    void print_buys();
    bool buy_validation(const string& username);
    bool request_buys_existance(Request* requesr);
    Request* find_sells_request(Request* request);
    Request* buy_match(Request* request);
    void erase_sells_request(Request* request);
    void erase_buy_request(Request* request);
    void change_price(const int money);
    Request* find_buy_request(Request* Request);
    Request* sell_match(Request* request);
    void remove_request(Request* request);
};