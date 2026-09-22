#include "bits/stdc++.h"

using namespace std;

const char SEP = ' ';

int find_oldest_index(int start, int end, vector<int>& age) {
    int index_of_oldest = start;
    for (int i = start + 1; i <= end; i++) {
        if (age[i] > age[index_of_oldest]) {
            index_of_oldest = i;
        }
    }
    return index_of_oldest;
}

void perform_operation(int start, int end, vector<int>& received_money, vector<int>& age, vector<int>& money) {
    if (start == end) {
        received_money[start] += money[start];
        return;
    }
    int index_of_oldest = find_oldest_index(start, end, age);
    bool has_left_child = (start != index_of_oldest);
    bool has_right_child = (end != index_of_oldest);
    int num_of_child = has_left_child + has_right_child;
    int left_child_index, right_child_index;
    if (has_left_child) {
        left_child_index = find_oldest_index(start, index_of_oldest - 1, age);
        received_money[left_child_index] += money[index_of_oldest] / num_of_child;
        perform_operation(start, index_of_oldest - 1, received_money, age, money);
    }
    if (has_right_child) {
        right_child_index = find_oldest_index(index_of_oldest + 1, end, age);
        received_money[right_child_index] += money[index_of_oldest] / num_of_child;
        perform_operation(index_of_oldest + 1, end, received_money, age, money);
    }
}

int main() {
    int num_of_members;
    cin >> num_of_members;
    vector<int> age(num_of_members), money(num_of_members), received_money(num_of_members, 0);
    for (int i = 0; i < num_of_members; i++)
        cin >> age[i];
    for (int i = 0; i < num_of_members; i++)
        cin >> money[i];
    int start = 0, end = num_of_members - 1;
    perform_operation(start, end, received_money, age, money);
    for (int i = 0; i < num_of_members; i++)
        cout << received_money[i] << SEP;
    return 0;
}