#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Report{
    string reported_username;
    string sender_username;
    string reason;
    int report_id;

    Report(const int id, const string& sender_username,const string& reported_username, const string& reason);
};


class Report_management{
private:
    int report_id = 1;
public:

    Report* make_reports(const string& sender_username,const string& reported_username, const string& reason);
};

