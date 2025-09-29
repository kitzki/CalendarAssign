#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//--------------------------------
// Check if a string is a number
//--------------------------------
bool isNumber(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

//--------------------------------
// Checks if a year is leap
//--------------------------------
bool isLeap(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    return (year % 4 == 0);
}

//--------------------------------
// Days in each month
//--------------------------------
int getDaysInMonth(int year, int month) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 1 && isLeap(year)) return 29;
    return daysInMonth[month];
}

//---------------------------------
// Print header for each month
//---------------------------------
void printHeader(int year, int month) {
    string monthNames[] = {
        "JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE",
        "JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"
    };
    string title = monthNames[month] + " " + to_string(year);
    int width = 31;
    int pad = (width - title.size())/2;
    cout << string(pad,' ') << title << "\n";
    cout << "  Su  Mo  Tu  We  Th  Fr  Sa\n";
    cout << "----------------------------\n";
}

//----------------------------------
// Print calendar for a single month
//----------------------------------
int printMonth(int year, int month, int startDay) {
    printHeader(year, month);

    for (int i = 0; i < startDay; i++) cout << "    ";

    int days = getDaysInMonth(year, month);
    for (int dayOfMonth = 1; dayOfMonth <= days; dayOfMonth++) {
        cout << setw(4) << dayOfMonth;
        startDay++;
        if (startDay == 7) {
            startDay = 0;
            cout << "\n";
        }
    }
    if (startDay != 0) cout << "\n";
    cout << "\n";
    return startDay;
}

//------------------------------------------------
// Compute the weekday of Jan 1 for a given year
//------------------------------------------------
int computeStartDay(int year) {
    // 0 = Sunday, 1 = Monday,... 3=Wednesday
    int day = 3;
    for (int y = 1800; y < year; y++) {
        day = (day + (isLeap(y)?366:365)) % 7;
    }
    return day;
}

int main() {
    string input;
    cout << "Enter the year --> ";
    cin >> input;

    if (input.length() != 4 || !isNumber(input)) {
        cout << "Invalid input. Please enter a 4-digit year.\n";
        return 1;
    }

    while (!isNumber(input)) {
        cout << "Invalid input. Please enter only digits.\n";
        return 1;
    }

    int year = stoi(input);

    while (year < 1800) {
        cout << "Year must be >= 1800\n";
        return 1;
    }

    int startDay = computeStartDay(year);
    for (int month = 0; month < 12; month++) {
        startDay = printMonth(year, month, startDay);
    }
    return 0;
}