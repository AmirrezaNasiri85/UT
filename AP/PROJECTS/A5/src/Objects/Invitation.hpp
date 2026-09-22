#pragma once

#include <iostream>
#include <string>
#include <set>


using namespace std;

struct Invitation{
    int id;
    string match_type;
    string sender_name;
    string giver_name;
    bool is_rejected = false;

    Invitation(const string& sender, const string& giver, const string& match_type, int id);
};

class Invitation_management{
private:
    set<string>match_types = {"casual", "ranked"};
    int invitation_id = 1;
public:
    Invitation* make_invitations(const string& sender, const string& giver
        , const string& match_type);
    bool check_type_existance(const string& match_type);
};


