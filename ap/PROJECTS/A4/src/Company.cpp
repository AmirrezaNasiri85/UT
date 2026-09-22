#include "Company.hpp"


void Company::erase_buy_request(Request* request){
    for(auto it = buys.begin();it != buys.end();it++){
        if(*it == request){
            buys.erase(it);
            break;
        }
    }
}

void Company::remove_request(Request* request){
    if(request->is_selling){
        erase_sells_request(request);
    }else{
        erase_buy_request(request);
    }
}

bool Company::request_buys_existance(Request* request){
    for(auto& obj : buys){
        if(obj->username == request->username){return false;}
    }
    return true;
}

void Company::change_price(const int moeny){
    price = moeny;
}

void Company::erase_sells_request(Request* request){
    for(auto it = sells.begin();it != sells.end();it++){
        if(*it == request){
            sells.erase(it);
            return;
        }
    }
}

Request* Company::find_buy_request(Request* request){
    Request* temp = nullptr;
    for(auto& obj : buys){
        if(obj->price == request->price && obj->shares_count == request->shares_count
            && obj->company_name == request->company_name){
                if(temp == nullptr || temp->request_id > obj->request_id){
                    temp = obj;
                }
        }
    } 
    return temp;
}

Request* Company::sell_match(Request* request){
    Request* temp = find_buy_request(request);
    if(temp == nullptr){
        sells.push_back(request);
        cout << "Order " << request->request_id << " queued." << endl;
        return nullptr;
    }return temp;
}

Request* Company::find_sells_request(Request* request){
    Request* temp = nullptr;
    for(auto& obj : sells){
        if(obj->price == request->price && obj->shares_count == request->shares_count
            && obj->company_name == request->company_name){
            if(temp == nullptr || temp->request_id > obj->request_id){
                temp = obj;
            }
        }
    }
    return temp;
}

Request* Company::buy_match(Request* request){
    Request* temp = find_sells_request(request);
    if(temp == nullptr){
        buys.push_back(request);
        cout << "Order " << request->request_id << " queued. " << endl;
        return nullptr;
    }return temp;
}

bool Company::buy_validation(const string& username){
    for(auto& request : sells){
        if(request->username == username){
            return false;
        }
    }
    return true;
}

void Company::print_buys(){
    cout << "buy queue: " << endl;
    if(buys.empty()){
        cout << "(empty)" << endl;
        return;
    }
    
    buys.sort(sort_request_greater);

    int buys_number = 1;
    for(auto& obj : buys){
        cout << buys_number << ". "
            << "Shares: " << obj->shares_count << " - "
            << "Price: $" << obj->price << " - "
            << "ID: " << obj->request_id << endl;
        buys_number++;
    }
}

void Company::print_sells(){
    cout << "sell queue: " << endl;
    if(sells.empty()){
        cout << "(empty)" << endl;
        return;
    }
    
    sells.sort(sort_request_lesser);

    int sells_number = 1;
    for(auto& obj : sells){
        cout << sells_number << ". "
            << "Shares: " << obj->shares_count << " - "
            << "Price: $" << obj->price << " - "
            << "ID: " << obj->request_id << endl;
        sells_number++;
    }
}

void Company::print_company_info(){
    cout << name << " report" << endl
        << "Current price: $" << price << endl;
    print_sells();
    print_buys();
}

int Company::get_price(){
    return price;
}

Company::Company(const string& name, int price)
: name(name), price(price){
}