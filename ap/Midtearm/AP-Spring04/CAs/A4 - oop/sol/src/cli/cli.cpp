#include "cli.hpp"

#include <string>

#include "../utils.hpp"
#include "consts.hpp"
#include "executers.hpp"

using namespace std;

CliHandler::CliHandler(UtGhalam* utGhalamService) {
    utGhalamService_ = utGhalamService;
}

void CliHandler::handleReportCommands(vector<string> arguments) {
    if (arguments.size() == 0) {
        cout << errormessages::INVALID_COMMAND_ERR_MSG << endl;
        return;
    }

    string starter = arguments[0];
    arguments.erase(arguments.begin());
    if (starter == commands::REPORT_ALL_STARTER)
        reportAllExecuter(arguments, utGhalamService_);
    else if (starter == commands::REPORT_TEST_STARTER)
        reportTestExecuter(arguments, utGhalamService_);
    else if (starter == commands::REPORT_TESTS_STARTER)
        reportTestsExecuter(arguments, utGhalamService_);
    else if (starter == commands::REPORT_SUBJECT_STARTER)
        reportSubjectExecuter(arguments, utGhalamService_);
    else
        cout << errormessages::INVALID_COMMAND_ERR_MSG << endl;
}

void CliHandler::handleCommands(string commandStarter, vector<string> arguments) {
    if (commandStarter == commands::REPORT_STARTER)
        handleReportCommands(arguments);
    else if (commandStarter == commands::CREATE_TEMPLATE_STARTER)
        createTemplateExecuter(arguments, utGhalamService_);
    else if (commandStarter == commands::GENERATE_TEST_STARTER)
        generateTestExecuter(arguments, utGhalamService_);
    else if (commandStarter == commands::ATTEND_TEST_STARTER)
        attendTestExecuter(arguments, utGhalamService_);
    else if (commandStarter == commands::AUTOGENERATE_TEST_STARTER)
        autoGenerateTestExecuter(arguments, utGhalamService_);
    else
        cout << errormessages::INVALID_COMMAND_ERR_MSG << endl;
}

void CliHandler::start() {
    string line;
    while (getline(cin, line)) {
        vector<string> splitted = quotationWiseSplit(line);
        if (splitted.empty())
            continue;

        string commandStarter = splitted[0];
        vector<string> arguments(splitted.begin() + 1, splitted.end());
        handleCommands(commandStarter, arguments);
    }
}