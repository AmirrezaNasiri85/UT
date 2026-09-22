#include "utils.hpp"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

string trimString(string str) {
    size_t start = str.find_first_not_of(" ");
    if (start == string::npos) {
        return "";
    }

    size_t end = str.find_last_not_of(" ");
    return str.substr(start, end - start + 1);
}

vector<string> splitString(string str, char delimiter) {
    vector<string> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        token = trimString(token);
        if (token.empty()) {
            continue;
        }

        result.push_back(token);
    }

    return result;
}

vector<string> quotationWiseSplit(string str) {
    vector<string> result;
    string current;
    bool inQuotes = false;
    for (char c : str) {
        if (c == '\'') {
            inQuotes = !inQuotes;
            if (!inQuotes) {
                result.push_back(current);
                current.clear();
            }
            continue;
        }

        if (c == ' ' && !inQuotes) {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
            continue;
        }

        current += c;
    }

    if (!current.empty()) {
        result.push_back(current);
    }

    return result;
}

vector<map<string, string>> readCSV(string csvPath) {
    ifstream file(csvPath);
    if (!file.is_open()) {
        throw invalid_argument("Could not open file: " + csvPath);
    }

    string line;
    getline(file, line);
    vector<string> headers = splitString(line, ',');

    vector<map<string, string>> rows;
    while (getline(file, line)) {
        vector<string> row = splitString(line, ',');
        map<string, string> mappedRow;
        for (size_t i = 0; i < headers.size(); i++) {
            mappedRow[headers[i]] = row[i];
        }
        rows.push_back(mappedRow);
    }

    file.close();
    return rows;
}

string generateUniqueString(string suffix = "") {
    stringstream ss;
    time_t t = time(nullptr);
    ss << put_time(localtime(&t), "%Y%m%d_%H%M%S");
    if (!suffix.empty()) {
        ss << "_" << suffix;
    }

    return ss.str();
}

double truncate(double inputNumber, int granularity) {
    double factor = pow(10.0, granularity);
    return floor(inputNumber * factor) / factor;
}