#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <string>
#include <vector>

class Question {
public:
    enum Difficulty { EASY,
                      MEDIUM,
                      HARD };
    enum AnswerStatus { CORRECT,
                        INCORRECT,
                        BLANK };
    Question(std::string text, std::vector<std::string> options, int correctAnswer, Difficulty difficulty,
             std::string subject);
    AnswerStatus evaluateAnswer(int answer);
    inline Difficulty getDifficulty() { return difficulty_; };
    inline std::string getText() { return text_; }
    inline std::string getSubject() { return subject_; }
    inline std::string getOption(int optionNumber) { return options_[optionNumber - 1]; }

private:
    int correctAnswer_;
    std::vector<std::string> options_;
    std::string text_;
    std::string subject_;
    Difficulty difficulty_;
};

#endif // QUESTION_HPP