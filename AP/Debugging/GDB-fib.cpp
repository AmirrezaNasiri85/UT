#include <iostream>

using namespace std;
 
int main(){
        cout << "Enter n: ";
        int n;
        cin >> n;
        int prev = 1;
        int cur = 1;
        for (int i = 2; i < n; i++){
                cur += prev;
                prev = cur;
        }
        cout << "Fibonacci number " << n << " : ";
        cout << cur << endl;
}

