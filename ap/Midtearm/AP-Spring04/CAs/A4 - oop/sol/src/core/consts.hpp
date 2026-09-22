#ifndef BANK_CONSTS_HEADERFILE
#define BANK_CONSTS_HEADERFILE

#include <map>
#include <string>

#include "question.hpp"

namespace bank {
extern const std::map<std::string, Question::Difficulty> DIFFICULTY_MAPPING;
extern const std::map<Question::Difficulty, std::string> DIFFICULTIES_HUMANREADABLE_IN_ORDER;

enum ValidAnswer { PREVIOUS_ENTRY,
                   BLANK,
                   OPT1,
                   OPT2,
                   OPT3,
                   OPT4 };
extern const std::map<std::string, ValidAnswer> VALID_ANSWERS_MAPPING;
} // namespace bank

namespace coefficients {
extern const int INCORRECT;
extern const int CORRECT;
extern const int BLANK;
} // namespace coefficients

namespace autogenerate {

enum SubjectRole {
    PRIMARY,
    SECONDARY
};

inline const std::map<SubjectRole, std::map<Question::Difficulty, int>> PLAN = {
    {PRIMARY, {{Question::Difficulty::EASY, 3}, {Question::Difficulty::MEDIUM, 2}, {Question::Difficulty::HARD, 1}}},
    {SECONDARY, {{Question::Difficulty::EASY, 2}, {Question::Difficulty::MEDIUM, 1}, {Question::Difficulty::HARD, 1}}}};

} // namespace autogenerate

namespace reporting {
constexpr int SCORE_TRUNC_GRANULARITY = 3;
}

#endif // BANK_CONSTS_HEADERFILE
