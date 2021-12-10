#include "GregorianCalendar.h"
#include "General.h"

bool GregorianCalendar::ifLeapYear(int year) {
    return (((year % 4) == 0) && ((year % 100) != 0))
           || ((year % 400) == 0);
}

GregorianCalendar::GregorianCalendar(int date) {
    year = date / (365 + 1);
    while (date >= GregorianCalendar(1, 1, year + 1))
        year++;
    month = 1;
    while (date > GregorianCalendar(month, LastMonthDay(month, year), year))
        month++;
    GregorianCalendar t = GregorianCalendar(month, 1, year);
    day = date - t + 1;
}

int GregorianCalendar::LastMonthDay(int month, int year)
{
    switch (month) {
        case 2:
            return (ifLeapYear(year) ? 29 : shortest_month);
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

/*
     The GregorianCalendar date of nth x-day in month, year before/after optional day.
     x = 0 means Sunday, x = 1 means Monday, and so on.  If n<0, return the nth
     x-day before month day, year (inclusive).  If n>0, return the nth x-day
     after month day, year (inclusive).  If day is omitted or 0, it defaults
     to 1 if n>0, and month's last day otherwise.
*/
GregorianCalendar GregorianCalendar::NthXday(int n, int x, int month, int year, int day) {
    if (n > 0) {
        if (day == 0) {
            day = 1;
        }
        GregorianCalendar calendar =
                GregorianCalendar(month, day, year);
       
        return
                GregorianCalendar
                        ((7 * (n - 1)) + General::XdayOnOrBefore(6 + calendar, x));
    }
    else {
        if (day == 0) {
            day = LastMonthDay(month, year);
        }
        GregorianCalendar calendar =
                GregorianCalendar(month, day, year);
        int date = (7 * (n + 1)) +
                General::XdayOnOrBefore(calendar, x);
        return GregorianCalendar(date);
    }
}

GregorianCalendar::operator int() { // Computes the absolute date from the GregorianCalendar date.
    int N = day;           // days this month
    for (int m = month - 1; m > 0; m--)
        N = N + LastMonthDay(m, year);
    return
            (N                    // days this year
                    + 365 * (year - 1)   // days in previous years ignoring leap days
                    + (year - 1) / 4       // JulianCalendar leap days before this year...
                    - (year - 1) / 100     // ...minus prior century years...
                    + (year - 1) / 400);   // ...plus prior years divisible by 400
}

