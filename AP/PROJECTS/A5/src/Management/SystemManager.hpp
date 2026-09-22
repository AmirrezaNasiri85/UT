#pragma once

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "../Objects/People.hpp"
#include "PostManagement.hpp"
#include "DataBase.hpp"
#include "GetManagement.hpp"
#include "Delete.hpp"
#include "PutManagement.hpp"
#include "../Objects/Invitation.hpp"
#include "../Objects/Report.hpp"




class System{
private:
    int report_id = 1;
    Data_base* data_base;
    Post_management* post_manager;
    Get_management* get_manager;
    Invitation_management* invitation_manger;
    Report_management* report_manger;
    Delet_management* delet_manager;
    Put_management* put_management;

public:
    System(Data_base* given_base);
    ~System();
    void add_new_admin(string& username, Admin* new_admin);
    void add_new_player(string& username, Player* new_player);
    void post_functions(vector<string>& orders);
    void get_functions(vector<string>& orders); 
    void delet_functions(vector<string>& orders);  
    void put_functions(vector<string>& orders);
};


