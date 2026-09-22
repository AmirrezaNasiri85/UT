#include <cmath>
#include <iostream>
#include <string>

using namespace std;

const string FRAC = "+\\frac{";
const string NUM_DENUM_SEP = "}{";
const string END_OF_FRAC = "}";
const int START_OF_FRAC_NUM = 1;
const int max_level_TO_MAX_DEPTH = 1;
const int NUMBER_OF_SUBTREES = 2;

int max_level_to_last_leaf_number(int max_level) {
    return pow(NUMBER_OF_SUBTREES, max_level - max_level_TO_MAX_DEPTH);
}

bool check_if_finished(int n, int max_level) {
    return n >= max_level_to_last_leaf_number(max_level);
}

string create_output(int n, string numerator, string denominator) {
    return to_string(n) + FRAC + numerator + NUM_DENUM_SEP + denominator +
           END_OF_FRAC;
}

string recursive_latex_frac(int n, int max_level) {
    if (check_if_finished(n, max_level)) {
        return to_string(n);
    }

    string numerator = recursive_latex_frac(2 * n, max_level);
    string denominator = recursive_latex_frac(2 * n + 1, max_level);
    return create_output(n, numerator, denominator);
}

int main() {
    int the_max_level;
    cin >> the_max_level;
    cout << recursive_latex_frac(START_OF_FRAC_NUM, the_max_level) << endl;
}