#ifndef TEMPLATE_HEADERFILE
#define TEMPLATE_HEADERFILE

#include <string>
#include <vector>

#include "question.hpp"

struct Config {
    std::string subject;
    Question::Difficulty difficulty;
    int questionsCount;
};

struct TestTemplate {
    std::string name;
    std::vector<Config> configs;
};

#endif // TEMPLATE_HEADERFILE