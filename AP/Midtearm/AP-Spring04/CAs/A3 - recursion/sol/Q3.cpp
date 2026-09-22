#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const double TAX_RATE = 1.1;
const double PERCENTAGE_DIVISOR = 100.0;

vector<string> bestSubset;
int maxTotalPrice = -1;

double calculateTotalAfterTax(int totalPrice) { return totalPrice * TAX_RATE; }

double calculateDiscount(double totalAfterTax, int discountPercentage) {
    return (totalAfterTax * discountPercentage) / PERCENTAGE_DIVISOR;
}

bool isValidSubset(double totalAfterTax, double discount, int minThreshold,
                   int maxDiscount) {
    return (totalAfterTax >= minThreshold - 1e-9) &&
           (discount <= maxDiscount + 1e-9);
}

void generateSubsets(const vector<pair<string, int>>& menuItems, int index,
                     vector<string>& currentSubset, int currentTotalPrice,
                     int discountPercentage, int minThreshold,
                     int maxDiscount) {
    if (index == menuItems.size()) {
        double totalAfterTax = calculateTotalAfterTax(currentTotalPrice);
        double discount = calculateDiscount(totalAfterTax, discountPercentage);

        if (isValidSubset(totalAfterTax, discount, minThreshold, maxDiscount)) {
            if (currentTotalPrice > maxTotalPrice) {
                maxTotalPrice = currentTotalPrice;
                bestSubset = currentSubset;
            }
        }
        return;
    }

    currentSubset.push_back(menuItems[index].first);
    generateSubsets(menuItems, index + 1, currentSubset,
                    currentTotalPrice + menuItems[index].second,
                    discountPercentage, minThreshold, maxDiscount);
    currentSubset.pop_back();

    generateSubsets(menuItems, index + 1, currentSubset, currentTotalPrice,
                    discountPercentage, minThreshold, maxDiscount);
}

int main() {
    int numItems, discountPercentage, minThreshold, maxDiscount;
    cin >> numItems >> discountPercentage >> minThreshold >> maxDiscount;

    vector<pair<string, int>> menuItems(numItems);
    for (int i = 0; i < numItems; ++i) {
        cin >> menuItems[i].first >> menuItems[i].second;
    }

    vector<string> currentSubset;
    generateSubsets(menuItems, 0, currentSubset, 0, discountPercentage,
                    minThreshold, maxDiscount);

    for (const string& item : bestSubset) {
        cout << item << endl;
    }

    return 0;
}