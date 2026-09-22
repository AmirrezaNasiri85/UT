#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const string EMPTY = "";
const char DATA_SEPARATOR = ',';
const char COMMAND_SEPARATOR = ' ';
const int START = 0;
const int NEXT = 1;

const int TABLES_FILE = 1;
const int STUDENTS_FILE = 2;
const int BEFORE_LAST = -1;
const string NAME_SEPARATOR = ", ";

namespace studentinfo {
const int ID = 0;
const int NAME = 1;
const int FRIEND_ID = 2;
const int ENEMY_ID = 3;
}; // namespace studentinfo

namespace tableinfo {
const int ID = 0;
const int X = 1;
const int Y = 2;
const int CAPACITY = 3;
const int TYPE = 4;
}; // namespace tableinfo

namespace tabletype {
const string WINDOW = "window";
const string DOOR = "door";
const string MIDDLE = "middle";
}; // namespace tabletype

namespace commands {
const string SHOW_TABLE_INFO = "show_table_info";
const string ENTER = "enter";
const string RESERVE_TABLE = "reserve_table";
const string EXIT = "exit";
const string SWITCH = "switch";
const int COMMAND = 0;
const int FIRST_ARG = 1;
}; // namespace commands

const int WINDOW_BONUS = 6;
const int DOOR_BONUS = 4;
const int MIDDLE_BONUS = 2;

struct Student {
    int id;
    string name;
    int friend_id;
    int enemy_id;
};

struct Table {
    int id;
    int x;
    int y;
    int capacity;
    string type;
    vector<int> students_id_at_the_table;
    vector<int> students_id_in_queue;
};

vector<string> separateItems(string str, char ch) {
    vector<string> separated;
    string str_part_separated = EMPTY;
    for (int i = START; i < str.size(); i += NEXT) {
        if (i == str.size() - 1 || str[i] == ch) {
            if (i == str.size() - 1)
                str_part_separated += str[i];
            separated.push_back(str_part_separated);
            str_part_separated = EMPTY;
        }
        else {
            str_part_separated += str[i];
        }
    }
    return separated;
}

void readAddStudents(string file_path, vector<Student>& students) {
    ifstream info_file(file_path);
    string reading_info;
    getline(info_file, reading_info);
    while (getline(info_file, reading_info)) {
        vector<string> info_extracted = separateItems(reading_info, DATA_SEPARATOR);
        Student new_student;
        new_student.id = stoi(info_extracted[studentinfo::ID]);
        new_student.name = info_extracted[studentinfo::NAME];
        new_student.friend_id = stoi(info_extracted[studentinfo::FRIEND_ID]);
        new_student.enemy_id = stoi(info_extracted[studentinfo::ENEMY_ID]);
        students.push_back(new_student);
    }
}

void readAddTables(string file_path, vector<Table>& tables) {
    ifstream info_file(file_path);
    string reading_info;
    getline(info_file, reading_info);
    while (getline(info_file, reading_info)) {
        vector<string> info_extracted = separateItems(reading_info, DATA_SEPARATOR);
        Table new_table;
        new_table.id = stoi(info_extracted[tableinfo::ID]);
        new_table.x = stoi(info_extracted[tableinfo::X]);
        new_table.y = stoi(info_extracted[tableinfo::Y]);
        new_table.capacity = stoi(info_extracted[tableinfo::CAPACITY]);
        new_table.type = info_extracted[tableinfo::TYPE];
        tables.push_back(new_table);
    }
}

void readFiles(char* argv[], vector<Student>& students, vector<Table>& tables) {
    string tables_filepath = argv[TABLES_FILE];
    string students_filepath = argv[STUDENTS_FILE];
    readAddTables(tables_filepath, tables);
    readAddStudents(students_filepath, students);
}

Table findTableById(int table_id, vector<Table>& tables) {
    for (auto& table : tables) {
        if (table.id == table_id) return table;
    }
    Table dummy;
    return dummy;
}

string studentNameById(int student_id, vector<Student>& students) {
    for (auto& student : students) {
        if (student.id == student_id) {
            return student.name;
        }
    }
    return EMPTY;
}

bool compareStrings(const string& str1, const string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    int minLength = min(len1, len2);

    for (int i = 0; i < minLength; i++) {
        if (str1[i] < str2[i]) {
            return true;
        }
        else if (str1[i] > str2[i]) {
            return false;
        }
    }

    return len1 < len2;
}

void showTableInfo(vector<string> command_line_separated, vector<Student>& students, vector<Table>& tables) {
    int table_id = stoi(command_line_separated[commands::FIRST_ARG]);
    Table table = findTableById(table_id, tables);
    cout << "Table ID: " << table.id << endl;
    cout << "People at the table: ";
    vector<string> students_names;
    for (int i = START; i < table.students_id_at_the_table.size(); i += NEXT) {
        students_names.push_back(studentNameById(table.students_id_at_the_table[i], students));
    }
    sort(students_names.begin(), students_names.end(), compareStrings);
    for (int i = START; i < students_names.size(); i += NEXT) {
        cout << students_names[i];
        if (i != students_names.size() + BEFORE_LAST)
            cout << NAME_SEPARATOR;
    }
    cout << endl;
    int occupied_size = table.students_id_at_the_table.size();
    int queue_length = table.students_id_in_queue.size();
    cout << "Table remaining capacity: " << table.capacity - occupied_size << endl;
    cout << "Waiting queue length: " << queue_length << endl;
}

int calculateDistance(const Table& table1, const Table& table2) {
    return abs(table1.x - table2.x) + abs(table1.y - table2.y);
}

Table* findTableWithStudent(int student_id, vector<Table>& tables) {
    for (auto& table : tables) {
        if (find(table.students_id_at_the_table.begin(), table.students_id_at_the_table.end(), student_id) != table.students_id_at_the_table.end()) {
            return &table;
        }
    }
    return nullptr;
}

Student* findStudent(vector<Student>& students, int student_id) {
    for (auto& s : students) {
        if (s.id == student_id) {
            return &s;
        }
    }
    return nullptr;
}

int getTableTypeBonus(const string& type) {
    if (type == tabletype::WINDOW) return WINDOW_BONUS;
    if (type == tabletype::DOOR) return DOOR_BONUS;
    return MIDDLE_BONUS;
}

vector<pair<int, Table*>> scoreTables(vector<Table>& tables, Table* friend_table, Table* enemy_table) {
    vector<pair<int, Table*>> scored_tables;

    for (auto& table : tables) {
        int distance_to_friend = friend_table ? calculateDistance(table, *friend_table) : 0;
        int distance_to_enemy = enemy_table ? calculateDistance(table, *enemy_table) : 0;
        int type_bonus = getTableTypeBonus(table.type);
        int score = distance_to_enemy - distance_to_friend + type_bonus;

        scored_tables.push_back({score, &table});
    }
    return scored_tables;
}

void sortTables(vector<pair<int, Table*>>& scored_tables) {
    sort(scored_tables.begin(), scored_tables.end(), [](pair<int, Table*> a, pair<int, Table*> b) {
        return (a.first == b.first) ? a.second->id < b.second->id : a.first > b.first;
    });
}

void displayTableOptions(const vector<pair<int, Table*>>& scored_tables) {
    for (const auto& [score, table] : scored_tables) {
        int remaining_capacity = table->capacity - table->students_id_at_the_table.size();
        cout << "Table " << table->id << ": " << remaining_capacity << " " << table->students_id_in_queue.size() << endl;
    }
}

void studentEnter(vector<string> command_line_separated, vector<Student>& students, vector<Table>& tables) {
    int student_id = stoi(command_line_separated[commands::FIRST_ARG]);
    Student* student = findStudent(students, student_id);
    if (!student) return;

    Table* friend_table = findTableWithStudent(student->friend_id, tables);
    Table* enemy_table = findTableWithStudent(student->enemy_id, tables);

    vector<pair<int, Table*>> scored_tables = scoreTables(tables, friend_table, enemy_table);
    sortTables(scored_tables);
    displayTableOptions(scored_tables);
}

Table* findBestTable(Student* student, vector<Table>& tables) {
    Table* friend_table = findTableWithStudent(student->friend_id, tables);
    Table* enemy_table = findTableWithStudent(student->enemy_id, tables);
    vector<pair<int, Table*>> scored_tables = scoreTables(tables, friend_table, enemy_table);
    sortTables(scored_tables);
    if (!scored_tables.empty()) return scored_tables[0].second;
    return nullptr;
}

Table* findTableByUserChoice(vector<string> command_line_separated, vector<Table>& tables) {
    if (command_line_separated.size() > 2 && !command_line_separated[2].empty()) {
        int table_id = stoi(command_line_separated[2]);
        for (auto& table : tables) {
            if (table.id == table_id) return &table;
        }
    }
    return nullptr;
}

void seatOrQueueStudent(Table& table, Student& student) {
    int remaining_capacity = table.capacity - table.students_id_at_the_table.size();
    if (remaining_capacity > 0) {
        table.students_id_at_the_table.push_back(student.id);
        cout << student.name << " sits at table " << table.id << endl;
    }
    else {
        table.students_id_in_queue.push_back(student.id);
        cout << student.name << " enters the waiting queue of table " << table.id << endl;
    }
}

void reserveTable(vector<string> command_line_separated, vector<Student>& students, vector<Table>& tables) {
    int student_id = stoi(command_line_separated[commands::FIRST_ARG]);
    Student* student = findStudent(students, student_id);
    if (!student) return;
    Table* selected_table = findTableByUserChoice(command_line_separated, tables);
    if (!selected_table) selected_table = findBestTable(student, tables);
    if (selected_table) seatOrQueueStudent(*selected_table, *student);
}

void studentExit(vector<string> command_line_separated, vector<Student>& students, vector<Table>& tables) {
    int student_id = stoi(command_line_separated[commands::FIRST_ARG]);
    Student* student = findStudent(students, student_id);
    if (!student) return;

    Table* table = findTableWithStudent(student->id, tables);
    if (table) {
        auto& seated = table->students_id_at_the_table;
        seated.erase(remove(seated.begin(), seated.end(), student->id), seated.end());
        cout << student->name << " exits!" << endl;

        if (!table->students_id_in_queue.empty()) {
            int replacement_student_id;
            int friend_id = student->friend_id;
            auto it = find(table->students_id_in_queue.begin(), table->students_id_in_queue.end(), friend_id);
            if (it != table->students_id_in_queue.end()) {
                replacement_student_id = *it;
                table->students_id_in_queue.erase(it);
            }
            else {
                replacement_student_id = table->students_id_in_queue.front();
                table->students_id_in_queue.erase(table->students_id_in_queue.begin());
            }
            table->students_id_at_the_table.push_back(replacement_student_id);
        }
    }
}

void switchWithFriend(vector<string> command_line_separated, vector<Student>& students, vector<Table>& tables) {
    int student_id = stoi(command_line_separated[commands::FIRST_ARG]);
    Student* student = findStudent(students, student_id);
    if (!student) return;

    Table* student_table = findTableWithStudent(student->id, tables);
    Table* friend_table = findTableWithStudent(student->friend_id, tables);

    if (!student_table || !friend_table) {
        cout << "Cannot switch seats!" << endl;
    }

    auto& student_seats = student_table->students_id_at_the_table;
    auto& friend_seats = friend_table->students_id_at_the_table;

    student_seats.erase(remove(student_seats.begin(), student_seats.end(), student->id), student_seats.end());
    friend_seats.erase(remove(friend_seats.begin(), friend_seats.end(), student->friend_id), friend_seats.end());

    student_seats.push_back(student->friend_id);
    friend_seats.push_back(student->id);

    cout << studentNameById(student->id, students) << " switches seats with "
         << studentNameById(student->friend_id, students) << "!" << endl;
}

void commandHandler(vector<Student>& students, vector<Table>& tables) {
    string command_line;
    while (getline(cin, command_line)) {
        if (command_line == EMPTY) break;
        vector<string> command_line_separated = separateItems(command_line, COMMAND_SEPARATOR);
        string command = command_line_separated[commands::COMMAND];
        if (command == commands::SHOW_TABLE_INFO) {
            showTableInfo(command_line_separated, students, tables);
        }
        else if (command == commands::ENTER) {
            studentEnter(command_line_separated, students, tables);
        }
        else if (command == commands::RESERVE_TABLE) {
            reserveTable(command_line_separated, students, tables);
        }
        else if (command == commands::EXIT) {
            studentExit(command_line_separated, students, tables);
        }
        else if (command == commands::SWITCH) {
            switchWithFriend(command_line_separated, students, tables);
        }
    }
}

void siteManager(char* argv[]) {
    vector<Student> students;
    vector<Table> tables;
    readFiles(argv, students, tables);
    commandHandler(students, tables);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " </path/to/tables/file> </path/to/students/file>" << endl;
        return EXIT_FAILURE;
    }
    siteManager(argv);
    return 0;
}
