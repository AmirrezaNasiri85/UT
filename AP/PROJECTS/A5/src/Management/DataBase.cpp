#include "DataBase.hpp"


Data_base::~Data_base(){
    for(auto obj : players_list){
        delete(obj.second);
    }for(auto obj : admins_list){
        delete(obj.second);
    }
}

void erase_report(const int id, map<int, Report*>& reports){
    auto obj = reports.find(id);
    if(obj != reports.end()){
        delete obj->second;
        reports.erase(obj);
    }
}

void fill_rank_options(Player* player, Data_base* data){
    data->rank_options.clear();
    string level_base = player->level_identification();
    for(auto obj : data->players_list){
        if(level_base == obj.second->level_identification()){
            data->rank_options.push_back(obj.second);
        }
    }
}

void print_ranked_players(Data_base* data){
    int player_numbers = 1;
    for(auto& player : data->rank_options){
        if(player == data->on_player){continue;}
        else{
            cout << player_numbers << ". ";
            player->printings(Printing_code::Rp);
            player_numbers += 1;
        }
    }
}

void print_casual_players(Data_base* data_base){
    int player_number = 1;
    for(auto& player : data_base->casual_options){
        if(player == data_base->on_player){
            continue;
        }else{
            cout << player_number << ". ";
            player->printings(Printing_code::XP);
            player_number += 1;
        }
    }
}

Player* find_player(Data_base* data_base, const string& name){
    if(data_base->players_list.find(name) == data_base->players_list.end()){
        return nullptr;
    }Player* temp = data_base->players_list.find(name)->second;
    return temp;
}

void print_reports(Data_base* data_base){
    for(auto report : data_base->reports){
        cout << report.first<< ": "
            << "\"" << report.second->sender_username<< "\""
            << " reported \"" << report.second->reported_username << "\""
            << " for: \"" <<  report.second->reason << "\"" << endl;
    }
}

void clear_cotation(vector<string>& orders){
    vector<string>new_orders;
    for(string& word : orders){
        if(word[0] == '\"' && word[word.size() -1] == '\"'){
            word = word.substr(1, word.size() - 2);
        }
    }
}

