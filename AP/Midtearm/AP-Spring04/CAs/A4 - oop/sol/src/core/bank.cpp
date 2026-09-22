#include "bank.hpp"

#include "../utils.hpp"
#include "consts.hpp"
#include "question.hpp"

using namespace std;

QuestionBank::QuestionBank(string csvPath) {
    vector<map<string, string>> rows = readCSV(csvPath);
    for (map<string, string> row : rows) {
        string subject = row["subject"];
        vector<string> options{row["option1"], row["option2"], row["option3"], row["option4"]};
        Question* question = new Question(row["question_text"], options, stoi(row["correct_answer"]),
                                          bank::DIFFICULTY_MAPPING.at(row["difficulty"]), subject);
        questionsPerSubject_[subject].push_back(question);
    }
}

vector<Question*> QuestionBank::getMatchingQuestions(string subject, Question::Difficulty difficulty) {
    vector<Question*> matchingQuestions;
    if (!MAP_CONTAINS(questionsPerSubject_, subject)) {
        return matchingQuestions;
    }

    for (Question* question : questionsPerSubject_[subject]) {
        if (question->getDifficulty() == difficulty) {
            matchingQuestions.push_back(question);
        }
    }

    return matchingQuestions;
}

vector<string> QuestionBank::getSubjects() {
    vector<string> subjects;
    for (auto [subject, _] : questionsPerSubject_) {
        subjects.push_back(subject);
    }
    return subjects;
}