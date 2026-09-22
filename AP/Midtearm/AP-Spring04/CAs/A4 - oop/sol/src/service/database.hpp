#ifndef DATABASE_HEADERFILE
#define DATABASE_HEADERFILE

#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "../core/attendance.hpp"
#include "../core/bank.hpp"
#include "../core/question.hpp"
#include "../core/template.hpp"
#include "../core/test.hpp"
#include "../utils.hpp"

struct StatEntry {
    int incorrectCount;
    int correctCount;
    int blankCount;

    StatEntry() {
        incorrectCount = 0;
        correctCount = 0;
        blankCount = 0;
    }

    double getScore() {
        int total = correctCount + incorrectCount + blankCount;
        return total > 0 ? double(correctCount) / total : 0.000;
    }

    void printWithoutScore() {
        std::cout << correctCount << " corrects, " << incorrectCount << " incorrects and " << blankCount << " blanks." << std::endl;
    }

    void printWithScore() {
        double truncatedScore = truncate(getScore() * 100, reporting::SCORE_TRUNC_GRANULARITY);
        std::cout << correctCount << " corrects, " << incorrectCount << " incorrects and " << blankCount
                  << " blanks. Score: " << std::fixed << std::setprecision(3) << truncatedScore << "%." << std::endl;
    }

    void update(Question::AnswerStatus result) {
        switch (result) {
        case Question::AnswerStatus::CORRECT:
            correctCount++;
            break;
        case Question::AnswerStatus::INCORRECT:
            incorrectCount++;
            break;
        case Question::AnswerStatus::BLANK:
            blankCount++;
            break;
        }
    }

    void update(const StatEntry otherStatEntry) {
        correctCount += otherStatEntry.correctCount;
        incorrectCount += otherStatEntry.incorrectCount;
        blankCount += otherStatEntry.blankCount;
    }
};

class Database {
public:
    Database(std::string csvPath);
    Test* getTest(std::string testName);
    TestTemplate* getTestTemplate(std::string templateName);
    TestAttendance* getAttendance(Test* test);
    void addTest(Test* test);
    void addTestTemplate(TestTemplate* testTemplate);
    void addAttendance(TestAttendance* attendance);
    void recordAnswer(Question* question, Test* test, Question::AnswerStatus result);
    std::vector<Question*> getMatchingQuestions(std::string subject, Question::Difficulty difficulty);
    StatEntry getQuestionStats(Question* question);
    StatEntry getTestStats(Test* test);
    StatEntry getSubjectStats(const std::string& subjectName);
    inline std::map<Question*, StatEntry> getQuestionsStats() { return questionStats_; };
    inline std::map<std::string, StatEntry> getSubjectsStats() { return subjectStats_; }
    std::vector<std::string> getSubjects();
    std::vector<std::string> getTestedSubjects();
    std::vector<TestAttendance*> getAttendances();

private:
    QuestionBank* bank_;
    std::map<std::string, Test*> testsByName_;
    std::map<std::string, TestTemplate*> templatesByName_;
    std::map<Test*, TestAttendance*> attendancesByTest_;
    std::map<Question*, StatEntry> questionStats_;
    std::map<Test*, StatEntry> testStats_;
    std::map<std::string, StatEntry> subjectStats_;
    std::vector<std::string> subjects_;
};

#endif // DATABASE_HEADERFILE