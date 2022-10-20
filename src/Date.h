#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <time.h>

class Date
{
    private:
        unsigned int minute;
        unsigned int hour;
        unsigned int day;
        unsigned int month;
        unsigned int year;

    public:
        Date();
        Date(unsigned int day,unsigned int month,unsigned int year);
        Date(unsigned int minute,unsigned int hour,unsigned int day,unsigned int month,unsigned int year);
        ~Date();

        unsigned int getMinute() const;
        unsigned int getHour() const;
        unsigned int getDay() const;
        unsigned int getMonth() const;
        unsigned int getYear() const;
        void setMinute(const unsigned int);
        void setHour(const unsigned int);
        void setDay(const unsigned int);
        void setMonth(const unsigned int);
        void setYear(const unsigned int);

        friend std::ostream& operator<<(std::ostream &, const Date&);
};

#endif // DATE_H
