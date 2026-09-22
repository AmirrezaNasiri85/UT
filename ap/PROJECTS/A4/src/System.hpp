#pragma once

#include <iostream>
#include <map>
#include "Stockholder.hpp"
#include "Company.hpp"


class System{
private:
    int request_id = 1;
    list<Request*>requests;
    map<string, Company*> companies;
    map<string, Stockholder*>stockholders;

public:

    void add_stockholder(Stockholder* new_stockholder, const string& name);
    void add_Company(Company* new_company, const string& name);
    bool username_existance(const string& username);
    Company* find_company(const string& name);
    Stockholder* find_stockholder(const string& username);
    void allocate_request_id(Request* request);
    void transfer(Stockholder* buyer, Stockholder* seller, Request* request, Company* company);
    void add_request(Request* request);
    void remove_request(Request* request);
    Request* find_request(const int id);
    void free_company();
    void free_stockholder();
    void free_requests();
    void total_free();
};