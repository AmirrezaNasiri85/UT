#include <cstdlib>

#include "../core/consts.hpp"
#include "../service/utghalam.hpp"
#include "../utils.hpp"
#include "consts.hpp"

using namespace std;

void createTemplateExecuter(vector<string> arguments, UtGhalam* service) {
    if (arguments.size() < 2) {
        cout << errormessages::WRONG_NUMBER_OF_ARGS_ERR_MSG << endl;
        return;
    }

    string templateName = arguments[0];
    vector<Config> configs;
    for (size_t i = 1; i < arguments.size(); i++) {
        vector<string> configSeparated = splitString(arguments[i], ':');

        string subjectName = configSeparated[0];
        Question::Difficulty difficulty = bank::DIFFICULTY_MAPPING.at(configSeparated[1]);
        int numOfQuestions = stoi(configSeparated[2]);
        configs.push_back({subjectName, difficulty, numOfQuestions});
    }

    string errMsg;
    service->createTemplate(templateName, configs, errMsg);
    if (!errMsg.empty()) {
        cout << errMsg << endl;
        return;
    }
    cout << "Template '" << templateName << "' was created successfully." << endl;
}

void generateTestExecuter(vector<string> arguments, UtGhalam* service) {
    if (arguments.size() != 2) {
        cout << errormessages::WRONG_NUMBER_OF_ARGS_ERR_MSG << endl;
        return;
    }

    string testName = arguments[0];
    string templateName = arguments[1];
    string errMsg;
    service->generateTest(testName, templateName, errMsg);
    if (!errMsg.empty()) {
        cout << errMsg << endl;
        return;
    }
    cout << "Test '" << testName << "' was generated successfully." << endl;
}

void attendTestExecuter(vector<string> arguments, UtGhalam* service) {
    if (arguments.size() != 1) {
        cout << errormessages::WRONG_NUMBER_OF_ARGS_ERR_MSG << endl;
        return;
    }

    string testName = arguments[0];
    string errMsg;
    service->attendTest(testName, errMsg);
    if (!errMsg.empty()) {
        cout << errMsg << endl;
        return;
    }
    cout << endl
         << "Finished " << testName << "." << endl;
}

void autoGenerateTestExecuter(vector<string> arguments, UtGhalam* service) {
    if (arguments.size() != 1) {
        cout << errormessages::WRONG_NUMBER_OF_ARGS_ERR_MSG << endl;
        return;
    }

    string testName = arguments[0];
    string errMsg;
    service->autoGenerateTest(testName, errMsg);
    if (!errMsg.empty()) {
        cout << errMsg << endl;
        return;
    }
    cout << "Test '" << testName << "' was generated successfully." << endl;
}

void reportAllExecuter(vector<string> arguments, UtGhalam* service) {
    if (arguments.size() > 0) {
        cout << errormessages::WRONG_NUMBER_OF_ARGS_ERR_MSG << endl;
        return;
    }

    service->reportAll();
}

void reportTestExecuter(vector<string> arguments, UtGhalam* service) {
    if (arguments.size() != 1) {
        cout << errormessages::WRONG_NUMBER_OF_ARGS_ERR_MSG << endl;
        return;
    }

    string errMsg;
    service->reportTest(arguments[0], errMsg);
    if (!errMsg.empty()) {
        cout << errMsg << endl;
    }
}

void reportTestsExecuter(vector<string> arguments, UtGhalam* service) {
    if (arguments.size() > 0) {
        cout << errormessages::WRONG_NUMBER_OF_ARGS_ERR_MSG << endl;
        return;
    }

    service->reportTests();
}
void reportSubjectExecuter(vector<string> arguments, UtGhalam* service) {
    if (arguments.size() != 1) {
        cout << errormessages::WRONG_NUMBER_OF_ARGS_ERR_MSG << endl;
        return;
    }

    service->reportSubject(arguments[0]);
}
