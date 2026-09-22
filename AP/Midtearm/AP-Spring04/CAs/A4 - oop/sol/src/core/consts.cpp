#include "consts.hpp"

#include "question.hpp"

using namespace std;

namespace bank {
const map<string, Question::Difficulty> DIFFICULTY_MAPPING{
    {"easy", Question::Difficulty::EASY},
    {"medium", Question::Difficulty::MEDIUM},
    {"hard", Question::Difficulty::HARD},
};
const map<Question::Difficulty, string> DIFFICULTIES_HUMANREADABLE_IN_ORDER{
    {Question::Difficulty::EASY, "Easy"},
    {Question::Difficulty::MEDIUM, "Medium"},
    {Question::Difficulty::HARD, "Hard"},
};

const map<string, ValidAnswer> VALID_ANSWERS_MAPPING{
    {"previous", PREVIOUS_ENTRY},
    {"", BLANK},
    {"1", OPT1},
    {"2", OPT2},
    {"3", OPT3},
    {"4", OPT4},
};
} // namespace bank

namespace coefficients {
int const INCORRECT = 3;
int const CORRECT = 2;
int const BLANK = 1;
} // namespace coefficients