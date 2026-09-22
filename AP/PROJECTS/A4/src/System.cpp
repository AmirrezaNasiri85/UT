#include "System.hpp"

void System::free_requests(){
    for(auto& obj : requests){
        delete(obj);
    }
}

void System::remove_request(Request* request){
    for(auto it = requests.begin();it != requests.end();it++){
        if(*it == request){
            requests.erase(it);
            break;
        }
    }
}

Request* System::find_request(const int id){
    for(auto& obj : requests){
        if(obj->request_id == id){
            return obj;
        }
    }
    return nullptr;
}

void System::add_request(Request* request){
    requests.push_back(request);
}

void System::free_company(){
    for(auto& obj : companies){
        delete(obj.second);
    }
}

void System::free_stockholder(){
    for(auto& obj : stockholders){
        obj.second->total_free();
        delete(obj.second);
    }
}

void System::total_free(){
    free_requests();
    free_stockholder();
    free_company();
}

void System::transfer(Stockholder* buyer, Stockholder* seller,Request* matched_request, Company* company){
    int money = matched_request->price * matched_request->shares_count;
    buyer->buy_finance(money, matched_request, company);
    seller->sell_finance(money, matched_request);
    company->change_price(matched_request->price);
    if(matched_request->is_selling){
        company->erase_sells_request(matched_request);
    }else{
        company->erase_buy_request(matched_request);
    }
    remove_request(matched_request);
}

void System::allocate_request_id(Request* request){
    request->request_id = request_id;
    request_id++;
}

Stockholder* System::find_stockholder(const string& username){
    auto obj = stockholders.find(username);
    if(obj == stockholders.end()){
        return nullptr;
    }
    return obj->second;
}

bool System::username_existance(const string& username){
    if(stockholders.find(username) == stockholders.end()){
        return false;
    }return true;
}

void System::add_stockholder(Stockholder* new_stockholder, const string& name){
    stockholders.emplace(name,new_stockholder);
}

Company* System::find_company(const string& name){
    for(auto const& obj : companies){
        if(obj.first == name){
            return obj.second;
        }
    }
    return nullptr;
}

void System::add_Company(Company* new_company, const string& name){
    companies.emplace(name, new_company);
}