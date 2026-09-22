#ifndef ATTENDANCE_HEADERFILE
#define ATTENDANCE_HEADERFILE

#include <chrono>
#include <vector>

#include "consts.hpp"
#include "test.hpp"

struct TestEntry {
    Question* question;
    int answer;
};

class TestAttendance {
public:
    TestAttendance(Test* test);
    bool isDone();
    void commitAnswer(int answer);
    void moveBack();
    void printCurrentQuestion();
    bank::ValidAnswer inputAnswer();
    inline Test* getTest() { return test_; }
    std::vector<TestEntry> getEntries();
    inline std::chrono::system_clock::time_point getAttendanceTime() { return attendanceTime_; }

private:
    Test* test_;
    bool isDone_;
    std::chrono::system_clock::time_point attendanceTime_;
    std::vector<TestEntry> entries_;
    std::vector<TestEntry>::iterator currPointer_;
    bool isAnswerValid(std::string answer);
};

#endif // ATTENDANCE_HEADERFILE