#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <set>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>

struct Shipment;
class Truck;

using namespace std;
using Scored_shipment = vector<pair<int, Shipment*>>;
using Scored_city = vector<pair<int, string>>;


const string CAPITAL = "Tehran";
const string DELIVERATION = "delivered";
const string TRANSITION = "transit";
const string START_PLACE = "warehouse";

struct City
{
    string name;
    int distance;
    list<Shipment *> delivered_list;
    void add_shipment(Shipment *shipment);
};

void City::add_shipment(Shipment *shipment)
{
    this->delivered_list.push_back(shipment);
}


struct Shipment
{
    int distance;
    int weight;
    int id;
    string transition = START_PLACE;
    string origin;
    string destination;

    Shipment(const string &origin, const string &destination, int weight, int id);
    void change_transition(const string &new_transition);
    void change_distance(const int distance);
    float cal_cost();
    int cal_score(const int id);
    void print_transition();
};

void Shipment::print_transition(){
    if (this->transition == START_PLACE){
        cout << "Order " << this->id << " is currently in warehouse in " << this->origin
                  << endl;
    }
    else if (this->transition == TRANSITION){
        cout << "Order " << this->id << " is in transit to " << this->destination
                  << endl;
    }
    else if (this->transition == DELIVERATION){
        cout << "Order " << this->id << " is delivered to " << this->destination
                  << endl;
    }
}

int Shipment::cal_score(const int id){
    int score = this->weight + (id - this->id) * 5;
    return score;
}

float Shipment::cal_cost()
{
    double cost = this->distance * this->weight;
    return cost;
}

void Shipment::change_distance(const int distance)
{
    this->distance = distance;
}

void Shipment::change_transition(const string &new_transition)
{
    this->transition = new_transition;
}

Shipment::Shipment(const string &origin, const string &destination, int weight, int id)
{
    this->destination = destination;
    this->origin = origin;
    this->id = id;
    this->weight = weight;
}

struct Shipment_list
{
    int id = 0;
    list<Shipment *> shipment_list;
};

class Truck
{
private:
    int loaded_weight = 0;
    int id;
    int capacity;
    bool transit = false;
    string origin = CAPITAL;
    string destination;
    vector<int> load_shipment;

public:
    void put_down_load();
    bool try_load(const int weight, int id);
    bool get_transit();
    Truck(const int id, const int capacity);
    int get_id();
    string get_origin();
    int get_capacity();
    void change_origin(const string &new_place);
    string get_destination();
    void change_transit();
    void change_destination(const string &new_destination);
    void sort_load_shipment();
    void print_shipment();
    bool is_empty();
    void change_load_transition(list<Shipment *> &shipment_list, City *city
    , vector<Shipment> &total_deliveration);
};

void Truck::change_load_transition(list<Shipment *> &shipment_list, City *city
    , vector<Shipment> &total_deliveration){
    for (auto &id : this->load_shipment)
    {
        for (auto &shipment : shipment_list)
        {
            if (id == shipment->id){
                shipment->change_transition(DELIVERATION);
                total_deliveration.push_back(*shipment);
                city->add_shipment(shipment);
                break;
            }
        }
    }
    this->load_shipment.clear();
}

bool Truck::is_empty(){
    if(this->load_shipment.empty()){
        return false;
    }
    return true;
}

void Truck::print_shipment(){
    for(const int& id : this->load_shipment)
        cout << id << " ";
}

void Truck::sort_load_shipment(){
    sort(this->load_shipment.begin(), this->load_shipment.end());
}

void Truck::put_down_load()
{
    this->load_shipment.clear();
    this->loaded_weight = 0;
}

bool Truck::try_load(const int weight, const int id)
{
    if (loaded_weight + weight <= capacity)
    {
        this->loaded_weight += weight;
        this->load_shipment.push_back(id);
        return true;
    }
    return false;
}

bool Truck::get_transit()
{
    return this->transit;
}

void Truck::change_destination(const string &new_destination)
{
    this->destination = new_destination;
}

void Truck::change_transit()
{
    this->transit = !this->transit;
}

string Truck::get_destination()
{
    return this->destination;
}

void Truck::change_origin(const string &new_place)
{
    this->origin = new_place;
    this->loaded_weight = 0;
}

int Truck::get_capacity()
{
    return this->capacity;
}

string Truck::get_origin()
{
    return this->origin;
}

int Truck::get_id()
{
    return this->id;
}

Truck::Truck(const int id, const int capacity)
{
    this->id = id;
    this->capacity = capacity;
}

struct Logistic_data
{
    list<Truck *> truck_list;
    list<City *> city_list;
    set<string> city_names = {CAPITAL};
    vector<Shipment> total_deliveration;
};


void process_truck(const string &file_name, Logistic_data &data)
{
    fstream file(file_name);

    if (!file.is_open()) abort();

    string read_line;

    getline(file, read_line);

    while (getline(file, read_line))
    {
        stringstream csv_string(read_line);
        string csv_cell;

        getline(csv_string, csv_cell, ',');
        int id = stoi(csv_cell);

        getline(csv_string, csv_cell, ',');
        int capacity = stoi(csv_cell);

        Truck *temp = new Truck(id, capacity);
        data.truck_list.push_back(temp);
    }
}

void process_city(const string &file_name, Logistic_data &data)
{
    fstream file(file_name);

    if (!file.is_open()) abort();

    string read_line;
    getline(file, read_line);

    while (getline(file, read_line))
    {
        stringstream csv_string(read_line);
        string csv_cell;

        City *temp = new City;

        getline(csv_string, csv_cell, ',');
        temp->name = csv_cell;

        getline(csv_string, csv_cell, ',');
        temp->distance = stoi(csv_cell);

        data.city_list.push_back(temp);
        data.city_names.insert(temp->name);
    }
}

bool add_validation(const string &origin, const string &destination)
{
    if ((origin != CAPITAL && destination != CAPITAL) 
    || origin == destination){
        return false;
    }
    return true;
}

void find_shipment_distance(list<City *> &city_list, const string &destination
    , const string &origin, Shipment *shipment)
{
    if (origin == CAPITAL){
        for (auto &city : city_list){
            if (city->name == destination){
                shipment->change_distance(city->distance);
                break;
            }
        }
    }else if (origin != CAPITAL){
        for (auto &city : city_list){
            if (city->name == origin){
                shipment->change_distance(city->distance);
                break;
            }
        }
    }
}

void add_main(const string &origin, const string &destination
    , int weight, Shipment_list *ship_list, list<City *> &city_list)
{
    ship_list->id += 1;

    int id = ship_list->id;
    Shipment *new_shipment = new Shipment(origin, destination, weight, id);

    find_shipment_distance(city_list, destination, origin, new_shipment);

    ship_list->shipment_list.push_front(new_shipment);

    cout << "Order " << id << " added\n";
}

void add_merge(set<string> &city_names, Shipment_list *ship_list, list<City *> &city_list)
{
    string origin, destination;
    int weight;
    cin >> origin >> destination >> weight;

    if (!add_validation(origin, destination)){
        cout << "Order not found\n";
        return;
    }

    add_main(origin, destination, weight, ship_list, city_list);
}

Shipment *find_shipment(list<Shipment *> &shipment_list, int id)
{
    for (auto &obj : shipment_list){
        if (obj->id == id){
            return obj;
        }
    }
    return nullptr;
}

void track_merge(list<Shipment *> &shipment_list)
{
    int id;
    cin >> id;

    Shipment *shipment = find_shipment(shipment_list, id);

    if (shipment == nullptr)
    {
        cout << "Order not found\n";
        return;
    }
    shipment->print_transition();
}

Truck *find_load_truck(int id,list<Truck *> &truck_list)
{
    for (auto &truck : truck_list)
    {
        if (truck->get_id() == id)
        {
            return truck;
        }
    }
    return nullptr;
}

list<Shipment *> find_shipment(const string &origin, const string destination, list<Shipment *> &shipment_list)
{
    list<Shipment *> possible_shipment;

    for (auto &shipment : shipment_list)
    {
        if (shipment->origin == origin
        && shipment->destination == destination 
        && shipment->transition == START_PLACE)
        {
            possible_shipment.push_back(shipment);
        }
    }
    return possible_shipment;
}

bool sort_scored_pair(const pair<int, Shipment *>& a, const pair<int, Shipment *> &b)
{
    if (a.first > b.first){
        return true;
    }else if (a.first == b.first){
        if (a.second->id< b.second->id){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

Scored_shipment set_score_shipment(int last_id, list<Shipment *>& possible_shipment)
{
    int size = possible_shipment.size();

    Scored_shipment score_shipment;
    score_shipment.reserve(size);

    pair<int, Shipment *> temp;
    for (auto &shipment : possible_shipment){
        int score = shipment->cal_score(last_id);
        temp.first = score;
        temp.second = shipment;
        score_shipment.emplace_back(temp);
    }
    return score_shipment;
}

void load_main(Scored_shipment& score_shipment, Truck *current_truck)
{
    sort(score_shipment.begin(), score_shipment.end(), sort_scored_pair);

    for (auto &pair : score_shipment)
    {
        if (current_truck->try_load(pair.second->weight, pair.second->id))
        {
            pair.second->change_transition(TRANSITION);
        }
    }
}

bool print_load(Truck *truck)
{
    if(!truck->is_empty()){
        cout << "No order could be loaded\n";
        return false;
    }
    truck->sort_load_shipment();
    cout << "Truck " << truck->get_id() << " loaded with orders: ";
    truck->print_shipment();
    cout << endl;
    return true;
}

bool check_possible_shipment(list<Shipment *>& possible_shipment, Truck* truck){
     if (possible_shipment.empty())
    {
        cout << "No order could be loaded\n";
        return false;
    }   
    return true;
}

bool load_check_truck(Truck *current_truck, const string& destination)
{
    if (current_truck->get_origin() == destination || current_truck->get_transit())
    {
        cout << "No order could be loaded\n";
        return false;
    }
    return true;
}

void load_merge(list<Truck *> &truck_list, Shipment_list *shipment_list)
{
    string destination;
    int id;
    cin >> id >> destination;

    Truck *current_truck = find_load_truck(id, truck_list);
    if(!load_check_truck(current_truck, destination)){return;}

    list<Shipment *> possible_shipment = find_shipment(current_truck->get_origin()
        , destination, shipment_list->shipment_list);
    if(!check_possible_shipment(possible_shipment, current_truck)){return;}

    Scored_shipment score_shipment = set_score_shipment(shipment_list->id, possible_shipment);

    load_main(score_shipment, current_truck);

    if(print_load(current_truck)){
        current_truck->change_transit();
        current_truck->change_destination(destination);
    }
}

void print_deliver(Truck *truck)
{
    truck->is_empty();
    cout << "Truck " << truck->get_id() << " delivered orders: ";
    truck->print_shipment();
    cout << endl;
}

void change_truck_place(Truck *truck)
{
    truck->change_origin(truck->get_destination());
    truck->change_destination("");
}

City *find_city(list<City *> &city_list, const string &destination)
{
    for (auto &city : city_list)
    {
        if (city->name == destination)
        {
            return city;
        }
    }
    return nullptr;
}

Truck *find_deliver_truck(int id, list<Truck *> &truck_list)
{
    for (auto &truck : truck_list)
    {
        if (truck->get_id() == id)
        {
            return truck;
        }
    }
    return nullptr;
}

bool deliver_city_existance(City *city)
{
    if (city == nullptr)
    {
        cout << "No order could be loaded\n";
        return false;
    }
    return true;
}

bool deliver_truck_check(Truck *truck)
{
    if(!truck->is_empty()){
        cout << "No orders to deliver in truck " << truck->get_id() << endl;
        return false;
    }
    return true;
}

void deliver_functions(Logistic_data *data, list<Shipment *> &shipment_list)
{
    int id;
    cin >> id;

    Truck *truck = find_deliver_truck(id, data->truck_list);
    if(!deliver_truck_check(truck)){return;}

    City *city = find_city(data->city_list, truck->get_destination());
    if(!deliver_city_existance(city)){return;}

    print_deliver(truck);

    change_truck_place(truck);

    truck->change_load_transition(shipment_list, city, data->total_deliveration);

    truck->change_transit();

    truck->put_down_load();
}

bool sort_total_shipment( Shipment &first, Shipment &second)
{
    if (first.id < second.id){return true;}
    return false;
}

float cal_total_cost(vector<Shipment> &total_deliveration)
{
    double total_cost = 0;
    for (auto &obj : total_deliveration)
    {
        total_cost += obj.cal_cost();
    }
    return total_cost;
}

void financial_report(vector<Shipment> &total_deliveration)
{
    sort(total_deliveration.begin(), total_deliveration.end(), sort_total_shipment);

    cout << "Total income: " << cal_total_cost(total_deliveration) << endl;
    cout << "Delivered orders:" << endl;

    for (auto &shipment : total_deliveration)
    {
        cout << shipment.id << " " << shipment.cal_cost() << endl;
    }
}

Scored_city set_score_city(list<Shipment *> &shipment_list, list<City *> &city_list, Shipment_list *ship_list)
{
    Scored_city score_city;

    for (auto &city : city_list)
    {
        int score = 0;
        if (city->name != CAPITAL)
        {
            for (auto &shipment : shipment_list)
            {
                if (shipment->transition == START_PLACE 
                && (shipment->origin == city->name
                || shipment->destination == city->name))
                {
                    score += shipment->cal_score(ship_list->id);
                }
            }
            score /= city->distance;
            score_city.push_back({score, city->name});
        }
    }
    return score_city;
}

void make_lower(char& a)
{
    if (a <= 90) a += 32;
}

bool sort_scored_city(pair<int,string> &a, pair<int,string> &b)
{
    if (a.first > b.first){return true;}
    else if (a.first == b.first){return a.second < b.second;}
    return false;
}

string find_best_city(Scored_city &scored_city)
{
    sort(scored_city.begin(), scored_city.end(), sort_scored_city);
    return scored_city[0].second;
}

int find_best_truck(list<Truck *> &truck_list, const string &destination, list<Shipment *> &shipment_list)
{
    int best_truck_id = 0;
    int min_dif = INT_MAX;

    for (auto &truck : truck_list){
        int total_weight = 0;

        if (truck->get_origin() == CAPITAL && !truck->get_transit()){
            for (auto &shipment : shipment_list){
                if (shipment->origin == CAPITAL 
                    && shipment->destination == destination
                    && shipment->transition == START_PLACE){
                    total_weight += shipment->weight;
                }
            }
            int dif = truck->get_capacity() - total_weight;
            if (dif >= 0 && dif < min_dif){
                best_truck_id = truck->get_id();
                min_dif = dif;
            }else if (dif >= 0 && dif == min_dif){
                if (best_truck_id == 0 || best_truck_id < truck->get_id()){
                    best_truck_id = truck->get_id();
                }
            }
        }
    }
    return best_truck_id;
}

void print_recommend(const string &best_city, int truck_id)
{
    cout << "Recommended city: " << best_city
              << endl
              << "Recommended truck: " << truck_id
              << endl;
}

void recommend_functions(list<City *> &city_list, Shipment_list *ship_list,list<Truck *> &truck_list)
{

    Scored_city scored_city = set_score_city(ship_list->shipment_list, city_list, ship_list);

    string best_city = find_best_city(scored_city);

    int best_truck_id = find_best_truck(truck_list, best_city, ship_list->shipment_list);

    print_recommend(best_city, best_truck_id);
}

void free_truck(list<Truck *> &truck_list)
{
    for (auto &truck : truck_list)
    {
        delete (truck);
    }
}

void free_city(list<City *>& city_list)
{
    for (auto &city : city_list)
    {
        delete (city);
    }
}

void free_logistic(Logistic_data &data)
{
    free_truck(data.truck_list);
    free_city(data.city_list);
}

void free_shipment(list<Shipment *> &shipment_list)
{
    for (auto &shipment : shipment_list)
    {
        delete (shipment);
    }
}

void get_orders(Logistic_data *data)
{
    Shipment_list ship_list;

    string command;

    while (cin >> command){
        if (command == "add_order"){
            add_merge(data->city_names, &ship_list, data->city_list);
        }else if (command == "track"){
            track_merge(ship_list.shipment_list);
        }else if (command == "load"){
            load_merge(data->truck_list, &ship_list);
        }else if (command == "deliver"){
            deliver_functions(data, ship_list.shipment_list);
        }else if (command == "financial_report"){
            financial_report(data->total_deliveration);
        }else if (command == "recommend"){
            recommend_functions(data->city_list, &ship_list, data->truck_list);
        }
    }
    free_shipment(ship_list.shipment_list);
}

int main(int args, char *argv[])
{
    if (args != 3)
    {
        cout << "Not enough files\n";
        return 1;
    }

    Logistic_data data;
    string truck_file = argv[1];
    string city_file = argv[2];

    process_truck(truck_file, data);
    process_city(city_file, data);

    get_orders(&data);

    free_logistic(data);

    return 0;
}
