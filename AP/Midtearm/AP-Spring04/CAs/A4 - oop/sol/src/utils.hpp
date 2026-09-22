#ifndef UTILS_HEADERFILE
#define UTILS_HEADERFILE

#include <map>
#include <string>
#include <vector>

#define MAP_CONTAINS(map, key) ((map).find(key) != (map).end())

std::string trimString(std::string str);
std::vector<std::string> splitString(std::string str, char delimiter);
std::vector<std::map<std::string, std::string>> readCSV(std::string csvPath);
std::vector<std::string> quotationWiseSplit(std::string str);
std::string generateUniqueString(std::string suffix);
double truncate(double inputNumber, int granularity);

#endif // UTILS_HEADERFILE
