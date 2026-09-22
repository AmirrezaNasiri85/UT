#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <utility>
#include "Management/Error.hpp"
#include "Invitation.hpp"


using namespace std;


struct Penalty{
    string type;
    int amount;
    int number_matches;
    int id;
    Penalty(const string& type = "", const int amount = 0, const int number_matches = 0, const int id = 0);
};


class User{
protected:
    string username;
    string password;
    bool is_logged = false;
    
public:
    User(const string& username, const string& password);
    virtual ~User() = default;
    
    void check_logging(const string& given_username, const string& given_password);
    void change_logging_status();
};


enum class Finding_code{
    invitations = 1,
    rejection = 2,
    acception = 3
};

enum class Printing_code{
    XP = 1,
    information = 2,
    invitations = 3,
    Rp = 4
};

enum class Invitation_code{
    invitation = 1,
    acception = 2,
    rejection = 3,
    remove = 4
};

enum class Game_code{
    diff_xp = 1,
    end_calculation = 2
};

enum class Block_code{
    block = 1,
    unblock = 2,
    block_existance = 3
};

enum class Change_code{
    increase_RP = 1,
    decrease_RP = 2,
    increase_XP = 3,
    decrease_XP = 4,
    change_status = 5
};

class Player : public User{
private:
    int total_wins = 0;
    int total_lost = 0;
    int XP;
    int RP;
    Penalty health;
    Penalty bullet;
    map<int, Invitation*>invitations;
    map<int, Invitation*>rejected_invitations;
    map<int, Invitation*>accepted_invitations;
    bool is_playing = false;
    map<string, Player*>blocked_players;

    Invitation* invitation_id_existance(int id);
    Invitation* rejected_invitation_existance(int id);
    Invitation* accepted_invitation_existance(int id);
    void print_XP();
    void print_RP();
    void print_information();
    void print_invitations();
    void add_invitations(int id, Invitation* invitation);
    void remove_invitations(const int id);
    void add_accepted_invitations(const int id, Invitation* invitation);
    void add_rejected_invitations(const int id, Invitation* invitation);
    void block_user(const string& username, Player* player);
    void unblock_user(const string& username);
    void increase_RP(const int score);
    void decrease_Rp(const int score);
    void increase_XP(const int score);
    void decrease_Xp(const int score);
    void change_playing_status();
public:
    string level_identification();
    friend bool sort_RP_asc(Player* a,  Player* b);
    friend bool sort_Rp_desc(Player* a,  Player* b);
    friend bool sort_XP_asc(Player* a, Player* b);
    friend bool sort_XP_desc(Player* a, Player* b);

    void apply_penalty(int& health, int& bullet);
    void initalize_penalty(Penalty& penalty);
    bool block_existance(const string& username);
    Player(const string& username, const string& password, const int XP, const int RP);
    bool check_data(const string& name, const string& password);
    Invitation* find_invitations(const int id, const Finding_code finding_code);
    void printings(const Printing_code printing_code);
    void invitation_op(const int id, Invitation* invitation, const Invitation_code invitation_code);
    void blockings(Block_code code, const string& username, Player* player);
    void earse_invitation(const int id);
    int diff_XP(const Player* other);
    void changings(const Change_code change_code, const int score = 0);

    bool show_playing();
    string get_name();


    //debuging function.
    void print_block_users();
};





class Admin : public User{
private:

public:
    Admin(const string& username, const string& password);

};


bool sort_RP_asc(Player* a,  Player* b);
bool sort_Rp_desc(Player* a,  Player* b);
bool sort_XP_asc(Player* a, Player* b);
bool sort_XP_desc(Player* a, Player* b);