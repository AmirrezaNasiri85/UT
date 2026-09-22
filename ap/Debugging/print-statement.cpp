#include <iostream>
#include <vector>
using namespace std;

int calculateSum(vector<int> numbers) {
    int sum = 0;
    for (int i = 0; i <= numbers.size(); i++) {
        sum += numbers[i];
    }
    return sum;
}

int main() {
    vector<int> numbers = {1,2,3,4,5};
    int totalSum = calculateSum(numbers);
    cout << "Total sum of the array: " << totalSum << endl;

    return 0;
}
