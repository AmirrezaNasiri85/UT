#include "Match.hpp"
#include "People.hpp"

Match::Match(Player* player_one, Player* player_two, const int start_value)
    : player_one(player_one), player_two(player_two), player_one_bullets(start_value),
        player_two_bullets(start_value), player_one_health(start_value), player_two_health(start_value)
{};

Casual::~Casual(){}

Ranked::~Ranked(){}

void Ranked::apply_penalty(){
    player_one->apply_penalty(player_one_health, player_one_bullets);
    player_two->apply_penalty(player_two_health, player_two_bullets);
}

bool Match::can_move(Player* player){
    if(player == player_one){
        if(current_one_movement.empty()){return true;}
        else{return false;}
    }else if(player == player_two){
        if(current_two_movement.empty()){return true;}
        else{return false;}
    }return true;
}

Casual::Casual(Player* player_one, Player* player_two, const int start_value)
    : Match(player_one, player_two, start_value){};

Match* find_match(map<Player*, Match*>& progress_match,Player* player){
    auto obj = progress_match.find(player);
    if(obj == progress_match.end()){return nullptr;}
    return obj->second;
}

Ranked::Ranked(Player* player_one, Player* player_two, const int start_value)
    : Match(player_one, player_two, start_value){};

void Match::print_base(Player* player){
    cout << "Turn " << turn_number << endl;
    if(player_one == player){
        if(current_one_movement.empty()){cout << "You: pending" << endl;}
        else{cout << "You: " << current_one_movement << endl;}
        if(current_two_movement.empty()){cout << "Your opponent: pending" << endl;}
        else{cout << "Your opponent: played" << endl;}
    }else if(player_two == player){
        if(current_two_movement.empty()){cout << "You: pending" << endl;}
        else{cout << "You: " << current_two_movement << endl;}
        if(current_one_movement.empty()){cout << "Your opponent: pending" << endl;}
        else{cout << "Your opponent: played" << endl;}
    }cout << left;
    cout << "History:" << endl
        << setw(20) << "Opponent's moves:" << "Your moves:" << endl;
    if(player == player_one){
        player_one_match_screen();
    }else if(player == player_two){
        player_two_match_screen();
    }
}

void Casual::print_information(Player* player){
    print_base(player);
    if(player == player_one){
        cout << "Your remaining bullets: " << player_one_bullets << endl;
    }else if(player == player_two){
        cout << "Your remaining bullets: " << player_two_bullets << endl;
    }
}

void Ranked::print_information(Player* player){
    print_base(player);
    if(player == player_one){
        cout << "Your remaining bullets: " << player_one_bullets << endl
            << "Your remaining health: " << player_one_health << endl;
    }else if(player == player_two){
        cout << "Your remaining bullets: " << player_two_bullets << endl
             << "Your remaining health: " << player_two_health << endl;
    }
}

void Casual::end_calculations(Player* winner, Player* losser){
    double diff_XP = winner->diff_XP(losser);
    int match_XP = static_cast<int>(max(5.0, 50.0 - (0.1 * diff_XP)));

    winner->changings(Change_code::increase_XP, match_XP);
    losser->changings(Change_code::decrease_XP, match_XP);

    winner->changings(Change_code::change_status);
    losser->changings(Change_code::change_status);
}

int Match::cal_health(Player* winner){
    if(winner == player_one){
        return player_one_health * HEALTH_COEFFICIENT;
    }return player_two_health * HEALTH_COEFFICIENT;
}

RPs cal_RP(const string& level){
    if(level == "Bronze"){return RPs::Bronze;}
    else if(level == "Silver"){return RPs::Silver;}
    else if(level == "Golden"){return RPs::Golden;}
    else{return RPs::Platinum;}
}

void Ranked::end_calculations(Player* winner, Player* losser){
    string level = winner->level_identification();

    int health_score = cal_health(winner);
    int RP_score = static_cast<int>(cal_RP(level));
    winner->changings(Change_code::increase_RP, RP_score + health_score);
    losser->changings(Change_code::decrease_RP, RP_score);   
    winner->changings(Change_code::change_status);
    losser->changings(Change_code::change_status);
}

void Match::check_end_game(){
    Player* winner;Player* losser;
    if(current_two_movement == "shoot" && current_one_movement == "reload"){
        player_two_bullets -= 1;
        player_one_health -= 1; 
        player_one_bullets += 1;
    }else if(current_one_movement == "shoot" && current_two_movement == "reload"){
        player_one_bullets -= 1;
        player_two_health -= 1;
        player_two_bullets += 1;
    }else if(current_two_movement == "shoot" && current_one_movement == "shoot"){
        player_one_bullets -= 1;
        player_two_bullets -= 1;
    }else if(current_two_movement == "shoot" && current_one_movement == "defend"){
        player_two_bullets -= 1;
    }else if(current_one_movement == "shoot" && current_two_movement == "defend"){
        player_one_bullets -= 1;
    }else if(current_two_movement == "reload" && current_one_movement == "reload"){
        player_one_bullets += 1;
        player_two_bullets += 1;
    }else if(current_two_movement == "reload" && current_one_movement == "defend"){
        player_two_bullets += 1;
    }else if(current_one_movement == "reload" && current_two_movement == "defend"){
        player_one_bullets += 1;
    }if(player_one_health == 0 || player_two_health == 0){
        if(player_one_health == 0){
            losser = player_one;
            winner = player_two;
        }else if(player_two_health == 0){
            losser = player_two;
            winner = player_one;
        }game_ended = true;
    }if(game_ended){
        end_calculations(winner, losser);
    }
}

void Casual::shoot_validation(vector<string>& orders, Player* player){
    if(player_one == player){
        if(orders[4] == "shoot" && player_one_bullets == 0){
            throw Format("Bad Request");
        }
    }else if(player_two == player){
        if(orders[4] == "shoot" && player_two_bullets == 0){
            throw Format("Bad Request");
        }
    }
}

void Ranked::shoot_validation(vector<string>& orders, Player* player){
    if(player_one == player){
        if(orders[4] == "shoot" && player_one_bullets == 0){
            throw Format("Bad Request");
        }
    }else if(player_two == player){
        if(orders[4] == "shoot" && player_two_bullets == 0){
            throw Format("Bad Request");
        }
    }
}

void earse_match(map<Player*, Match*>& progress_match, Player* winner, Player* loser){
    auto obj_winner = progress_match.find(winner);
    auto obj_loser = progress_match.find(loser);
    progress_match.erase(obj_winner);
    progress_match.erase(obj_loser);
}
 
void Match::player_one_match_screen(){
    int one_size = player_one_movements.size();
    int two_size = player_two_movements.size();

    if(one_size == two_size){
        for(int index = 0;index < one_size;index++){
            cout << setw(20) << player_two_movements[index] 
                << player_one_movements[index] << endl;
        }
    }else if(one_size  > two_size){
        for(int index = 0;index < two_size;index++){
            cout << setw(20) << player_two_movements[index] 
                << player_one_movements[index] << endl;     
        }cout << setw(20) << "" << player_one_movements[one_size - 1] << endl;
    }else{
        for(int index = 0;index < two_size;index++){
            cout << setw(20) << player_two_movements[index] 
                << player_one_movements[index] << endl;     
        }cout <<  setw(20) << "" << player_two_movements[one_size - 1] << endl;           
    }
}

void Match::player_two_match_screen(){
    int one_size = player_one_movements.size();
    int two_size = player_two_movements.size();

    if(one_size == two_size){
        for(int index = 0;index < one_size;index++){
            cout << setw(20) << player_one_movements[index] 
                << player_two_movements[index] << endl;
        }
    }else if(one_size > two_size){
        for(int index = 0;index < one_size;index++){
            cout << setw(20) << player_one_movements[index] 
                << player_two_movements[index] << endl;
        }cout << setw(20) << player_one_movements[one_size - 1] << "" << endl;
    }else if(one_size < two_size){
        for(int index = 0;index < one_size;index++){
            cout << setw(20) << player_one_movements[index] 
                << player_two_movements[index] << endl;
        }cout << setw(20) << "" << player_two_movements[two_size - 1] << endl;
    }
}

void Match::match_clearance(map<Player*, Match*>& progress_match, Player* player){
    Match* match = find_match(progress_match, player);
    
    if(!match->current_two_movement.empty() && !match->current_one_movement.empty()){
        match->current_two_movement.clear();
        match->current_one_movement.clear();
        match->turn_number += 1; 
    } 
}

void Match::action(map<Player*, Match*>& progress_match, vector<string>& orders, Player* on_player){
    if(on_player == player_one){
        current_one_movement = orders[4];
        if(!current_two_movement.empty()){
            player_one_movements.push_back(current_one_movement);
            player_two_movements.push_back(current_two_movement);
       
            check_end_game();
            if(game_ended){
                earse_match(progress_match, player_one, player_two);
            }else{
                match_clearance(progress_match, on_player);
            }
        }cout << "OK" << endl;
    }else if(on_player == player_two){
        current_two_movement =  orders[4];
        if(!current_one_movement.empty()){
            player_one_movements.push_back(current_one_movement);
            player_two_movements.push_back(current_two_movement);
        
            check_end_game();
            if(game_ended){
                earse_match(progress_match, player_one, player_two);
            }else{
                match_clearance(progress_match, on_player);
            }
        }cout << "OK" << endl;
    }
}