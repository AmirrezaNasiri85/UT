#include "People.hpp"

Penalty::Penalty(const string& type, const int amount, const int number_matches, const int id)
    : type(type), amount(amount), number_matches(number_matches), id(id){}

bool sort_RP_asc(Player* a, Player* b){
    if(a->RP == b->RP){
        string username_a = a->username;
        string username_b = b->username;

        transform(username_a.begin(), username_a.end(), username_a.begin(), ::tolower);
        transform(username_b.begin(), username_b.end(), username_b.begin(), ::tolower);

        return username_a < username_b;
    }else{return a->RP < b->RP;}
}

bool sort_Rp_desc(Player* a, Player* b){
    if(a->RP == b->RP){
        string username_a = a->username;
        string username_b = b->username;

        transform(username_a.begin(), username_a.end(), username_a.begin(), ::tolower);
        transform(username_b.begin(), username_b.end(), username_b.begin(), ::tolower);

        return username_a < username_b;
    }else{return a->RP > b->RP;}
}

User::User(const string& username, const string& password)
    : username(username), password(password){
};

void User::change_logging_status(){
    is_logged = !is_logged;
}

void User::check_logging(const string& given_username, const string& given_password){
    if(username == given_username && password != given_password){
        throw Permission("Permission Denied");
    }else if(username == given_username && password == given_password && is_logged){
        throw Permission("Permission Denied");
    }
}




Player::Player(const string& username, const string& password, const int XP, const int rp)
    : User(username, password), XP(XP), RP(rp){}

bool Player::check_data(const string& given_name, const string& given_password){
    if(given_name == username && given_password == password){
        return true;
    }return false;
}

bool sort_XP_asc(Player* a, Player* b){
    if(a->XP == b->XP){
        string username_a  = a->username;
        string username_b = b->username;

        transform(username_a.begin(), username_a.end(), username_a.begin(), ::tolower);
        transform(username_b.begin(), username_b.end(), username_b.begin(), ::tolower);

        return username_a < username_b;
    }return a->XP < b->XP;
}

bool sort_XP_desc(Player* a, Player* b){
    if(a->XP == b->XP){
        string username_a  = a->username;
        string username_b= b->username;

        transform(username_a.begin(), username_a.end(), username_a.begin(), ::tolower);
        transform(username_b.begin(), username_b.end(), username_b.begin(), ::tolower);

        return username_a < username_b;
    }return a->XP > b->XP;
}

void Player::print_XP(){
    cout << username << " with " << XP << " XP" << endl;
}

void Player::print_RP(){
    cout << username << " with " << RP << " RP" << endl;
}

string Player::level_identification(){
    string level;
    if(RP <  1400){level = "Bronze";}
    else if(RP >= 1400 && RP < 1750){level = "Silver";}
    else if(RP >= 1750 && RP < 2250){level = "Golden";}
    else{level = "Platinum";}
    return level;
}

void Player::print_information(){
    string level = level_identification();
    cout << "username: \"" << username << "\"" << endl
        << "Level: " << level << endl
        << "RP: " << RP << endl
        << "XP: " << XP << endl
        << "Total wins: " << total_wins << endl
        << "Total losses: " << total_lost << endl;
}

void Player::add_invitations(int id, Invitation* invitation){
    invitations.emplace(id, invitation);
}

void Player::add_accepted_invitations(const int id, Invitation* invitation){
    accepted_invitations.emplace(id, invitation);
}

void Player::add_rejected_invitations(const int id, Invitation* invitation){
    rejected_invitations.emplace(id, invitation);
}

void Player::invitation_op(const int id, Invitation* invitation, const Invitation_code invitation_code){
    if(Invitation_code::invitation == invitation_code){
        add_invitations(id, invitation);
    }else if(Invitation_code::acception == invitation_code){
        add_accepted_invitations(id, invitation);
    }else if(Invitation_code:: rejection == invitation_code){
        add_rejected_invitations(id, invitation);
    }else if(invitation_code == Invitation_code::remove){
        remove_invitations(id);
    }
}

Invitation* Player::invitation_id_existance(int id){
    for(auto obj : invitations){
        if(obj.first == id){
            return obj.second;
        }
    }return nullptr;
}

Invitation* Player::rejected_invitation_existance(int id){
    auto it = rejected_invitations.find(id);
    if(it == rejected_invitations.end()){return nullptr;}
    return it->second;
}

Invitation* Player::accepted_invitation_existance(int id){
    auto it = accepted_invitations.find(id);
    if(it == accepted_invitations.end()){return nullptr;}
    return it->second;
}

Invitation* Player::find_invitations(const int id, const Finding_code finding_code){
    if(finding_code == Finding_code::invitations){
        return invitation_id_existance(id);
    }else if(finding_code == Finding_code::rejection){
        return rejected_invitation_existance(id); 
    }else if(finding_code == Finding_code::acception){
        return accepted_invitation_existance(id);
    }return nullptr;
}

void Player::printings(const Printing_code printing_code){
    if(printing_code == Printing_code::XP){
        print_XP();
    }else if(printing_code == Printing_code::information){
        print_information();
    }else if(printing_code == Printing_code::invitations){
        print_invitations();
    }else if(printing_code == Printing_code::Rp){
        print_RP();
    }
}

void Player::change_playing_status(){
    is_playing = !is_playing;
}

bool Player::show_playing(){
    return is_playing;
}

void Player::earse_invitation(const int id){
    for(auto it = invitations.begin();it != invitations.end();it++){
        if(it->first == id){
            invitations.erase(it);
            break;
        }
    }
}

void Player::print_invitations(){
    if(invitations.empty()){
        cout << "Empty" << endl;
        return;
    }else{
        for(auto obj : invitations){
            cout << obj.first 
                << ": Invitation from \""
                << obj.second->sender_name << "\" for a \""
                << obj.second->match_type << "\" match"
                << endl;
        }
    }
}

string Player::get_name(){
    return username;
}

int Player::diff_XP(const Player* other){
    return this->XP - other->XP;
}

void Player::remove_invitations(const int id){
    auto obj = invitations.find(id);
    invitations.erase(obj);
}

bool Player::block_existance(const string& username){
    if(blocked_players.find(username) == blocked_players.end()){return false;}
    return true;
}

void Player::block_user(const string& username, Player* player){
    blocked_players.emplace(username, player);
}

void Player::unblock_user(const string& username){
    auto obj = blocked_players.find(username);
    if(obj == blocked_players.end()){
        throw Existance("Not Found");
    }else{
        blocked_players.erase(obj);
    }
}   

void Player::blockings(Block_code code, const string& username, Player* player){
    if(code == Block_code::block){
        block_user(username, player);
    }else if(code == Block_code::unblock){
        unblock_user(username);
    }
}

void Player::increase_RP(const int score){
    RP += score;
    total_wins += 1;
}

void Player::decrease_Rp(const int score){
    RP -= score;
    total_lost += 1;
}

void Player::increase_XP(const int score){
    XP += score;
    total_wins += 1;
}

void Player::decrease_Xp(const int score){
    XP -= score;
    total_lost += 1;
}

void Player::changings(const Change_code change_code, const int score){
    if(change_code == Change_code::increase_RP){
        increase_RP(score);
    }else if(change_code == Change_code::decrease_RP){
        decrease_Rp(score);
    }else if(change_code == Change_code::increase_XP){
        increase_XP(score);
    }else if(change_code == Change_code::decrease_XP){
        decrease_Xp(score);
    }else if(change_code == Change_code::change_status){
        change_playing_status();
    }
}

void Player::initalize_penalty(Penalty& penalty){
    if(penalty.type == "health_penalty"){
        health = penalty;
    }else if(penalty.type == "bullet_penalty"){
        bullet = penalty;
    }
}

void Player::apply_penalty(int& health_count, int& bullet_count){
    if(health.number_matches != 0){
        health_count -= health.amount;
        health.number_matches -= 1;
    }if(bullet.number_matches != 0){
        bullet_count -= bullet.amount;;
        bullet.number_matches -= 1;
    }
}

void Player::print_block_users(){
    for(auto obj : blocked_players){
        cout << obj.first << " --- " << obj.second << endl;
    }
}

Admin::Admin(const string& username, const string& password)
    : User(username, password){
}
