#include <iostream>
using namespace std;

int gcd(int a, int b) {
    // Logical error: wrong base case
    if (a == 0 || b == 0) {  // Should stop when one number becomes 0, not both
        return 0;  // This will return 0 instead of GCD
    }

    return gcd(b, a % b);
}

int main() {
    int num1, num2;

    cout << "Enter two numbers to calculate GCD: ";
    cin >> num1 >> num2;

    if (num1 < 0 || num2 < 0) {
        cout << "GCD is not defined for negative numbers." << endl;
    } else {
        int result = gcd(num1, num2);
        cout << "GCD of " << num1 << " and " << num2 << " is: " << result << endl;
    }

    return 0;
}







// Correct Code

// int gcd(int a, int b) {
//     if (b == 0) {
//         return a;
//     }

//     return gcd(b, a % b);
// }

// int main() {
//     int num1, num2;
//     cout << "Enter two numbers to calculate GCD: ";
//     cin >> num1 >> num2;

//     if (num1 < 0 || num2 < 0) {
//         cout << "GCD is not defined for negative numbers." << endl;
//     } else {
//         int result = gcd(num1, num2);
//         cout << "GCD of " << num1 << " and " << num2 << " is: " << result << endl;
//     }

//     return 0;
// }


