#ifndef TEST_HEADERFILE
#define TEST_HEADERFILE

#include <string>
#include <vector>

#include "question.hpp"
#include "template.hpp"

class Test {
public:
    Test(std::string name, std::vector<Question*> questions, TestTemplate* startingTemplate);
    inline std::string getName() { return name_; }
    inline std::vector<Question*> getQuestions() { return questions_; };

private:
    std::string name_;
    TestTemplate* startingTemplate_;
    std::vector<Question*> questions_;
};

#endif // TEST_HEADERFILE