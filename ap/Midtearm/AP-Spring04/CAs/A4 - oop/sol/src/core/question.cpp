#include "question.hpp"

using namespace std;

Question::Question(string text, vector<string> options, int correctAnswer, Difficulty difficulty, string subject) {
    text_ = text;
    options_ = options;
    correctAnswer_ = correctAnswer;
    difficulty_ = difficulty;
    subject_ = subject;
}

Question::AnswerStatus Question::evaluateAnswer(int answer) {
    if (answer == 0) {
        return AnswerStatus::BLANK;
    }
    return answer == correctAnswer_ ? AnswerStatus::CORRECT : AnswerStatus::INCORRECT;
}