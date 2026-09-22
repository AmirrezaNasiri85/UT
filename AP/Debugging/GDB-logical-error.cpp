#include <iostream>
using namespace std;

// Calculate average of two numbers and compare with 8

int main()
{
    int num1, num2;
    cout << "Enter first number:" << endl;
    cin >> num1;
    cout << "Enter second number:" << endl;
    cin >> num2;
    float average = (num1 + num2) / 2;
    if (average = 8)
    {
        cout << "Average is 8!" << endl;
    }
    else
    {
        cout << "Average is not 8!" << endl;
    }

    return 0;
}