#include <iostream>

#include "cli/cli.hpp"
#include "service/database.hpp"
#include "service/utghalam.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Missing path to CSV file. Usage: ./utghalam <pathToCsv>" << endl;
        return 1;
    }

    Database* db = new Database(argv[1]);
    UtGhalam* app = new UtGhalam(db);
    CliHandler cliHandler = CliHandler(app);
    cliHandler.start();

    return 0;
}