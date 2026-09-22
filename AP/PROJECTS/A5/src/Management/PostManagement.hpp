#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <set>
#include <algorithm>
#include <cctype>
#include <string>
#include "../Objects/People.hpp"
#include "../Objects/Report.hpp"
#include "../Objects/Invitation.hpp"
#include "../Objects/Match.hpp"
#include "Error.hpp"
#include "DataBase.hpp"

using namespace std;


const int REGISTER_XP = 500;


class Post_input{
private:

public:
    void register_extraction(vector<string>& orders);
    void login_extraction(vector<string>& orders);
    void logout_extraction(vector<string>& orders);
    void casual_match_extraction(vector<string>& orders);
    void invitation_extraction(vector<string>& orders);
    void start_match_extraction(vector<string>& orders);
    void reject_invitation_extraction(vector<string>& orders);
    void action_extraction(vector<string>& orders);
    void report_extraction(vector<string>& orders);
    void dismiss_report_extraction(vector<string>& orders);
    void block_extraction(vector<string>& orders);
    void penalty_extraction(vector<string>& orders);
};




class Post_management{
    private:
    Data_base* data;
    Post_input* post_input;
    set<string>post_methods = {
        "register", "login", "logout", "casual_match_ready",
        "invitation", "start_match", "reject_invitation", 
        "report", "action", "dismiss_report", "block", "penalty"
    };

    void add_new_player(string& username, Player* new_player);
    void check_login_role(string& username, string& password);
    void second_check_invitation(vector<string>& orders, Invitation_management* invitation_handeler);
    void start_player_check(int invitation_id);
    void check_start_match(vector<string>& orders);
    void start_match_core(vector<string>& orders);
    void add_progress_match(Player* player_one, Player* player_two, const string& type);
    void check_register(vector<string>& orders);
    void register_core(vector<string>& orders);
    void check_login(vector<string>& orders);
    void login_core(vector<string>& orders);
    void check_logout(vector<string>& orders);
    void logout_core();
    void check_casual_match_ready(vector<string>& orders);
    void casual_match_ready_core(vector<string>& orders);
    void check_invitation(vector<string>& orders, Invitation_management* invitation_handeler);
    void invitation_core(vector<string>& orders, Invitation_management* invitation_handeler);
    void check_rejection(vector<string>& orders);
    void rejection_core(vector<string>& orders);
    void check_report(vector<string>& orders);
    void second_check_report(vector<string>& orders);
    void report_core(vector<string>& orders,Report_management* report_manger);
    void check_action(vector<string>& orders);
    void second_action_check(vector<string>& orders);
    void action_core(vector<string>& orders);
    void check_dissmis_report(vector<string>& orders);
    void dismiss_report_core(vector<string>& orders);
    void check_block(vector<string>& orders);
    void second_check_block(vector<string>& orders);
    void block_core(vector<string>& orders);
    void check_penalty(vector<string>& orders);
    void penalty_parameter_check(vector<string>& orders);
    void penalty_core(vector<string>& orders);
public:
    Post_management(Data_base* data);
    ~Post_management();  
    string find_mathod(vector<string>& orders);  
    void registerr(vector<string>& orders);
    void login(vector<string>& orders);
    void logout(vector<string>& orders);
    void casual_match_ready(vector<string>& orders);
    void invitation(vector<string>& orders, Invitation_management* invitation_handeler);
    void start_match(vector<string>& orders);
    void rejection(vector<string>& orders);
    void report(vector<string>& orders,Report_management* report_manger);
    void action(vector<string>& orders);
    void dismiss_report(vector<string>& orders);
    void block(vector<string>& orders);
    void penalty(vector<string>& orders);
};

void username_password(vector<string>& orders, string& username, string& password);
void username_match_type(vector<string>& orders, string& username, string& match_type);
void username_find(vector<string>& orders, string& username);
void username_reason(vector<string>& orders, string& username, string& report);
void username_status(vector<string>& orders, string& username, string& status);
void penalty_parameter(string& amount, string& type, string& report_id
        , string& number_of_matched, const vector<string>orders);