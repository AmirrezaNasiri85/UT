#include "SystemManager.hpp"



void System::add_new_admin(string& username, Admin* new_admin){
    data_base->admins_list.emplace(username, new_admin);
}

void System::add_new_player(string& username, Player* new_player){
    data_base->players_list.emplace(username, new_player);
}

System::System(Data_base* given_base)
    : data_base(given_base){
    post_manager = new Post_management(given_base);
    get_manager = new Get_management(given_base);
    invitation_manger = new Invitation_management();
    report_manger = new Report_management();
    delet_manager = new Delet_management();
    put_management = new Put_management();
}

System::~System(){
    delete(post_manager);
    delete(get_manager);
    delete(delet_manager);
    delete(put_management);
    delete(data_base);
    delete(report_manger);
    delete(invitation_manger);
}

void System::post_functions(vector<string>& orders){
    try{
        string word = post_manager->find_mathod(orders);
        if(word == "register"){
            post_manager->registerr(orders);
        }else if(word == "login"){
            post_manager->login(orders);
        }else if(word == "logout"){
            post_manager->logout(orders);
        }else if(word == "casual_match_ready"){
            post_manager->casual_match_ready(orders);
        }else if(word == "invitation"){
            post_manager->invitation(orders, invitation_manger);
        }else if(word == "start_match"){
            post_manager->start_match(orders);
        }else if(word == "reject_invitation"){
            post_manager->rejection(orders);
        }else if(word == "report"){
            post_manager->report(orders, report_manger);
        }else if(word == "action"){
            post_manager->action(orders);
        }else if(word == "dismiss_report"){
            post_manager->dismiss_report(orders);
        }else if(word == "block"){
            post_manager->block(orders);
        }else if(word == "penalty"){
            post_manager->penalty(orders);
        }
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

void System::get_functions(vector<string>& orders){
    try{
        string word = get_manager->find_mathod(orders);
        if(word == "casual_match_opponents"){  
            get_manager->casual_match_opponents(orders);
        }else if(word == "profile"){
            get_manager->profile(orders);
        }else if(word == "received_invitations"){
            get_manager->received_invitations(orders);
        }else if(word == "reports"){
            get_manager->reports(orders);
        }else if(word == "match_status"){
            get_manager->match_status(orders);
        }else if(word == "ranked_match_opponents"){
            get_manager->ranked_match_opponents(orders);
        }
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

void System::delet_functions(vector<string>& orders){
    try{
        string word = delet_manager->find_mathod(orders);

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

void System::put_functions(vector<string>& orders){
    try{
        string word = put_management->find_mathod(orders);

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