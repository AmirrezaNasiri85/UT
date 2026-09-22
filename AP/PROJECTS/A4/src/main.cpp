#include "main.hpp"


bool cancel_validation(Request* request, const int id){
    if(request == nullptr){
        cout << "Order " << id << " not found." << endl;
        return false;
    }
    return true;
}

void cancel_request(System& system, const int id){
    Request* request = system.find_request(id);
    if(!cancel_validation(request, id)){return;}
    Company* company = system.find_company(request->company_name);
    Stockholder* target = system.find_stockholder(request->username);
    if(target != nullptr){
        int value = request->price * request->shares_count;
        if(request->is_selling){
            target->cancel_sell_finance(value, request);
        }else{
            target->cancel_buy_finance(value);
        }
        company->remove_request(request);
        system.remove_request(request);
        cout << "Canceled order " << id << "." << endl;
        return;
    }
}

bool sell_validation(Stockholder* seller, Company* company, Request* request){
    if(!seller->sell_validation(request)){
        cout << "Insufficient free shares." << endl;
        return false;
    }else if(!company->request_buys_existance(request)){
        cout << request->username << " already has a buy order queued for " 
            << request->company_name << "." << endl;
        return false;
    }
    return true;
}

void sell_order(System& system, Request* request){
    
    Stockholder* seller = system.find_stockholder(request->username);
    Company* company = system.find_company(request->company_name);
    if(!sell_validation(seller, company, request)){return;}
    system.allocate_request_id(request);
    seller->lock_shares(request, company);

    Request* matched_request = company->sell_match(request);
    if(matched_request != nullptr){
        Stockholder* buyer = system.find_stockholder(matched_request->username);

        system.transfer(buyer, seller, matched_request, company);

        cout << "Order " << request->request_id << " matched with order "
             << matched_request->request_id << "." << endl; 
        return;
    }
    system.add_request(request);
}

bool buy_validation(Stockholder* buyer, Company* company, Request* request){
    if(!buyer->buy_validation(request)){
        cout << "Insufficient free credit." << endl;
        return false;
    }else if(!company->buy_validation(request->username)){
        cout << request->username << " already has a sell order queued for " 
            << request->company_name <<  "." << endl;
        return false;
    }
    return true;
}

void buy_order(System& system, Request* request){
    Stockholder* buyer = system.find_stockholder(request->username);
    Company* company = system.find_company(request->company_name);
    if(!buy_validation(buyer, company, request)){return;}
    system.allocate_request_id(request);
    buyer->lock_money(request->price * request->shares_count);

    Request* matched_request = company->buy_match(request);
    if(matched_request != nullptr){
        Stockholder* seller = system.find_stockholder(matched_request->username);
        system.transfer(buyer, seller, matched_request, company);

        cout << "Order " << request->request_id << " matched with order " 
            << matched_request->request_id << "." << endl;
        return;
    }
    system.add_request(request);
}

void report_company(System& system,const string& company_name){
    Company* target = system.find_company(company_name);
    if(target == nullptr){
        cout << company_name << " not found." << endl;
        return;
    }
    target->print_company_info();
}

void report_portfolio(System& system, Input& input){
    Stockholder* target = system.find_stockholder(input.user_name);
    if(target == nullptr){
        cout << input.user_name << " not found." << endl;
        return;
    }
    target->print_portfilo();
}

bool register_validation(System& system, const string& username){
    if(system.username_existance(username)){
        cout << username << " already exists." << endl;
        return false;
    }return true;
}   

void register_merge(Input& input, System& system){
    if(!register_validation(system, input.user_name)){return;}
    set<Stock*, Compare>empty_stock;
    Stockholder* new_stockholder = new Stockholder(input.user_name, input.free_credit, empty_stock);
    system.add_stockholder(new_stockholder, input.user_name);
    
    cout << input.user_name << " registered successfully." << endl;
}

void process(System& system){
    Input input;
    string command;

    while (cin >> command){
        if(command == "register"){
            cin >> input.user_name >> input.free_credit;
            register_merge(input, system);
        }else if(command == "report_portfolio"){
            cin >> input.user_name;
            report_portfolio(system, input);
        }else if(command == "report_company"){
            cin >> input.user_name;
            report_company(system, input.user_name);
        }else if(command == "sell_order"){
            Request* request = new Request();
            request->is_selling = true;
            cin >> request->username >> request->shares_count >> request->company_name >> request->price;
            sell_order(system, request);
        }else if(command == "buy_order"){
            Request* request = new Request();
            request->is_selling = false;
            cin >> request->username >> request->shares_count >> request->company_name >> request->price;
            buy_order(system, request);
        }else if(command == "cancel_order"){
            cin >> input.id;
            cancel_request(system, input.id);
        }
    }
}

void process_stockers(System& system, const string& Stocker_file){
    ifstream file(Stocker_file);

    string line;
    getline(file, line);
    while(getline(file, line)){

        stringstream csv_string(line);
        string csv_cell;

        getline(csv_string, csv_cell, ',');
        string user_name = csv_cell;

        getline(csv_string, csv_cell, ',');
        int free_credit = stoi(csv_cell);

        set<Stock*, Compare>temp_stock;
        while(getline(csv_string, csv_cell, ';')){
            stringstream stock_csv(csv_cell);
            string stock_part;

            getline(stock_csv, stock_part, ':');
            string name = stock_part;

            getline(stock_csv, stock_part, ':');
            int count = stoi(stock_part);

            Company* base = system.find_company(name);
            Stock* temp = new Stock(count, name, base);

            temp_stock.emplace(temp);
        }
        Stockholder* temp = new Stockholder(user_name, free_credit, temp_stock);
        system.add_stockholder(temp, user_name);
    }
    file.close();
}

void process_company(System& system, const string& Company_file){
    ifstream file(Company_file);

    string line;
    getline(file, line);
    while(getline(file, line)){
        stringstream csv_string(line);
        string csv_cell;

        getline(csv_string, csv_cell, ',');
        string name = csv_cell;

        getline(csv_string, csv_cell, ',');
        int price = stoi(csv_cell);
        
        Company* temp = new Company(name, price);
        system.add_Company(temp, name);
    }
    file.close();
}

int main(int args, char* argv[]){
    if(args != 3){
        abort();
    }

    System system;

    string Company_file = argv[1];
    string Stocker_file = argv[2];

    process_company(system, Company_file);
    process_stockers(system, Stocker_file);

    process(system);

    system.total_free();
}
