#include <stdio.h>

int isLeap(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

int daysInMonth(int year, int month) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeap(year)) return 29;
    return days[month];
}

int main() {
    int year = 2000, month = 1, day = 1;
    int weekday = 6;
    int total = 0;
    
    while (!(year == 2020 && month == 10 && day == 2)) {
        int run = 1;
        if (day == 1 || weekday == 1) {
            run = 2;
        }
        total += run;
        
        weekday = (weekday + 1) % 7;
        day++;
        
        if (day > daysInMonth(year, month)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }
    
    printf("%d\n", total);
    return 0;
}