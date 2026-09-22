#include "utghalam.hpp"

#include <algorithm>
#include <climits>
#include <iostream>

#include "../core/attendance.hpp"
#include "../core/consts.hpp"
#include "../core/template.hpp"
#include "../utils.hpp"
#include "database.hpp"

using namespace std;

UtGhalam::UtGhalam(Database* db) {
    db_ = db;
}

TestTemplate* UtGhalam::createTemplate(const string& templateName, const vector<Config>& configs, string& errMsg) {
    if (db_->getTestTemplate(templateName) != nullptr) {
        errMsg = "Duplicate name: '" + templateName + "'";
        return nullptr;
    }

    TestTemplate* testTemplate = new TestTemplate{templateName, configs};
    db_->addTestTemplate(testTemplate);
    return testTemplate;
}

Test* UtGhalam::generateTest(const string& testName, const string& templateName, string& errMsg) {
    TestTemplate* testTemplate = db_->getTestTemplate(templateName);
    if (testTemplate == nullptr) {
        errMsg = "Could not find template: '" + templateName + "'";
        return nullptr;
    }
    if (db_->getTest(testName) != nullptr) {
        errMsg = "Duplicate name: '" + templateName + "'";
        return nullptr;
    }

    vector<Question*> questions = selectQuestions(testTemplate, errMsg);
    if (!errMsg.empty()) {
        return nullptr;
    }

    Test* test = new Test{testName, questions, testTemplate};
    db_->addTest(test);
    return test;
}

Test* UtGhalam::autoGenerateTest(const string& testName, string& errMsg) {
    vector<string> subjects = db_->getSubjects();
    if (subjects.size() < autogenerate::PLAN.size()) {
        errMsg = "Not enough available subjects to create an auto-generated test.";
        return nullptr;
    }

    sort(subjects.begin(), subjects.end(), [this](const string& s1, const string& s2) {
        if (db_->getSubjectStats(s1).getScore() == db_->getSubjectStats(s2).getScore()) {
            return s1 < s2;
        }
        return db_->getSubjectStats(s1).getScore() < db_->getSubjectStats(s2).getScore();
    });

    vector<Config> configs;
    int selectedSubjectIdx = 0;
    for (auto [role, countPerDifficulty] : autogenerate::PLAN) {
        string subject = subjects[selectedSubjectIdx++];
        for (auto [difficulty, count] : countPerDifficulty) {
            configs.push_back(Config{subject, difficulty, count});
        }
    }

    string templateName = generateUniqueString("AUTO_GENERATED_TEMPLATE_NAME");
    createTemplate(templateName, configs, errMsg);
    if (!errMsg.empty()) {
        return nullptr;
    }

    return generateTest(testName, templateName, errMsg);
}

void UtGhalam::attendTest(const string& testName, string& errMsg) {
    Test* test = db_->getTest(testName);
    if (test == nullptr) {
        errMsg = "Could not find test: '" + testName + "'";
        return;
    }
    if (db_->getAttendance(test)) {
        errMsg = "Test '" + testName + "' is already attended.";
        return;
    }

    TestAttendance* attendance = new TestAttendance(test);
    db_->addAttendance(attendance);

    cout << testName << ":" << endl;
    while (!attendance->isDone()) {
        attendance->printCurrentQuestion();
        switch (attendance->inputAnswer()) {
        case bank::PREVIOUS_ENTRY:
            attendance->moveBack();
            break;
        case bank::BLANK:
            attendance->commitAnswer(0);
            break;
        case bank::OPT1:
            attendance->commitAnswer(1);
            break;
        case bank::OPT2:
            attendance->commitAnswer(2);
            break;
        case bank::OPT3:
            attendance->commitAnswer(3);
            break;
        case bank::OPT4:
            attendance->commitAnswer(4);
            break;
        }
    }

    updateStatistics(attendance);
}

void UtGhalam::reportAll() {
    cout << "Total report:" << endl
         << endl;

    StatEntry totalStats = StatEntry();
    vector<string> subjects = db_->getTestedSubjects();
    sort(subjects.begin(), subjects.end());
    for (string subject : subjects) {
        cout << subject + ": ";
        StatEntry subjectStat = db_->getSubjectStats(subject);
        subjectStat.printWithScore();
        totalStats.update(subjectStat);
    }

    cout << endl
         << "Total results: ";
    totalStats.printWithoutScore();
    double truncatedScore = truncate(totalStats.getScore() * 100, reporting::SCORE_TRUNC_GRANULARITY);
    cout << "Total score: " << fixed << setprecision(3) << truncatedScore << "%." << endl;
}

void UtGhalam::reportTest(const string& testName, string& errMsg) {
    Test* test = db_->getTest(testName);
    if (test == nullptr) {
        errMsg = "Could not find test: '" + testName + "'";
        return;
    }
    TestAttendance* attendance = db_->getAttendance(test);
    if (attendance == nullptr) {
        errMsg = "Test '" + testName + "'has not been attended.";
        return;
    }

    StatEntry testStats = db_->getTestStats(test);
    map<string, StatEntry> testPerSubjectStats;
    for (TestEntry testEntry : attendance->getEntries()) {
        testPerSubjectStats[testEntry.question->getSubject()].update(testEntry.question->evaluateAnswer(testEntry.answer));
    }

    cout << "Results for " + testName + ":" << endl
         << endl;
    for (auto [subject, stat] : testPerSubjectStats) {
        cout << subject + ": ";
        stat.printWithScore();
    }

    cout << endl
         << "Total results: ";
    testStats.printWithoutScore();
    double truncatedScore = truncate(testStats.getScore() * 100, reporting::SCORE_TRUNC_GRANULARITY);
    cout << "Total score: " << fixed << setprecision(3) << truncatedScore << "%." << endl;
}

vector<Question*> UtGhalam::selectQuestions(TestTemplate* testTemplate, string& errMsg) {
    vector<Question*> selectedQuestions;
    for (Config config : testTemplate->configs) {
        vector<Question*> matchingQuestions = db_->getMatchingQuestions(config.subject, config.difficulty);
        if (int(matchingQuestions.size()) < config.questionsCount) {
            errMsg = "Not enough matching question to generate test";
            return selectedQuestions;
        }

        map<Question*, int> questionPriorities;
        for (Question* matchingQuestion : matchingQuestions) {
            StatEntry stats = db_->getQuestionStats(matchingQuestion);
            int priority = coefficients::INCORRECT * stats.incorrectCount +
                           coefficients::BLANK * stats.blankCount - coefficients::CORRECT * stats.correctCount;
            questionPriorities[matchingQuestion] = priority;
        }

        sort(matchingQuestions.begin(), matchingQuestions.end(), [questionPriorities](Question* q1, Question* q2) {
            if (questionPriorities.at(q1) != questionPriorities.at(q2)) {
                return questionPriorities.at(q1) > questionPriorities.at(q2);
            }
            return q1->getText() < q2->getText();
        });

        selectedQuestions.insert(selectedQuestions.end(), matchingQuestions.begin(), matchingQuestions.begin() + config.questionsCount);
    }

    sort(selectedQuestions.begin(), selectedQuestions.end(), [](Question* q1, Question* q2) {
        if (q1->getSubject() != q2->getSubject()) {
            return q1->getSubject() < q2->getSubject();
        }
        return q1->getText() < q2->getText();
    });

    return selectedQuestions;
}

void UtGhalam::updateStatistics(TestAttendance* attendance) {
    for (TestEntry entry : attendance->getEntries()) {
        Question::AnswerStatus result = entry.question->evaluateAnswer(entry.answer);
        db_->recordAnswer(entry.question, attendance->getTest(), result);
    }
}

void UtGhalam::reportTests() {
    vector<TestAttendance*> attendances = db_->getAttendances();
    sort(attendances.begin(), attendances.end(), [](TestAttendance* a1, TestAttendance* a2) {
        return a1->getAttendanceTime() < a2->getAttendanceTime();
    });

    cout << "Results per attended tests:" << endl
         << endl;
    for (TestAttendance* attendance : attendances) {
        StatEntry testStats = db_->getTestStats(attendance->getTest());
        cout << (attendance->getTest())->getName() << ": ";
        testStats.printWithScore();
    }
}

void UtGhalam::reportSubject(const string& subjectName) {
    map<Question::Difficulty, StatEntry> difficultyStats;
    for (auto [question, stat] : db_->getQuestionsStats()) {
        if (question->getSubject() != subjectName) {
            continue;
        }

        difficultyStats[question->getDifficulty()].update(stat);
    }

    cout << "Results for " << subjectName << ": " << endl
         << endl;
    for (auto [difficulty, name] : bank::DIFFICULTIES_HUMANREADABLE_IN_ORDER) {
        cout << name << ": ";
        difficultyStats[difficulty].printWithoutScore();
    }

    double truncatedScore = truncate(db_->getSubjectStats(subjectName).getScore() * 100, reporting::SCORE_TRUNC_GRANULARITY);
    cout << endl
         << "Total score: " << fixed << setprecision(3) << truncatedScore << "%." << endl;
}