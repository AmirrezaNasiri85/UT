#include <bits/stdc++.h> 

using namespace std;

bool construct(string &target, int startIndex, int endIndex){
    int targetLength = endIndex - startIndex + 1; 
    if (targetLength == 1)
        return (target[startIndex] == 'a' || target[startIndex] == 'b');
    if (targetLength == 2){
        if (target[startIndex] == 'a' && target[startIndex + 1] == 'a')
            return true;
        if (target[startIndex] == 'c' && target[startIndex + 1] == 'c')
            return true;
        if (target[startIndex] == 'b' && target[startIndex + 1] == 'a')
            return true;
    }
    
    bool result = false;
    if (target[startIndex] == 'a'){
        if (!result && targetLength > 1 && target[startIndex + 1] == 'a')
            result = construct(target, startIndex + 2, endIndex); 
        if (!result && targetLength > 1 && target[endIndex] == 'a')
            result = construct(target, startIndex + 1, endIndex - 1);
        if (!result && targetLength > 2 && target[endIndex] == 'b' && target[endIndex - 1] == 'b')
            result = construct(target, startIndex + 1, endIndex - 2);
    }
    else if (target[startIndex] == 'b'){
        result = construct(target, startIndex + 1, endIndex); 
    }
    else if (target[startIndex] == 'c'){
        if (!result && targetLength > 1 && target[startIndex + 1] == 'a')
            result = construct(target, startIndex + 2, endIndex);
        if (!result && targetLength > 1 && target[endIndex] == 'b')
            result = construct(target, startIndex + 1, endIndex - 1);
    }
    return result; 
}

int main() {
    string target; 
    cin >> target; 
    int endIndex = target.size() - 1; 
    if (construct(target, 0, endIndex))
        cout << "yes";
    else 
        cout << "no";
    return 0;
}
