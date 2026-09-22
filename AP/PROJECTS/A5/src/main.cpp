#include "main.hpp"

void read_players_file(const string& player_file_name, System& managment){
    fstream file(player_file_name);
    if(!file.is_open()){
        cerr << "The Players file has not opened." << endl;
        abort();
    }
    string line;
    getline(file, line);
    // cout << "---------------------------" << endl;
    // cout << "PLAYERS LIST:" << endl;
    while(getline(file, line)){
        line.erase(remove(line.begin(), line.end(), '\r'),line.end());
        stringstream csv_stringstream(line);
        string csv_cell;

        getline(csv_stringstream, csv_cell, ',');
        string username = csv_cell;

        getline(csv_stringstream, csv_cell, ',');
        string passwrod = csv_cell;

        getline(csv_stringstream, csv_cell, ',');
        int XP = stoi(csv_cell);

        getline(csv_stringstream, csv_cell, ',');
        int RP = stoi(csv_cell);

        // cout << username << " | " << RP << endl;

        Player* new_player = new Player(username, passwrod, XP, RP);
        managment.add_new_player(username, new_player);
    }
    // cout << "---------------------------" << endl;
    file.close();
}

void read_admin_file(const string& admins_file_name, System& managment){
    fstream file(admins_file_name);
    if(!file.is_open()){
        cerr << "The admins file has not opened." << endl;
        abort();
    }   
    string line;
    getline(file, line);
    // cout << "---------------------------" << endl;
    // cout << "ADMINS LIST:" << endl;
    while(getline(file, line)){
        line.erase(remove(line.begin(), line.end(), '\r'),line.end());
        stringstream csv_stringstream(line);
        string csv_cell;

        getline(csv_stringstream, csv_cell, ',');
        string username = csv_cell;

        getline(csv_stringstream, csv_cell, ',');
        string password = csv_cell;

        // cout << username << " | " << password << endl;

        Admin* new_admin = new Admin(username, password);
        managment.add_new_admin(username, new_admin);
    }//cout << "---------------------------" << endl;
    file.close();
}

int main(int args, char* argv[]){
    if(args != 3){
        abort();
    }

    Data_base* data_base = new Data_base;
    System managment(data_base);
    
    string players_file_name = argv[1];
    string admin_file_name = argv[2];
    
    read_players_file(players_file_name, managment);
    read_admin_file(admin_file_name, managment);

    process_orders(managment);
}