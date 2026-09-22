#include "Stockholder.hpp"



void Stockholder::free_lock_stocks(){
    auto it = locked_Stock.begin();
    while (it != locked_Stock.end()) {
        delete *it; 
        it = locked_Stock.erase(it); 
    }
}

void Stockholder::free_free_stocks(){
    auto it = free_stokcs.begin();
    while (it != free_stokcs.end()){
        delete *it;
        it = free_stokcs.erase(it);
    }
}

void Stockholder::total_free(){
    free_free_stocks();
    free_lock_stocks();
}

void Stockholder::earse_lock_shares(Stock* deleted){
    for(auto it = locked_Stock.begin();it != locked_Stock.end();it++){
        if(*it == deleted){
            locked_Stock.erase(it);
            return;
        }
    }   
}

void Stockholder::erase_free_stock(Stock* deleted){
    for(auto it = free_stokcs.begin();it != free_stokcs.end();it++){
        if(*it == deleted){
            free_stokcs.erase(it);
            return;
        }
    }
}

void Stockholder::lock_shares(Request* request, Company* company){
    for(auto& obj : free_stokcs){
        if(obj->name == request->company_name){
            obj->count -= request->shares_count;
            if(obj->count == 0){
                erase_free_stock(obj);
            }for(auto& lock_share : locked_Stock){
                if(lock_share->name == request->company_name){
                    lock_share->count += request->shares_count;
                    return;
                }
            }
            Stock* new_stock = new Stock(request->shares_count, request->company_name, company);
            locked_Stock.emplace(new_stock);
            return;
        }
    }
}

void Stockholder::cancel_sell_finance(const int money, Request* request){
    for(auto& stock : locked_Stock){
        if(stock->name == request->company_name){
            stock->count -= request->shares_count;
            if(stock->count == 0){
                earse_lock_shares(stock);
            }
            for(auto& obj : free_stokcs){
                if(obj->name == request->company_name){
                    obj->count += request->shares_count;
                    return;
                }
            }
            Stock* new_stock = new Stock(request->shares_count, request->company_name, stock->base);
            free_stokcs.emplace(new_stock);
            return;
        }
    }   
}

void Stockholder::sell_finance(const int money, Request* request){
    free_credit += money;
    for(auto& stock : locked_Stock){
        if(stock->name == request->company_name){
            stock->count -= request->shares_count;
            if(stock->count == 0){
                earse_lock_shares(stock);
            }
            return;
        }
    }
}

void Stockholder::cancel_buy_finance(const int money){
    locked_credit -= money;
    free_credit += money;
}

void Stockholder::buy_finance(const int money, Request* request, Company* company){
    locked_credit -= money;
    for(auto& stock : free_stokcs){
        if(stock->name == request->company_name){
            stock->count += request->shares_count;
            return;
        }
    }
    Stock* new_stock = new Stock(request->shares_count, request->company_name, company);
    free_stokcs.emplace(new_stock); 
}

bool Stockholder::sell_validation(const Request* request){
    for(auto& obj : free_stokcs){
        if(obj->name == request->company_name && obj->count < request->shares_count){
            return false;    
        }else if(obj->name == request->company_name && obj->count >= request->shares_count){
            return true;
        }
    }
    return false;
}

void Stockholder::lock_money(const int money){
    locked_credit += money;
    free_credit -= money;
}

bool Stockholder::buy_validation(const Request* request){
    int buy_value = request->price * request->shares_count;
    if(buy_value > free_credit){
        return false;
    }
    return true;
}

int Stockholder::cal_free_assert(){
    int assert = free_credit;
    for(auto& obj : free_stokcs){
        assert += obj->base->get_price() * obj->count;
    }
    return assert;
}

Stockholder::Stockholder(const string& name, int free_credit, set<Stock*, Compare>&stocks)
: name(name), free_credit(free_credit), free_stokcs(stocks){
}

void Stockholder::print_free_shares(){
    cout << "Free shares:" << endl;
    if(free_stokcs.empty()){
        cout << "(empty)" << endl;
        return;
    }
    int stock_number = 1;
    for(auto& obj : free_stokcs){
        cout << stock_number << ". " 
            << obj->name << ": " << obj->count << endl;
        stock_number++;
    }
}

void Stockholder::print_lock_shares(){
    cout << "Locked shares: " << endl;
    if(locked_Stock.empty()){
        cout << "(empty)" << endl;
        return;
    }
    int stock_number = 1;
    for(auto& obj : locked_Stock){
        cout << stock_number << ". " 
            << obj->name << ": " << obj->count << endl;
        stock_number++;
    }
}

void Stockholder::print_portfilo(){    
    cout << name << " Portfolio" << endl 
        << "Total free assets: $" << cal_free_assert() << endl
        <<  "Free credit: $" << free_credit << endl
        <<  "Locked credit: $" << locked_credit << endl;
    print_free_shares();
    print_lock_shares();
}