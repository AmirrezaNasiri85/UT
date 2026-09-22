#ifndef UTGHALAM_HEADERFILE
#define UTGHALAM_HEADERFILE

#include <string>

#include "../core/attendance.hpp"
#include "../core/template.hpp"
#include "../core/test.hpp"
#include "database.hpp"

class UtGhalam {
public:
    UtGhalam(Database* db);
    TestTemplate* createTemplate(const std::string& templateName, const std::vector<Config>& configs, std::string& errMsg);
    Test* generateTest(const std::string& testName, const std::string& templateName, std::string& errMsg);
    void attendTest(const std::string& testName, std::string& errMsg);
    Test* autoGenerateTest(const std::string& testName, std::string& errMsg);
    void reportAll();
    void reportTest(const std::string& testName, std::string& errMsg);
    void reportTests();
    void reportSubject(const std::string& subjectName);

private:
    void updateStatistics(TestAttendance* attendance);
    std::vector<Question*> selectQuestions(TestTemplate* testTemplate, std::string& errMsg);
    Database* db_;
};

#endif // UTGHALAM_HEADERFILE