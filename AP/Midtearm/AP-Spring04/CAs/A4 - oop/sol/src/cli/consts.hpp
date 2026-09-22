#ifndef COMMANDS_CONSTS_HEADERFILE
#define COMMANDS_CONSTS_HEADERFILE

namespace commands {
constexpr char CREATE_TEMPLATE_STARTER[] = "create_template";
constexpr char GENERATE_TEST_STARTER[] = "generate_test";
constexpr char ATTEND_TEST_STARTER[] = "attend";
constexpr char AUTOGENERATE_TEST_STARTER[] = "auto_generate";
constexpr char REPORT_STARTER[] = "report";
constexpr char REPORT_ALL_STARTER[] = "all";
constexpr char REPORT_TEST_STARTER[] = "test";
constexpr char REPORT_TESTS_STARTER[] = "tests";
constexpr char REPORT_SUBJECT_STARTER[] = "subject";
} // namespace commands

namespace errormessages {
constexpr char WRONG_NUMBER_OF_ARGS_ERR_MSG[] = "Wrong number of arguments.";
constexpr char INVALID_COMMAND_ERR_MSG[] = "Inavlid command.";
} // namespace errormessages

#endif