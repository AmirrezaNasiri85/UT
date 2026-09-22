#include "IOhandeling.hpp"



vector<string> seperate_orders(const string& orders){
    vector<string>seperated_orders;
    string order = "";
    for(size_t index = 0;index < orders.length();index++){
        if(orders[index] != ' '){
            order += orders[index];
        }else if((orders[index] == ' ') && !order.empty()){
            seperated_orders.push_back(order);
            order.clear();
        }
    }if(!order.empty()){
        seperated_orders.push_back(order);
    }return seperated_orders;
}

string find_line(vector<string>orders){
    bool command_line = false;
    for(string& word : orders){
        if(word == "POST" || word == "GET" || word == "DELETE" || word == "PUT"){
            command_line = true;
            return word;
        }
    }if(!command_line){
        throw invalid_argument("Bad Request");
    }return "";
}

void process_orders(System& managment){
    string commands;
    while(getline(cin, commands)){
        commands.erase(remove(commands.begin(), commands.end(), '\r'),commands.end());
        vector<string>orders = seperate_orders(commands);
        try{
            string method_line = find_line(orders);
            if(method_line == "POST"){
                managment.post_functions(orders);
            }else if(method_line == "GET"){
                managment.get_functions(orders);
            }else if(method_line == "DELETE"){
                managment.delet_functions(orders);
            }else if(method_line == "PUT"){
                managment.put_functions(orders);
            }
        }catch(const exception& error){
            cout << error.what() << endl;
        }
    }
}

