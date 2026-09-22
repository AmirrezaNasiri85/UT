#include "PostManagement.hpp"
#include <iterator>


Post_management::Post_management(Data_base* data)
    : data(data){
        post_input = new Post_input();
};

Post_management::~Post_management(){
    delete(post_input);
}

string Post_management::find_mathod(vector<string>& orders){
    bool post_pass = false;
    bool method_find = false;
    for(auto word : orders){
        if(word == "POST"){
            post_pass = true;
        }else if(post_pass){
            auto it = post_methods.find(word);
            if(it != post_methods.end()){
                method_find = true;
                return word;
            }
        }
    }if(!method_find){
        throw Existance("Not Found");
    }return "";
}

void username_status(vector<string>& orders, string& username, string& status){
    if(orders[3] == "username"){
        username = orders[4];
        status = orders[6];
    }else{
        username = orders[6];
        status = orders[4];
    }
}

void username_password(vector<string>& orders, string& username, string& password){
    if(orders[3] == "username"){
        username = orders[4];
        password = orders[6];
    }else{
        username = orders[6];
        password = orders[4];
    }
}

void username_match_type(vector<string>& orders, string& username, string& match_type){
    if(orders[3] == "username"){
        username = orders[4];
        match_type = orders[6];
    }else{
        username = orders[6];
        match_type = orders[4];
    } 
}

void username_find(vector<string>& orders, string& username){
    if(orders[3] == "username"){username = orders[4];}
    else{username = orders[6];}
}

void username_reason(vector<string>& orders, string& username, string& reason){
    if(orders[3] == "username"){
        username = orders[4];
        reason = orders[6];
    }else{
        username = orders[6];
        reason = orders[4];
    }
}

void penalty_parameter(string& amount, string& type, string& report_id
        , string& number_of_matches, const vector<string>orders){
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "amount"){
            amount = orders[index + 1];
        }else if(orders[index] == "report_id"){
            report_id = orders[index + 1];
        }else if(orders[index] == "type"){
            type = orders[index + 1];
        }else if(orders[index] == "number_of_matches"){
            number_of_matches = orders[index + 1];
        }
    }
}

void Post_management::add_new_player(string& username, Player* new_player){
    data->players_list.emplace(username, new_player);
}

void Post_management::check_register(vector<string>& orders){
    if(orders[2] == "?" && orders.size() == 7){
        if((orders[3] == "username" && orders[5] == "password")
            || (orders[5] == "username" && orders[3] == "password")){

            string username, password;
            username_password(orders, username, password);

            if(username[0] != '\"' || username[username.size() - 1] != '\"'){
                throw Format("Bad Request");
            }else if(password[0] != '\"' || password[password.size() - 1] != '\"'){
                throw Format("Bad Request");
            }
            clear_cotation(orders);
            username_password(orders, username, password);
            if(data->on_player != nullptr || data->on_admin != nullptr){
                throw Format("Permission Denied");
            }auto it_player = data->players_list.find(username);
            if(it_player != data->players_list.end()){
                throw Format("Bad Request");
            }auto it_admin = data->admins_list.find(username);
            if(it_admin != data->admins_list.end()){
                throw Format("Bad Request");
            }

        }else{throw Format("Bad Request");}
    }else{throw Format("Bad Request");}
}

void Post_management::register_core(vector<string>& orders){
    string username, password;
    if(orders[3] == "username"){
        username = orders[4];
        password = orders[6];
    }else{
        username = orders[6];
        password = orders[4];
    }
    Player* new_player = new Player(username, password, REGISTER_XP, START_RP);
    new_player->change_logging_status();
    add_new_player(username, new_player);
    data->on_player = new_player;
    data->on_username =  username;
    
    cout << "OK" << endl;
}

void Post_input::register_extraction(vector<string>& orders){
    vector<string> new_orders;
    for(size_t index = 0;index < orders.size();index++){
        if(index != orders.size() - 1){
            if(orders[index] == "POST"){
                int count = std::count(new_orders.begin(), new_orders.end(), "POST");
                if(count == 0){new_orders.push_back(orders[index]);}
            }else if(orders[index] == "register"){
                int count = std::count(new_orders.begin(), new_orders.end(), "register");
                if(count == 0){new_orders.push_back(orders[index]);}
            }else if(orders[index] == "?"){
                int count = std::count(new_orders.begin(), new_orders.end(), "?");
                if(count == 0){new_orders.push_back("?");}
            }else if(orders[index] == "username"){
                int count = std::count(new_orders.begin(), new_orders.end(), "username");
                if(count == 0){
                    new_orders.push_back("username");
                    new_orders.push_back(orders[index + 1]);
                }
            }else if(orders[index] == "password"){
                int count = std::count(new_orders.begin(), new_orders.end(), "password");
                if(count == 0){
                    new_orders.push_back("password");
                    new_orders.push_back(orders[index + 1]);
                }
            }
        }
    }orders = new_orders;
}

void Post_management::registerr(vector<string>& orders){
    try{
        post_input->register_extraction(orders);
        check_register(orders);
        register_core(orders);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}

void Post_input::login_extraction(vector<string>& orders){
    vector<string> new_order;
    for(size_t index = 0;index < orders.size();index++){
        if(index != orders.size() - 1){
            if(orders[index] == "POST"){
                int count = std::count(new_order.begin(), new_order.end(), "POST");
                if(count == 0){new_order.push_back("POST");}
            }else if(orders[index] == "login"){
                int count = std::count(new_order.begin(), new_order.end(), "login");
                if(count == 0){new_order.push_back("login");}
            }else if(orders[index] == "username"){
                int count = std::count(new_order.begin(), new_order.end(), "username");
                if(count == 0){
                    new_order.push_back("username");
                    new_order.push_back(orders[index + 1]);
                }
            }else if(orders[index] == "password"){
                int count = std::count(new_order.begin(), new_order.end(), "password");
                if(count == 0){
                    new_order.push_back("password");
                    new_order.push_back(orders[index + 1]);
                }
            }else if(orders[index] == "?"){
                int count = std::count(new_order.begin(), new_order.end(), "?");
                if(count == 0){new_order.push_back("?");}
            }
        }
    }orders = new_order;
}

void Post_management::check_login_role(string& username, string& password){
    auto admin_ptr = data->admins_list.find(username);
    auto player_ptr = data->players_list.find(username);
    if(admin_ptr == data->admins_list.end() && player_ptr == data->players_list.end()){
        throw Existance("Not Found");
    }else if(admin_ptr == data->admins_list.end()){
        auto it = player_ptr;
        (*it).second->check_logging(username, password);
    }else if(player_ptr == data->players_list.end()){
        auto it = admin_ptr;
        (*it).second->check_logging(username, password);
    }
}

void Post_management::check_login(vector<string>& orders){
    if(orders[2] == "?" && orders.size() == 7){
        if((orders[3] == "username" && orders[5] == "password")
            || (orders[5] == "username" && orders[3] == "password")){
            string username, password;
            username_password(orders, username, password);
            if(username[0] != '\"' || username[username.size() - 1] != '\"'){
                throw Format("Bad Request");
            }else if(password[0] != '\"' || password[password.size() - 1] != '\"'){
                throw Format("Bad Request");
            }clear_cotation(orders);
            username_password(orders, username, password);

            if(data->on_player != nullptr){
                throw Existance("Permission Denied");
            }else if(data->on_admin != nullptr){
                throw Existance("Permission Denied");
            }

            check_login_role(username, password);
        }else{throw Format("Bad Request");}
    }else{throw Format("Bad Request");}
}

void Post_management::login_core(vector<string>& orders){
    string username;
    if(orders[3] == "username"){username = orders[4];}
    else{username = orders[6];}

    auto admin_ptr = data->admins_list.find(username);
    auto player_ptr = data->players_list.find(username);
    if(admin_ptr == data->admins_list.end()){
        auto it = player_ptr;
        (*it).second->change_logging_status();
        data->on_player = (*it).second;
    }else if(player_ptr == data->players_list.end()){
        auto it = admin_ptr;
        (*it).second->change_logging_status();
        data->on_admin = (*it).second;
    }
    data->on_username = username;
    cout << "OK" << endl;
}

void Post_management::login(vector<string>& orders){
    try{
        post_input->login_extraction(orders);
        check_login(orders);
        login_core(orders);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}

void Post_input::logout_extraction(vector<string>& orders){
    vector<string> new_order;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "POST"){
            int count = std::count(new_order.begin(), new_order.end(), "POST");
            if(count == 0){new_order.push_back("POST");}
        }else if(orders[index] == "logout"){
            int count = std::count(new_order.begin(), new_order.end(), "logout");
            if(count == 0){new_order.push_back("logout");}
        }else if(orders[index] == "?"){
            int count = std::count(new_order.begin(), new_order.end(), "?");
            if(count == 0){new_order.push_back("?");}    
        } 
    }orders = new_order;
}

void Post_management::check_logout(vector<string>& orders){
    if(orders[2] == "?" && orders.size() == 3){
        if(data->on_player == nullptr && data->on_admin == nullptr){
           throw Permission("Permission Denied");
        }
    }else{throw Format("Bad Request");}
}

void Post_management::logout_core(){
    if(data->on_player == nullptr){
        data->on_admin->change_logging_status();
        data->on_admin = nullptr;
        data->on_match = nullptr;
    }else if(data->on_admin == nullptr){
        data->on_player->change_logging_status();
        data->on_player = nullptr;
    }data->on_username.clear();
    cout << "OK" << endl;
}

void Post_management::logout(vector<string>& orders){
    try{
        post_input->logout_extraction(orders);
        check_logout(orders);
        logout_core();
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}

void Post_input::casual_match_extraction(vector<string>& orders){
    vector<string>new_order;
    for(size_t index = 0;index < orders.size();index++){
        if(index != orders.size() - 1){
            if(orders[index] == "POST"){
                int count = std::count(new_order.begin(), new_order.end(), "POST");
                if(count == 0){new_order.push_back("POST");}
            }else if(orders[index] == "?"){
                int count = std::count(new_order.begin(), new_order.end(), "?");
                if(count == 0){new_order.push_back("?");}    
            }else if(orders[index] == "casual_match_ready"){
                int count = std::count(new_order.begin(), new_order.end(), "casual_match_ready");
                if(count == 0){new_order.push_back("casual_match_ready");}   
            }else if(orders[index] == "status"){
                int count = std::count(new_order.begin(), new_order.end(), "status");
                if(count == 0){
                    new_order.push_back("status");
                    new_order.push_back(orders[index + 1]);
                } 
            }
        }
    }orders = new_order;
}

void Post_management::check_casual_match_ready(vector<string>& orders){
    if(orders.size() == 5 && orders[2] == "?" && orders[3] == "status"){
        if(orders[4] != "\"true\"" && orders[4] != "\"false\""){
            throw Format("Bad Request");
        }else if(data->on_admin != nullptr){
            throw Permission("Permission Denied");
        }else if(data->on_player == nullptr){
            throw Permission("Permission Denied");  
        }
    }else{throw Format("Bad Request");}
}

void Post_management::casual_match_ready_core(vector<string>& orders){
    clear_cotation(orders);
    if(orders[4] == "true"){
        bool find_player = false;
        for(auto player : data->casual_options){
            if(player == data->on_player){find_player = true;}
        }if(!find_player){
            data->casual_options.push_back(data->on_player);
        }
    }else if(orders[4] == "false"){
        for(auto it = data->casual_options.begin();it != data->casual_options.end();it++){
            if(*it == data->on_player){
                data->casual_options.erase(it);
                break;
            }
        }
    }cout << "OK" << endl;
}

void Post_management::casual_match_ready(vector<string>& orders){
    try{
        post_input->casual_match_extraction(orders);
        check_casual_match_ready(orders);
        casual_match_ready_core(orders);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    }   
}

void Post_management::second_check_invitation(vector<string>& orders, Invitation_management* invitation_handeler){
    string username, match_type;
    username_match_type(orders, username, match_type);
    if(username[0] != '\"' || username[username.size() - 1] != '\"'){
        throw Format("Bad Request");
    }else if(match_type[0] != '\"' || match_type[match_type.size() - 1] != '\"'){
        throw Format("Bad Request");
    }clear_cotation(orders);
    username_match_type(orders, username, match_type);
    
    Player* target = find_player(data, username);
    if(!invitation_handeler->check_type_existance(match_type)){throw Format("Bad Request");}
    else if(data->on_username == username){throw Permission("Permission Denied");}
    else if(data->on_admin != nullptr){throw Permission("Permission Denied");}
    else if(data->on_player == nullptr){throw Permission("Permission Denied");}
    else if(data->admins_list.find(username) != data->admins_list.end()){throw Permission("Permission Denied");}
    else if(data->players_list.find(username) == data->players_list.end()){throw Existance("Not Found");}
    else if(target->block_existance(data->on_username)){throw Existance("Not Found");}
    else if (data->on_player->block_existance(username)){throw Existance("Not Found");}
}

void Post_management::check_invitation(vector<string>& orders, Invitation_management* invitation_handeler){
    if(orders[2] == "?" && orders.size() == 7){
        if((orders[3] == "username" && orders[5] == "match_type") 
        || ((orders[3] == "match_type" && orders[5] == "username"))){
            second_check_invitation(orders, invitation_handeler);
        }else{throw Format("Bad Request");}
    }else{throw Format("Bad Request");}
}

void Post_management::invitation_core(vector<string>& orders, Invitation_management* invitation_handeler){
    string username, match_type;
    if(orders[3] == "username"){
        username = orders[4];
        match_type = orders[6];
    }else{
        username = orders[6];
        match_type = orders[4];
    }Player* giver = data->players_list.find(username)->second;
    Invitation* new_invitation = invitation_handeler->make_invitations(data->on_username, username, match_type);
    giver->invitation_op(new_invitation->id, new_invitation, Invitation_code::invitation);
    cout << "OK" << endl;
}

void Post_input::invitation_extraction(vector<string>& orders){
    vector<string> new_order;
    for(size_t index = 0;index < orders.size();index++){
        if(index != orders.size() - 1){
            if(orders[index] == "POST"){
                int count = std::count(new_order.begin(), new_order.end(), "POST");
                if(count == 0){new_order.push_back("POST");}
            }else if(orders[index] == "?"){
                int count = std::count(new_order.begin(), new_order.end(), "?");
                if(count == 0){new_order.push_back("?");}    
            }else if(orders[index] == "invitation"){
                int count = std::count(new_order.begin(), new_order.end(), "invitation");
                if(count == 0){new_order.push_back("invitation");} 
            }else if(orders[index] == "username"){
                int count = std::count(new_order.begin(), new_order.end(), "username");
                if(count == 0){
                    new_order.push_back("username");
                    new_order.push_back(orders[index + 1]);
                } 
            }else if(orders[index] == "match_type"){
                int count = std::count(new_order.begin(), new_order.end(), "match_type");
                if(count == 0){
                    new_order.push_back("match_type");
                    new_order.push_back(orders[index + 1]);
                } 
            }
        }
    }orders = new_order;
}

void Post_management::invitation(vector<string>& orders, Invitation_management* invitation_handeler){
    try{
        post_input->invitation_extraction(orders);
        check_invitation(orders, invitation_handeler);
        invitation_core( orders, invitation_handeler);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}

void Post_management::start_player_check(int invitation_id){
    Invitation* temp = data->on_player->find_invitations(invitation_id, Finding_code::invitations);
    Player* temp_player = find_player(data, temp->sender_name);
    if(temp_player->show_playing() || data->on_player->show_playing()){
       throw Permission("Permission Denied");
    }else if(temp->match_type == "ranked"){
        string temp_level = temp_player->level_identification();
        string on_level = data->on_player->level_identification();

        if(on_level != temp_level){
            data->on_player->invitation_op(invitation_id, temp, Invitation_code::remove);
            throw Level("Level Mismatch");
        }
    }
}

void Post_management::check_start_match(vector<string>& orders){
    if(orders[2] == "?" && orders[3] == "invitation_id" && orders.size() == 5){
        string id = orders[4];
        if(id[0] != '\"'  || id[id.size() - 1] != '\"'){
            throw Format("Bad Request");
        }clear_cotation(orders);

        int invitation_id = stoi(orders[4]);

        if(data->on_admin != nullptr || data->on_player == nullptr){
            throw Format("Permission Denied");
        }else if(data->on_player->find_invitations(invitation_id, Finding_code::rejection) != nullptr){
            throw Existance("Not Found");
        }else if(data->on_player->find_invitations(invitation_id, Finding_code::invitations) == nullptr){
            throw Existance("Not Found");
        }else if(data->on_player->find_invitations(invitation_id, Finding_code::acception) != nullptr){
            throw Existance("Not Found");
        }else{
            start_player_check(invitation_id);
        }
    }else{throw Format("Bad Request");}
}

void Post_management::add_progress_match(Player* player_one, Player* player_two, const string& type){
    if(type == "casual"){
        Casual* new_match = new Casual(player_one, player_two, START_CASUAL);
        data->progress_match.emplace(player_one, new_match);
        data->progress_match.emplace(player_two, new_match);
    }else if(type == "ranked"){
        Ranked* new_match = new Ranked(player_one, player_two, START_RANK);
        new_match->apply_penalty();
        data->progress_match.emplace(player_one, new_match);
        data->progress_match.emplace(player_two, new_match);
    }
}

void Post_management::start_match_core(vector<string>& orders){
    int invitation_id = stoi(orders[4]);
    Invitation* invitation = data->on_player->find_invitations(invitation_id, Finding_code::invitations);
    Player* opponents = find_player(data, invitation->sender_name);

    opponents->changings(Change_code::change_status);
    data->on_player->changings(Change_code::change_status);

    add_progress_match(data->on_player, opponents, invitation->match_type);

    data->on_player->invitation_op(invitation_id, invitation, Invitation_code::acception);
    data->on_player->earse_invitation(invitation_id);
    cout << "OK" << endl;
}

void Post_input::start_match_extraction(vector<string>& orders){
    vector<string> new_order;
    for(size_t index = 0;index < orders.size();index++){
        if(index != orders.size() - 1){
            if(orders[index] == "POST"){
                int count = std::count(new_order.begin(), new_order.end(), "POST");
                if(count == 0){new_order.push_back("POST");}
            }else if(orders[index] == "?"){
                int count = std::count(new_order.begin(), new_order.end(), "?");
                if(count == 0){new_order.push_back("?");}    
            }else if(orders[index] == "start_match"){
                int count = std::count(new_order.begin(), new_order.end(), "start_match");
                if(count == 0){new_order.push_back("start_match");} 
            }else if(orders[index] == "invitation_id"){
                int count = std::count(new_order.begin(), new_order.end(), "invitation_id");
                if(count == 0){
                    new_order.push_back("invitation_id");
                    new_order.push_back(orders[index  + 1]);
                } 
            }
        }
    }orders = new_order;
}

void Post_management::start_match(vector<string>& orders){
    try{
        post_input->start_match_extraction(orders);
        check_start_match(orders);
        start_match_core(orders);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}

void Post_management::check_rejection(vector<string>& orders){
    if(orders.size() == 5 && orders[2] == "?" && orders[3] == "invitation_id"){
        string id = orders[4];
        if(id[0] != '\"' || id[id.size() - 1] != '\"'){
            throw Format("Bad Request");
        }clear_cotation(orders);

        for(auto letter : orders[4]){
            if(!isdigit(letter)){throw Format("Bad Request");}
        }int invitation_id = stoi(orders[4]);

        if(data->on_admin != nullptr){
            throw Permission("Permission Denied");
        }else if(data->on_player == nullptr){
            throw Permission("Permission Denied");
        }else if(data->on_player->find_invitations(invitation_id, Finding_code::invitations) == nullptr){
            throw Existance("Not Found");
        }else if(data->on_player->find_invitations(invitation_id, Finding_code::rejection) != nullptr){
            throw Existance("Not Found");
        }else if(data->on_player->find_invitations(invitation_id, Finding_code::acception) != nullptr){
            throw Existance("Not Found");
        }
    }else{throw Format("Bad Request");}
}

void Post_management::rejection_core(vector<string>& orders){
    int invitation_id = stoi(orders[4]);
    Invitation* invitation = data->on_player->find_invitations(invitation_id, Finding_code::invitations);
    data->on_player->invitation_op(invitation_id, invitation, Invitation_code::rejection);
    data->on_player->earse_invitation(invitation_id);
    cout << "OK" << endl;
}

void Post_input::reject_invitation_extraction(vector<string>& orders){
    vector<string> new_order;
    for(size_t index = 0;index < orders.size();index++){
        if(index != orders.size() - 1){
            if(orders[index] == "POST"){
                int count = std::count(new_order.begin(), new_order.end(), "POST");
                if(count == 0){new_order.push_back("POST");}
            }else if(orders[index] == "?"){
                int count = std::count(new_order.begin(), new_order.end(), "?");
                if(count == 0){new_order.push_back("?");}    
            }else if(orders[index] == "reject_invitation"){
                int count = std::count(new_order.begin(), new_order.end(), "reject_invitation");
                if(count == 0){new_order.push_back("reject_invitation");} 
            }else if(orders[index] == "invitation_id"){
                int count = std::count(new_order.begin(), new_order.end(), "invitation_id");
                if(count == 0){
                    new_order.push_back("invitation_id");
                    new_order.push_back(orders[index  + 1]);
                } 
            }
        }
    }orders = new_order;
}

void Post_management::rejection(vector<string>& orders){
    try{
        post_input->reject_invitation_extraction(orders);
        check_rejection(orders);
        rejection_core(orders);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}

void Post_management::second_check_report(vector<string>& orders){
    if(data->on_admin == nullptr && data->on_player == nullptr){
        throw Permission("Permission Denied");
    }else if(data->on_admin != nullptr && data->on_player == nullptr){
        throw Permission("Permission Denied");
    }
    string username, reason;
    username_reason(orders, username, reason);
    
    if(username[0] != '\"' || username[username.size() - 1] != '\"'){
        throw Format("Bad Request");
    }else if(reason[0] != '\"' || reason[reason.size() - 1] != '\"'){
        throw Format("Bad Request"); 
    }
    
    clear_cotation(orders);
    username_reason(orders, username, reason);

    if(data->players_list.find(username) == data->players_list.end()){
        throw Existance("Not Found");
    }
}

void Post_management::check_report(vector<string>& orders){
    if(orders[2] == "?" && orders.size() >= 7){
        if(orders[3] == "username" && orders[5] == "reason"){
            if(orders[6] == "\"\""){throw Format("Bad Request");}
            second_check_report(orders);
        }else if(orders[3] == "reason" && orders[5] == "username"){
            if(orders[4] == "\"\""){throw Format("Bad Request");}
            second_check_report(orders);
        }else{throw Format("Bad Request");}
    }else{throw Format("Bad Request");}
}

void Post_management::report_core(vector<string>& orders,Report_management* report_manger){
    string reported_name, reason;
    username_reason(orders, reported_name, reason);

    Report* new_report = report_manger->make_reports(data->on_player->get_name(),reported_name,reason);
    data->reports.emplace(new_report->report_id, new_report);
    cout << "OK" << endl;
}

void Post_input::report_extraction(vector<string>& orders){
    vector<string>new_order;
    bool cotation_pass = false;
    bool reason_pass = false;
    string reason = "";
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "POST"){
            int count  = std::count(new_order.begin(), new_order.end(), "POST");
            if(count == 0){new_order.push_back("POST");}
        }else if(orders[index] == "report"){
            int count  = std::count(new_order.begin(), new_order.end(), "report");
            if(count == 0){new_order.push_back("report");} 
        }else if(orders[index] == "username"){
            int count  = std::count(new_order.begin(), new_order.end(), "username");
            if(count == 0){
                new_order.push_back("username");
                new_order.push_back(orders[index + 1]);
            }  
        }else if(orders[index] == "reason"){
            int count  = std::count(new_order.begin(), new_order.end(), "reason");
            if(count == 0){
                new_order.push_back("reason");
                reason_pass = true;
            } 
        }else if(orders[index] == "?"){            
            int count  = std::count(new_order.begin(), new_order.end(), "?");
            if(count == 0){new_order.push_back("?");} 
        }if(reason_pass){
            if(orders[index][0] == '\"'){cotation_pass = true;}
            if(cotation_pass){
                reason += orders[index];
                if(index != orders.size() - 1){reason += " ";}
            }if(orders[index][orders[index].size() - 1] == '\"'){
                cotation_pass = false;reason_pass = false;
                new_order.push_back(reason);
            }
        }
    }orders = new_order;
}

void Post_management::report(vector<string>& orders,Report_management* report_manger){
    try{
        post_input->report_extraction(orders);
        check_report(orders);
        report_core(orders, report_manger);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}


void Post_management::second_action_check(vector<string>& orders){
    Match* current_match = find_match(data->progress_match, data->on_player);

    if(data->on_player == nullptr || data->on_admin != nullptr){
        throw Permission("Permission Denied");
    }else if(current_match == nullptr){
        throw Existance("Not Found");
    }else if(!current_match->can_move(data->on_player)){
        throw Permission("Permission Denied");
    }else{
        current_match->shoot_validation(orders, data->on_player);
    }
}

void Post_management::check_action(vector<string>& orders){
    clear_cotation(orders);
    if(orders[2] == "?" && orders[3] == "action"){
        if(orders[4] == "shoot" || orders[4] == "defend" || orders[4] == "reload"){
            second_action_check(orders);
        }else{throw Format("Bad Request");}
    }else{throw Format("Bad Request");}
}

void Post_input::action_extraction(vector<string>& orders){
    vector<string> new_order;
    for(size_t i = 0; i < orders.size(); ++i){
        if(i != orders.size() - 1){
            if(orders[i] == "POST"){
                if(std::count(new_order.begin(), new_order.end(), "POST") == 0)
                    new_order.push_back("POST");
            }else if(orders[i] == "?"){
                if(std::count(new_order.begin(), new_order.end(), "?") == 0)
                    new_order.push_back("?");
            }else if(orders[i] == "action"){
                if(std::count(new_order.begin(), new_order.end(), "action") == 0){
                    new_order.push_back("action");
                }else if(std::count(new_order.begin(), new_order.end(), "action") == 1){
                    new_order.push_back("action");
                    new_order.push_back(orders[i+1]); 
                }
            }
        }
    }orders = new_order;
}

void Post_management::action_core(vector<string>& orders){
    Match* match = find_match(data->progress_match, data->on_player);
    match->action(data->progress_match, orders, data->on_player);
}

void Post_management::action(vector<string>& orders){
    try{
        post_input->action_extraction(orders);
        check_action(orders);
        action_core(orders);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}

void Post_input::dismiss_report_extraction(vector<string>& orders){
    vector<string>new_order;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "POST"){
            int count = std::count(new_order.begin(), new_order.end(), "POST");
            if(count == 0){new_order.push_back("POST");}
        }else if(orders[index] == "dismiss_report"){
            int count = std::count(new_order.begin(), new_order.end(), "dismiss_report");
            if(count == 0){new_order.push_back("dismiss_report");}
        }else if(orders[index] == "report_id"){
            int count = std::count(new_order.begin(), new_order.end(), "report_id");
            if(count == 0){
                new_order.push_back("report_id");
                new_order.push_back(orders[index + 1]);
            }
        }else if(orders[index] == "?"){
            int count = std::count(new_order.begin(), new_order.end(), "?");
            if(count == 0){new_order.push_back("?");}
        }
    }orders = new_order;
}

void Post_management::check_dissmis_report(vector<string>& orders){
    if(orders.size() == 5 && orders[2] == "?" && orders[3] == "report_id"){
        if(orders[4][0] == '\"' && orders[4][orders[4].size() - 1] == '\"'){
            if(data->on_admin == nullptr){
                throw Permission("Permission Denied");
            }else if(data->on_player != nullptr){
                throw Permission("Permission Denied");
            }else{
                clear_cotation(orders);
                int report_id = stoi(orders[4]);
                if(data->reports.find(report_id) == data->reports.end()){
                    throw Existance("Not Found");
                }
            }
        }else{throw Format("Bad Request");}
    }else{throw Format("Bad Request");}
}

void Post_management::dismiss_report_core(vector<string>& orders){
    int report_id = stoi(orders[4]);
    auto target = data->reports.find(report_id);
    data->reports.erase(target);
    cout << "OK" << endl;
}

void Post_management::dismiss_report(vector<string>& orders){
    try{
       post_input->dismiss_report_extraction(orders);
       check_dissmis_report(orders);
       dismiss_report_core(orders);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}

void Post_input::block_extraction(vector<string>& orders){
    vector<string>new_order;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "POST"){
            int count = std::count(new_order.begin(), new_order.end(), "POST");
            if(count == 0){new_order.push_back("POST");}
        }else if(orders[index] == "block"){
            int count = std::count(new_order.begin(), new_order.end(), "block");
            if(count == 0){new_order.push_back("block");}
        }else if(orders[index] == "status"){
            int count = std::count(new_order.begin(), new_order.end(), "status");
            if(count == 0){
                new_order.push_back("status");
                new_order.push_back(orders[index + 1]);
            }
        }else if(orders[index] == "username"){
            int count = std::count(new_order.begin(), new_order.end(), "username");
            if(count == 0){
                new_order.push_back("username");
                new_order.push_back(orders[index + 1]);
            }
        }else if(orders[index] == "?"){
            int count = std::count(new_order.begin(), new_order.end(), "?");
            if(count == 0){new_order.push_back("?");}
        }
    }orders = new_order;
}

void Post_management::second_check_block(vector<string>& orders){
    clear_cotation(orders);
    string username, status;
    username_status(orders, username, status);
    Player* target = find_player(data, username);

    if(data->on_player == nullptr){
        throw Permission("Permission Denied");
    }else if(data->on_admin != nullptr){
        throw Permission("Permission Denied");
    }else if(data->admins_list.find(username) != data->admins_list.end()){
        throw Format("Bad Request");
    }else if(target == nullptr){
        throw Existance("Not Found");
    }
}

void Post_management::check_block(vector<string>& orders){
    if(orders.size() == 7 && orders[2] == "?"){
        if(orders[5] == "username" && orders[3] == "status"){
            string username = orders[6];
            if(orders[4] != "\"blocked\"" && orders[4] != "\"unblocked\""){
               throw Format("Bad Request");
            }else if(username[0] != '\"' || username[username.size() - 1] != '\"'){
                throw Format("Bad Request");
            }second_check_block(orders);
        }else if(orders[3] == "username" && orders[5] == "status" ){
            string username = orders[4];
            if(orders[6] != "\"blocked\"" && orders[6] != "\"unblocked\""){
               throw Format("Bad Request");
            }else if(username[0] != '\"' || username[username.size() - 1] != '\"'){
                throw Format("Bad Request");
            }second_check_block(orders);
        }else{throw Format("Bad Request");}
    }else{throw Format("Bad Request");}
}

void Post_management::block_core(vector<string>& orders){
    string username, status;
    username_status(orders, username, status);
    Player* blocked_player = find_player(data, username);
    if(status == "blocked"){
        data->on_player->blockings(Block_code::block, username, blocked_player);
        cout << "OK" << endl;
    }else if(status == "unblocked"){
        data->on_player->blockings(Block_code::unblock, username, blocked_player);
        cout << "OK" << endl;
    }
}

void Post_management::block(vector<string>& orders){
    try{
        post_input->block_extraction(orders);
        check_block(orders);
        block_core(orders);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}

void Post_input::penalty_extraction(vector<string>& orders){
    vector<string>new_order;
    int post_count = 0;int penalty_count = 0;int report_id_count = 0;
    int type_count = 0;int amount_count = 0;int q_count = 0;
    int number_of_matched_count = 0;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "POST"){
            if(post_count == 0){new_order.push_back("POST");post_count++;}
        }else if(orders[index] == "penalty"){
            if(penalty_count == 0){new_order.push_back("penalty");penalty_count++;}
        }else if(orders[index] == "report_id"){
            if(report_id_count == 0){
                new_order.push_back("report_id");
                new_order.push_back(orders[index + 1]);
                report_id_count++;
            }
        }else if(orders[index] == "type"){
            if(type_count == 0){
                new_order.push_back("type");
                new_order.push_back(orders[index + 1]);
                type_count++;
            }
        }else if(orders[index] == "amount"){
            if(amount_count == 0){
                new_order.push_back("amount");
                new_order.push_back(orders[index + 1]);
                amount_count++;
            }
        }else if(orders[index] == "?"){
            if(q_count == 0){new_order.push_back("?");q_count++;}
        }else if(orders[index] == "number_of_matches"){
            if(number_of_matched_count == 0){
                new_order.push_back("number_of_matches");
                new_order.push_back(orders[index + 1]);
                number_of_matched_count++;
            }
        }
    }orders = new_order;
}

void Post_management::penalty_parameter_check(vector<string>& orders){
    string type, report_id, amount, number_of_matches;
    penalty_parameter(amount, type, report_id, number_of_matches, orders);

    if(type.empty() || report_id.empty() || amount.empty() || number_of_matches.empty())
        throw Format("Bad Request");
    
    if(amount[0] != '\"' || amount[amount.size() - 1] != '\"')
        throw Format("Bad Request");
        
    if(number_of_matches[0] != '\"' || number_of_matches[number_of_matches.size() - 1] != '\"') // باگ == به != اصلاح شد
        throw Format("Bad Request");
        
    if(report_id[0] != '\"' || report_id[report_id.size() - 1] != '\"')
        throw Format("Bad Request");

    if(type == "\"health_penalty\""){
        int value = stoi(amount.substr(1, amount.size() - 2));
        if(value > 2 || value <= 0){throw Format("Bad Request");}
    }else if(type == "\"bullet_penalty\""){
        int value = stoi(amount.substr(1, amount.size() - 2));
        if(value <= 0 || value > 3){throw Format("Bad Request");}
    }else{
        throw Format("Bad Request");
    }

    int number = stoi(number_of_matches.substr(1, number_of_matches.size() - 2));
    if(number <= 0){throw Format("Bad Request");}

    int id = stoi(report_id.substr(1, report_id.size() - 2));
    if(data->reports.find(id) == data->reports.end()){
        throw Existance("Not Found");
    }
}


void Post_management::check_penalty(vector<string>& orders){
    if(orders.size() == 11 && orders[2] == "?"){
        if(data->on_player != nullptr){
            throw Permission("Permission Denied");
        }else if(data->on_admin == nullptr){
            throw Permission("Permission Denied");
        }else{
            penalty_parameter_check(orders);
        }
    }else{throw Format("Bad Request");}
}

void Post_management::penalty_core(vector<string>& orders){
    clear_cotation(orders);
    string type, report_id, amount, number_of_matches;
    penalty_parameter(amount, type, report_id, number_of_matches, orders);
    Penalty new_penalty = Penalty(type, stoi(amount), stoi(number_of_matches), stoi(report_id));

    Report* report = data->reports.find(new_penalty.id)->second;
    Player* guilty = find_player(data, report->reported_username);
    guilty->initalize_penalty(new_penalty);
    erase_report(report->report_id, data->reports);
    cout << "OK" << endl;
}

void Post_management::penalty(vector<string>& orders){
    try{
        post_input->penalty_extraction(orders);
        check_penalty(orders);
        penalty_core(orders);
    }catch(const Existance& error){
        cout << error.what() << '\n';
    }catch(const Level& error){
        cout << error.what() << '\n';
    }catch(const Permission& error){
        cout << error.what() << '\n';
    }catch(const Format& error){
        cout << error.what() << '\n';
    } 
}