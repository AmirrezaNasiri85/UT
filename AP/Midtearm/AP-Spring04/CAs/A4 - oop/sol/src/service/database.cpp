#include "database.hpp"

#include "../utils.hpp"

using namespace std;

Database::Database(string csvPath) {
    bank_ = new QuestionBank(csvPath);
    subjects_ = bank_->getSubjects();
}

Test* Database::getTest(std::string testName) {
    if (MAP_CONTAINS(testsByName_, testName)) {
        return testsByName_[testName];
    }
    return nullptr;
}

TestTemplate* Database::getTestTemplate(std::string templateName) {
    if (MAP_CONTAINS(templatesByName_, templateName)) {
        return templatesByName_[templateName];
    }
    return nullptr;
}

TestAttendance* Database::getAttendance(Test* test) {
    if (MAP_CONTAINS(attendancesByTest_, test)) {
        return attendancesByTest_[test];
    }
    return nullptr;
}

void Database::addTest(Test* test) {
    testsByName_[test->getName()] = test;
}

void Database::addTestTemplate(TestTemplate* testTemplate) {
    templatesByName_[testTemplate->name] = testTemplate;
}

void Database::addAttendance(TestAttendance* attendance) {
    attendancesByTest_[attendance->getTest()] = attendance;
}

void Database::recordAnswer(Question* question, Test* test, Question::AnswerStatus result) {
    questionStats_[question].update(result);
    subjectStats_[question->getSubject()].update(result);
    testStats_[test].update(result);
}

vector<Question*> Database::getMatchingQuestions(string subject, Question::Difficulty difficulty) {
    return bank_->getMatchingQuestions(subject, difficulty);
}

StatEntry Database::getQuestionStats(Question* question) {
    return questionStats_[question];
}

StatEntry Database::getTestStats(Test* test) {
    return testStats_[test];
}

StatEntry Database::getSubjectStats(const std::string& subjectName) {
    return subjectStats_[subjectName];
}

vector<string> Database::getSubjects() {
    return subjects_;
}

vector<string> Database::getTestedSubjects() {
    vector<string> subjects;
    for (auto [subject, _] : subjectStats_) {
        subjects.push_back(subject);
    }
    return subjects;
}

vector<TestAttendance*> Database::getAttendances() {
    vector<TestAttendance*> attendances;
    for (const auto& entry : attendancesByTest_)
        attendances.push_back(entry.second);

    return attendances;
}