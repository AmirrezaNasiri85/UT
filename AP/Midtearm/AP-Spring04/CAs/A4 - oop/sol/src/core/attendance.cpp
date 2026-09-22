#include "attendance.hpp"

#include <iostream>

#include "../utils.hpp"
#include "consts.hpp"
#include "test.hpp"

using namespace std;

TestAttendance::TestAttendance(Test* test) {
    for (Question* question : test->getQuestions()) {
        entries_.push_back(TestEntry{question, 0});
    }
    currPointer_ = entries_.begin();
    test_ = test;
    attendanceTime_ = chrono::system_clock::now();
}

bool TestAttendance::isDone() { return isDone_; }

void TestAttendance::commitAnswer(int answer) {
    currPointer_->answer = answer;
    currPointer_++;

    if (currPointer_ == entries_.end()) {
        isDone_ = true;
    }
}

void TestAttendance::moveBack() { currPointer_--; }

void TestAttendance::printCurrentQuestion() {
    int questionsNumber = (currPointer_ - entries_.begin()) + 1;
    Question* currQuestion = currPointer_->question;
    cout << endl
         << questionsNumber << ") " << currQuestion->getText() << endl;
    for (int optionNumber = 1; optionNumber <= 4; optionNumber++) {
        cout << "    " << optionNumber << ". " << currQuestion->getOption(optionNumber);
        if (optionNumber == currPointer_->answer)
            cout << " <-";
        cout << endl;
    }
}

bank::ValidAnswer TestAttendance::inputAnswer() {
    cout << "Your answer: ";
    string enterredAnswer;
    getline(cin, enterredAnswer);
    while (!isAnswerValid(enterredAnswer)) {
        cout << "Invalid answer, please try again." << endl;
        cout << "Your answer: ";
        getline(cin, enterredAnswer);
    }

    return bank::VALID_ANSWERS_MAPPING.at(enterredAnswer);
}

bool TestAttendance::isAnswerValid(string answer) {
    if (!MAP_CONTAINS(bank::VALID_ANSWERS_MAPPING, answer)) {
        return false;
    }
    if (bank::VALID_ANSWERS_MAPPING.at(answer) == bank::ValidAnswer::PREVIOUS_ENTRY) {
        return currPointer_ != entries_.begin();
    }
    return true;
}

std::vector<TestEntry> TestAttendance::getEntries() {
    return entries_;
}