#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Management/SystemManager.hpp"
#include "Objects/People.hpp"
#include "Management/IOhandeling.hpp"


using namespace std;

void read_players_file(const string& player_file_name, System& managment);

void read_admin_file(const string& admins_file_name, System& managment);

int main(int args, char* argv[]);