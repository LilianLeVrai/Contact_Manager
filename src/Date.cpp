/**
 * @file Date.cpp
 * @brief Fichier cpp de la classe Date
 */

#include "Date.h"

//debut constructeurs/destructeurs
Date::Date(){
    time_t now = time(NULL);
    struct tm * tm = localtime(&now);
    this->minute=tm->tm_min;
    this->hour=tm->tm_hour;
    this->day=tm->tm_mday;
    this->month=tm->tm_mon+1;
    this->year=tm->tm_year+1900;
    this->dateType=WithoutHours;
}

Date::Date(unsigned int day, unsigned int month, unsigned int year){
    time_t now = time(NULL);
    struct tm * tm = localtime(&now);
    this->minute=tm->tm_min;
    this->hour=tm->tm_hour;
    this->day=day;
    this->month=month;
    this->year=year;
    this->dateType=WithoutHours;
}

Date::Date(unsigned int minute, unsigned int hour, unsigned int day, unsigned int month, unsigned int year){
    this->minute=minute;
    this->hour=hour;
    this->day=day;
    this->month=month;
    this->year=year;
    this->dateType=WithoutHours;
}

Date::Date(const std::string s){
    if(s.size()!=10 && s.size()!=16)//si le format n'est pas bon
        {
        time_t now = time(NULL);
        struct tm * tm = localtime(&now);
        this->minute=tm->tm_min;
        this->hour=tm->tm_hour;
        this->day=tm->tm_mday;
        this->month=tm->tm_mon+1;
        this->year=tm->tm_year+1900;
        }
     else//si le format est bon
        {
        this->day=std::stoi(s.substr(0,2));
        this->month=std::stoi(s.substr(3,2));
        this->year=std::stoi(s.substr(6,4));
        if(s.size()==16)
            {
            this->hour=std::stoi(s.substr(11,2));
            this->minute=std::stoi(s.substr(14,2));
            }
        else
            {
            time_t now = time(NULL);
            struct tm * tm = localtime(&now);
            this->minute=tm->tm_min;
            this->hour=tm->tm_hour;
            }
        }
     this->dateType=WithoutHours;
}

Date::~Date(){
}
//fin constructeurs/destructeurs


//debut accesseurs basiques
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



std::string addZero(int i){
    std::string s;
    if(i<10){s="0"+std::to_string(i);}
    else{s=std::to_string(i);}
    return s;
}

std::string Date::toString() const{
    std::string s;
    s = addZero(this->getDay()) + "/" + addZero(this->getMonth()) + "/" + std::to_string(this->getYear());
    if(this->dateType==WithHours)
        {s = s+ " " + addZero(this->getHour()) + ":" + addZero(this->getMinute());}
    return s;
}



bool Date::isLessThan(Date* date){
    if (this->getYear() < date->getYear())
        {return true;}
    if (this->getYear() == date->getYear()
            && this->getMonth() < date->getMonth())
        {return true;}
    if (this->getYear() == date->getYear()
            && this->getMonth() == date->getMonth()
            && this->getDay() < date->getDay())
        {return true;}
    if (this->getYear() == date->getYear()
            && this->getMonth() == date->getMonth()
            && this->getDay() == date->getDay())
        {return true;}
    return false;
}

bool Date::isBetween(Date* firstDate, Date* secondDate){
    if (firstDate->isLessThan(this) && this->isLessThan(secondDate))
        return true;
    else
        return false;
}

