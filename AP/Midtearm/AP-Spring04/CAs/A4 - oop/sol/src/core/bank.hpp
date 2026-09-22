#ifndef BANK_HEADERFILE
#define BANK_HEADERFILE

#include <map>
#include <string>

#include "question.hpp"

class QuestionBank {
public:
    QuestionBank(std::string csvPath);
    std::vector<Question*> getMatchingQuestions(std::string subject, Question::Difficulty difficulty);
    std::vector<std::string> getSubjects();

private:
    std::map<std::string, std::vector<Question*>> questionsPerSubject_;
};

#endif // BANK_HEADERFILE