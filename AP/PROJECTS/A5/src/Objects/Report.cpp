#include "Report.hpp"



Report::Report(const int id,
               const string& sender_username,
               const string& reported_username,
               const string& reason)
    :reported_username(reported_username), 
    sender_username(sender_username),
    reason(reason),
    report_id(id)
{}

Report* Report_management::make_reports(const string& sender_username,const string& reported_username, const string& reason){
    Report* new_report = new Report(report_id, sender_username, reported_username, reason);
    report_id += 1;
    return new_report;
}

