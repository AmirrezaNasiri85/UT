#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include "../Objects/People.hpp"

using namespace std;


const int START_RP = 1200;
const int HEALTH_COEFFICIENT = 25;
const int START_RANK = 3;
const int START_CASUAL = 1;

class Match{
protected:
    Player* player_one;
    vector<string>player_one_movements;
    string current_one_movement;
    Player* player_two;
    vector<string>player_two_movements;
    string current_two_movement;
    int turn_number = 1; 
    bool game_ended = false;
    void print_base(Player* player);
    void player_one_match_screen();
    void player_two_match_screen();
    int player_one_bullets;
    int player_two_bullets;
    int player_one_health;
    int player_two_health;

    int cal_health(Player* winner);
public:
    virtual ~Match() = default;
    virtual void end_calculations(Player* winner, Player* losser) = 0;
    virtual void shoot_validation(vector<string>& orders, Player* player) = 0;
    virtual void print_information(Player* player) = 0;
    bool can_move(Player* player);
    void check_end_game();
    void action(map<Player*, Match*>& progress_match, vector<string>& orders, Player* on_player);
    void match_clearance(map<Player*, Match*>& progress_match, Player* player);
    Match(Player* player_one, Player* player_two, const int start_value);
};


class Casual : public Match{
private:
    void end_calculations(Player* winner, Player* losser);
public:
    virtual ~Casual();
    Casual(Player* player_one, Player* player_two, const int start_value);
    void shoot_validation(vector<string>& orders, Player* player) override;
    void print_information(Player* player) override;
};

enum class RPs{
    Bronze = 75,
    Silver = 100,
    Golden = 125,
    Platinum = 150
};

class Ranked : public Match{
private:


public:
    Ranked(Player* player_one, Player* player_two, const int start_value);
    virtual ~Ranked();
    void shoot_validation(vector<string>& orders, Player* player) override;
    void print_information(Player* player) override;
    void end_calculations(Player* winner, Player* losser);
    void apply_penalty();
};


Match* find_match(map<Player*, Match*>& progress_match, Player* player);
void earse_match(map<Player*, Match*>& progress_match, Player* winner, Player* loser);
RPs cal_RP(const string& level);