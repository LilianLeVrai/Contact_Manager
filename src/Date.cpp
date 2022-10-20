#include "Date.h"

//d�but constructeurs/destructeurs
Date::Date(){
    time_t now = time(NULL);
    struct tm * tm = localtime(&now);
    this->minute=tm->tm_min;
    this->hour=tm->tm_hour;
    this->day=tm->tm_mday;
    this->month=tm->tm_mon+1;
    this->year=tm->tm_year+1900;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year){
    time_t now = time(NULL);
    struct tm * tm = localtime(&now);
    this->minute=tm->tm_min;
    this->hour=tm->tm_hour;
    this->day=day;
    this->month=month;
    this->year=year;
}

Date::Date(unsigned int minute, unsigned int hour, unsigned int day, unsigned int month, unsigned int year){
    this->minute=minute;
    this->hour=hour;
    this->day=day;
    this->month=month;
    this->year=year;
}

Date::~Date(){
}
//fin constructeurs/destructeurs


//d�but accesseurs basiques
unsigned int Date::getMinute() const{
    return this->minute;
}
unsigned int Date::getHour() const{
    return this->hour;
}
unsigned int Date::getDay() const{
    return this->day;
}
unsigned int Date::getMonth() const{
    return this->month;
}
unsigned int Date::getYear() const{
    return this->year;
}


void Date::setMinute(const unsigned int val){
    this->minute=val;
}
void Date::setHour(const unsigned int val){
    this->hour=val;
}
void Date::setDay(const unsigned int val){
    this->day=val;
}
void Date::setMonth(const unsigned int val){
    this->month=val;
}
void Date::setYear(const unsigned int val){
    this->year=val;
}
//fin accesseurs basiques


//surcharge op�rateur pour affichage console
std::ostream& operator<<(std::ostream& os, const Date& date){
    os << date.getDay() << "/" << date.getMonth() << "/" << date.getYear();
    return os;
}

















