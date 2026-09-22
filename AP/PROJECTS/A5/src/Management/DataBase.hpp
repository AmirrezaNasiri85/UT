#pragma once
#include <string>
#include <map>
#include <list>
#include "../Objects/People.hpp"
#include "../Objects/Report.hpp"
#include "../Objects/Match.hpp"

using namespace std;


struct Data_base{
    string on_username;
    Player* on_player = nullptr;
    Admin* on_admin = nullptr;
    Match* on_match = nullptr;
    map<string,Player*>players_list;
    map<string,Admin*>admins_list;
    map<Player*, Match*> progress_match;
    list<Player*>casual_options;
    list<Player*>rank_options;
    map<int, Report*> reports;

    ~Data_base();
};

void fill_rank_options(Player* player, Data_base* data);
void print_reports(Data_base* data_base);
void print_casual_players(Data_base* data_base);
void print_ranked_players(Data_base* data);
Player* find_player(Data_base* data_base, const string& name); 
void clear_cotation(vector<string>& orders);
void erase_report(const int id, map<int, Report*>& reports);