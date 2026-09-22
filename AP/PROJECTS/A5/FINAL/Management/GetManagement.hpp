#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include "../Objects/People.hpp"
#include "Error.hpp"
#include "DataBase.hpp"

using namespace std;

class Get_input{
private:
    
public:
    void casual_match_opponents_extraction(vector<string>& orders);
    void profile_extraction(vector<string>& orders);
    void received_invitation_extraction(vector<string>& orders);
    void reports_extraction(vector<string>& orders);
    void match_status_extraction(vector<string>& orders);
    void ranked_match_opponents_extraction(vector<string>& orders);
};



class Get_management{
    private:
    Get_input* get_input;
    Data_base* data;
    set<string>get_methods = {
        "casual_match_opponents", "profile", "received_invitations",
        "reports", "match_status", "ranked_match_opponents"
    };

    void second_layer_match_check();
    void check_casual_match_opponents(vector<string>& orders);
    void casual_match_opponents_core(vector<string>& orders);
    void check_profile(vector<string>& orders);
    void profile_core(vector<string>& orders);
    void check_received_invitations(vector<string>& orders);
    void received_invitations_core();
    void check_reports(vector<string>& orders);
    void reports_core();
    void check_match_status(vector<string>& orders);
    void match_status_core();
    void check_ranked_match_opponents(vector<string>& orders);
    void ranked_match_opponents_core(vector<string>& orders);
public:
    Get_management(Data_base* given_base);
    ~Get_management();
    string find_mathod(vector<string>& orders);
    void casual_match_opponents(vector<string>& orders);
    void profile(vector<string>& orders);
    void received_invitations(vector<string>& orders);
    void reports(vector<string>& orders);
    void match_status(vector<string>& orders);
    void ranked_match_opponents(vector<string>& orders);
};


