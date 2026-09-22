#pragma once

#include <set>
#include <iostream>
#include "Stock.hpp"
#include "Company.hpp"

using namespace std;

class Stockholder
{
private:
    string name;
    int free_credit;
    int locked_credit = 0;
    set<Stock *, Compare> free_stokcs;
    set<Stock *, Compare> locked_Stock;

public:
    Stockholder(const string &name, int free_credit, set<Stock *, Compare>&stocks);
    int cal_free_assert();
    void print_portfilo();
    void print_free_shares();
    void print_lock_shares();
    void lock_money(const int money);
    void buy_finance(const int money, Request *request, Company *company);
    void cancel_buy_finance(const int money);
    void sell_finance(const int money, Request *request);
    void cancel_sell_finance(const int money, Request *request);
    void lock_shares(Request *request, Company *company);
    void erase_free_stock(Stock *deleted);
    void earse_lock_shares(Stock *deleted);
    bool buy_validation(const Request *request);
    bool sell_validation(const Request *request);
    void free_free_stocks();
    void free_lock_stocks();
    void total_free();
};
