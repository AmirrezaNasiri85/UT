#include "GetManagement.hpp"


Get_management::Get_management(Data_base* given_base)
    : data(given_base){
}

Get_management::~Get_management(){
    delete(get_input);
}

string Get_management::find_mathod(vector<string>& orders){
    bool find_word = false;
    for(auto word : orders){
        if(get_methods.find(word) != get_methods.end()){
            find_word = true;
            return word;
        }
    }if(!find_word){
        throw Existance("Not Found");
    }return "";
}

void Get_management::second_layer_match_check(){
    if(data->on_player == nullptr || data->on_admin != nullptr){
        throw Permission("Permission Denied");
    }else if(data->casual_options.empty()){
        throw Existance("Empty");
    }else if(data->casual_options.size() == 1){
        auto it = find(data->casual_options.begin(),
                data->casual_options.end(), data->on_player);
        if(it != data->casual_options.end()){
            throw Existance("Empty");
        }
    }
}

void Get_management::check_casual_match_opponents(vector<string>& orders){
    if(orders[2] == "?"){
        if(orders.size() == 3){
            second_layer_match_check();
        }else if(orders.size() == 5 && orders[3] == "sort_order"){
            if(orders[4] == "\"asc\""){
                second_layer_match_check();
            }else if(orders[4] == "\"desc\"" && orders[3] == "sort_order"){  
                second_layer_match_check();
            }else{throw Format("Bad Request");}
        }else{throw Format("Bad Request");}
    }else{throw Format("Bad Request");}
}

void Get_management::casual_match_opponents_core(vector<string>& orders){
    clear_cotation(orders);
    if(orders.size() == 3 || (orders.size() == 5 && orders[4] == "desc")){
       data->casual_options.sort(sort_XP_desc);
    }else if(orders.size() == 5 && orders[4] == "asc"){
        data->casual_options.sort(sort_XP_asc);
    }print_casual_players(data);
}

void Get_input::casual_match_opponents_extraction(vector<string>& orders){
    vector<string> new_orders;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "GET"){
            int count = std::count(new_orders.begin(), new_orders.end(), "GET");
            if(count == 0){new_orders.push_back(orders[index]);}
        }else if(orders[index] == "casual_match_opponents"){
            int count = std::count(new_orders.begin(), new_orders.end(), "casual_match_opponents");
            if(count == 0){new_orders.push_back(orders[index]);}   
        }else if(orders[index] == "?"){
            int count = std::count(new_orders.begin(), new_orders.end(), "?");
            if(count == 0){new_orders.push_back(orders[index]);}        
        }else if(orders[index] == "sort_order"){
            int count = std::count(new_orders.begin(), new_orders.end(), "sort_order");
            if(count == 0){
                new_orders.push_back(orders[index]);
                new_orders.push_back(orders[index + 1]);
            } 
        }
    }orders = new_orders;
}

void Get_management::casual_match_opponents(vector<string>& orders){
    try{
        get_input->casual_match_opponents_extraction(orders);
        check_casual_match_opponents(orders);
        casual_match_opponents_core(orders);  
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

void Get_management::check_profile(vector<string>& orders){
    if(orders[2] == "?"){
        if(orders.size() == 3){
            if(data->on_player == nullptr && data->on_admin == nullptr){
                throw Permission("Permission Denied");
            }else if(data->on_admin != nullptr){
                throw Permission("Permission Denied");
            }
        }else if(orders.size() == 5){
            string username = orders[4];
            if(username[0] != '\"' || username[username.size() - 1] != '\"'){
                throw Format("Bad Request");
            }clear_cotation(orders);
            username = orders[4];

            if(data->on_player == nullptr && data->on_admin == nullptr){
                    throw Permission("Permission Denied");
            }else if(orders[3] == "username"){
                if(data->admins_list.find(username) != data->admins_list.end()){
                    throw Permission("Permission Denied");
                }else if(data->players_list.find(username) == data->players_list.end()){
                    throw Existance("Not Found");
                }
            }else{throw Format("Bad Request");}
        }else{throw Format("Bad Request");} 
    }else{throw Format("Bad Request");}
}

void Get_management::profile_core(vector<string>& orders){
    if(orders.size() == 5){
        string username = orders[4];
        Player* target = data->players_list.find(username)->second;
        target->printings(Printing_code::information);
    }else if(orders.size() == 3){
        data->on_player->printings(Printing_code::information);
    }
}

void Get_input::profile_extraction(vector<string>& orders){
    vector<string> new_orders;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "GET"){
            int count = std::count(new_orders.begin(), new_orders.end(), "GET");
            if(count == 0){new_orders.push_back(orders[index]);}
        }else if(orders[index] == "profile"){
            int count = std::count(new_orders.begin(), new_orders.end(), "profile");
            if(count == 0){new_orders.push_back(orders[index]);}   
        }else if(orders[index] == "?"){
            int count = std::count(new_orders.begin(), new_orders.end(), "?");
            if(count == 0){new_orders.push_back(orders[index]);}        
        }else if(orders[index] == "username"){
            int count = std::count(new_orders.begin(), new_orders.end(), "username");
            if(count == 0){
                new_orders.push_back(orders[index]);
                new_orders.push_back(orders[index + 1]);
            }  
        }
    }orders = new_orders;
}

void Get_management::profile(vector<string>& orders){
    try{
        get_input->profile_extraction(orders);
        check_profile(orders);
        profile_core(orders);
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

void Get_management::check_received_invitations(vector<string>& orders){
    if(orders.size() == 3 && orders[2] == "?"){
        if(data->on_admin != nullptr || data->on_player == nullptr){
            throw Permission("Permission Denied");
        }
    }else{throw Format("Bad Request");}
}

void Get_management::received_invitations_core(){
    data->on_player->printings(Printing_code::invitations);
}

void Get_input::received_invitation_extraction(vector<string>& orders){
    vector<string> new_orders;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "GET"){
            int count = std::count(new_orders.begin(), new_orders.end(), "GET");
            if(count == 0){new_orders.push_back(orders[index]);}
        }else if(orders[index] == "received_invitations"){
            int count = std::count(new_orders.begin(), new_orders.end(), "received_invitations");
            if(count == 0){new_orders.push_back(orders[index]);}   
        }else if(orders[index] == "?"){
            int count = std::count(new_orders.begin(), new_orders.end(), "?");
            if(count == 0){new_orders.push_back(orders[index]);}        
        }
    }orders = new_orders;
}

void Get_management::received_invitations(vector<string>& orders){
    try{
        get_input->received_invitation_extraction(orders);
        check_received_invitations(orders);
        received_invitations_core();
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

void Get_management::check_reports(vector<string>& orders){
    if(orders[2] == "?" && orders.size() == 3){
        if(data->on_player == nullptr && data->on_admin == nullptr){
            throw Permission("Permission Denied");
        }else if(data->on_player != nullptr && data->on_admin == nullptr){
            throw Permission("Permission Denied");
        }else if(data->reports.empty()){
            throw Existance("Empty");
        }
    }else{throw Format("Bad Request");}
}

void Get_management::reports_core(){
    print_reports(data);
}

void Get_input::reports_extraction(vector<string>& orders){
    vector<string> new_orders;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "GET"){
            int count = std::count(new_orders.begin(), new_orders.end(), "GET");
            if(count == 0){new_orders.push_back(orders[index]);}
        }else if(orders[index] == "reports"){
            int count = std::count(new_orders.begin(), new_orders.end(), "reports");
            if(count == 0){new_orders.push_back(orders[index]);}   
        }else if(orders[index] == "?"){
            int count = std::count(new_orders.begin(), new_orders.end(), "?");
            if(count == 0){new_orders.push_back(orders[index]);}        
        }
    }orders = new_orders; 
}

void Get_management::reports(vector<string>& orders){
    try{
        get_input->reports_extraction(orders);
        check_reports(orders);
        reports_core();
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

void Get_management::check_match_status(vector<string>& orders){
    if(orders.size() == 3 && orders[2] == "?"){
        if(data->on_player == nullptr){
            throw Permission("Permission Denied");
        }else if(data->on_admin != nullptr){
            throw Permission("Permission Denied");
        }else if(data->progress_match.find(data->on_player) == data->progress_match.end()){
            throw Existance("Not Found");
        }
    }else{throw Format("Bad Request");}
}
  
void Get_management::match_status_core(){
    Match* match = data->progress_match.find(data->on_player)->second;

    match->print_information(data->on_player);
}

void Get_input::match_status_extraction(vector<string>& orders){
    vector<string> new_orders;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "GET"){
            int count = std::count(new_orders.begin(), new_orders.end(), "GET");
            if(count == 0){new_orders.push_back("GET");}
        }else if(orders[index] == "match_status"){
            int count = std::count(new_orders.begin(), new_orders.end(), "match_status");
            if(count == 0){new_orders.push_back("match_status");}   
        }else if(orders[index] == "?"){
            int count = std::count(new_orders.begin(), new_orders.end(), "?");
            if(count == 0){new_orders.push_back("?");}        
        }
    }orders = new_orders;  
}

void Get_management::match_status(vector<string>& orders){
    try{
        get_input->match_status_extraction(orders);
        check_match_status(orders);
        match_status_core();
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

void Get_input::ranked_match_opponents_extraction(vector<string>& orders){
    vector<string> new_orders;
    for(size_t index = 0;index < orders.size();index++){
        if(orders[index] == "GET"){
            int count = std::count(new_orders.begin(), new_orders.end(), "GET");
            if(count == 0){new_orders.push_back(orders[index]);}
        }else if(orders[index] == "ranked_match_opponents"){
            int count = std::count(new_orders.begin(), new_orders.end(), "ranked_match_opponents");
            if(count == 0){new_orders.push_back(orders[index]);}   
        }else if(orders[index] == "?"){
            int count = std::count(new_orders.begin(), new_orders.end(), "?");
            if(count == 0){new_orders.push_back(orders[index]);}        
        }else if(orders[index] == "sort_order"){
            int count = std::count(new_orders.begin(), new_orders.end(), "sort_order");
            if(count == 0){
                new_orders.push_back("sort_order");
                new_orders.push_back(orders[index + 1]);
            }   
        }
    }orders = new_orders;  
}

void Get_management::check_ranked_match_opponents(vector<string>& orders){
    if((orders.size() == 5 || orders.size() == 3) && orders[2] == "?"){
        if(data->on_admin != nullptr){
            throw Permission("Permission Denied");
        }else if(data->on_player == nullptr){
            throw Permission("Permission Denied");
        }else if(orders.size() == 5){
            if(orders[3] == "sort_order"){
                if(orders[4] != "\"asc\"" && orders[4] != "\"desc\""){
                    throw Format("Bad Request");
                }
            }else{throw Format("Bad Request");}
        }fill_rank_options(data->on_player, data);
        if(data->rank_options.empty()){
            throw Existance("Empty");
        }else if(data->rank_options.size() == 1){
            auto obj = data->rank_options.front();
            if(obj == data->on_player){
                throw Existance("Empty");
            }
        }
    }else{throw Format("bad Request");}
}

void Get_management::ranked_match_opponents_core(vector<string>& orders){
    
    if(orders.size() == 3 || (orders[4] == "\"desc\"" && orders.size() == 5)){
        data->rank_options.sort(sort_Rp_desc);       
    }else if(orders[4] == "\"asc\""){
        data->rank_options.sort(sort_RP_asc);
    }print_ranked_players(data);
}

void Get_management::ranked_match_opponents(vector<string>& orders){
    try{
        get_input->ranked_match_opponents_extraction(orders);
        check_ranked_match_opponents(orders);
        ranked_match_opponents_core(orders);
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