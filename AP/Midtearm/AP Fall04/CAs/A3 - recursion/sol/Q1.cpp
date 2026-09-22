#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void readItems(int x, vector<int>& allPrices) {
    if (x == 0) {
        return;
    }
    
    int price;
    cin >> price;
    allPrices.push_back(price);
    
    readItems(x - 1, allPrices);
}

void readSellers(int F, vector<int>& allPrices) {
    if (F == 0) {
        return;
    }
    
    int x;
    cin >> x;
    
    readItems(x, allPrices);
    
    readSellers(F - 1, allPrices);
}

void printPurchasesRecursive(const vector<int>& purchaseList, int index) {
    if (index == purchaseList.size()) {
        return;
    }
    
    cout << " " << purchaseList[index];
    printPurchasesRecursive(purchaseList, index + 1);
}

int doShopping(int money, vector<int>& allPrices, vector<int>& cyclePurchases) {
    if (allPrices.empty()) {
        return money;
    }
    
    int cheapestPrice = allPrices[0];
    
    if (money < cheapestPrice) {
        return money;
    }
    
    money -= cheapestPrice;
    cyclePurchases.push_back(cheapestPrice);
    allPrices.erase(allPrices.begin());
    
    return doShopping(money, allPrices, cyclePurchases);
}

void manageCycles(int numberOfCycles, int currentMoney, vector<int>& allPrices) {
    if (numberOfCycles == 0) {
        return;
    }
    
    int moneyToAdd;
    cin >> moneyToAdd;
    currentMoney += moneyToAdd;
    
    vector<int> cyclePurchases;
    
    int remainingMoney = doShopping(currentMoney, allPrices, cyclePurchases);
    
    cout << cyclePurchases.size();
    printPurchasesRecursive(cyclePurchases, 0);
    cout << endl;
    
    manageCycles(numberOfCycles - 1, remainingMoney, allPrices);
}


int main() {
    int F;
    cin >> F;
    
    vector<int> allPrices;
    readSellers(F, allPrices);  
    
    sort(allPrices.begin(), allPrices.end());
    
    int n;
    cin >> n;
    
    manageCycles(n, 0, allPrices);
    
    return 0;
}