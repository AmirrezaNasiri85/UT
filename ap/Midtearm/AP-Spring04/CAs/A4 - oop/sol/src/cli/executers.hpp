#ifndef EXECUTERS_HEADERFILE
#define EXECUTERS_HEADERFILE

#include <string>
#include <vector>

#include "../service/utghalam.hpp"

void createTemplateExecuter(std::vector<std::string> arguments, UtGhalam* service);
void generateTestExecuter(std::vector<std::string> arguments, UtGhalam* service);
void attendTestExecuter(std::vector<std::string> arguments, UtGhalam* service);
void autoGenerateTestExecuter(std::vector<std::string> arguments, UtGhalam* service);
void reportAllExecuter(std::vector<std::string> arguments, UtGhalam* service);
void reportTestExecuter(std::vector<std::string> arguments, UtGhalam* service);
void reportTestsExecuter(std::vector<std::string> arguments, UtGhalam* service);
void reportSubjectExecuter(std::vector<std::string> arguments, UtGhalam* service);

#endif // EXECUTERS_HEADERFILE