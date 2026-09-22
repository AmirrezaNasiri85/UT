#include "test.hpp"

using namespace std;

Test::Test(string name, vector<Question*> questions, TestTemplate* startingTemplate) {
    name_ = name;
    questions_ = questions;
    startingTemplate_ = startingTemplate;
}