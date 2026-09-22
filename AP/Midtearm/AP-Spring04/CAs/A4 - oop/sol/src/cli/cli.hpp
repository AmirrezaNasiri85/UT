#ifndef CLI_HEADERFILE
#define CLI_HEADERFILE

#include "../service/utghalam.hpp"

class CliHandler {
public:
    CliHandler(UtGhalam* utGhalamService);
    void start();

private:
    UtGhalam* utGhalamService_;
    void handleReportCommands(std::vector<std::string> arguments);
    void handleCommands(std::string commandStarter, std::vector<std::string> arguments);
};

#endif // CLI_HEADERFILE