#include <iostream>
#include <stdexcept>
using namespace std;

class Date {
public:
  // methods or member functions
  void setDate(int d, int m, int y);
  void printDate();
private:
  // fields or member variables
  int day;
  int month;
  int year;
};

void Date::setDate(int d, int m, int y) {
  if (y < 0 || m < 1 || m > 12 || d < 1 || 
      (m < 7 && d > 31) || 
      (m > 6 && m < 12 && d > 30) ||
      (m == 12 && d > 29)) // leap years not checked
    throw invalid_argument("Invalid date parameters");

  day = d;
  month = m;
  year = y;
}

void Date::printDate() {
  cout << day << '/' << month << '/' << year << endl;
}

int main() {
  Date bd;
  bd.setDate(31, 6, 1352);
  bd.printDate();
  // compile error: access to private member
  // bd.day = 14;
}