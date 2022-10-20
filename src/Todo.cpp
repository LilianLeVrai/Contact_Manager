#include "Todo.h"

//début constructeurs/destructeurs
Todo::Todo(){
    this->content="";

    this->boolTagDate=false;
}

Todo::Todo(const std::string & content){
    this->content=content;

    this->boolTagDate=false;
}

Todo::Todo(const std::string & content, Date date){
    this->content=content;
    this->date=date;
    this->boolTagDate=true;
}

Todo::Todo(const std::string & content, Date date, bool boolTagDate){
    this->content=content;
    this->date=date;
    this->boolTagDate=boolTagDate;
}

Todo::~Todo(){
}
//fin constructeurs/destructeurs


//début accesseurs basiques
std::string Todo::getContent() const{
    return this->content;
}
Date Todo::getDate() const{
    return this->date;
}
bool Todo::getBoolTagDate() const{
    return this->boolTagDate;
}

void Todo::setContent(const std::string & val){
    this->content=val;
}
void Todo::setDate(Date val){
    this->date=val;
}
void Todo::setBoolTagDate(bool val){
    this->boolTagDate=val;
}
//fin accesseurs basiques

//surcharge opérateur pour affichage console
std::ostream& operator<<(std::ostream& os, const Todo& todo){
    if(todo.getBoolTagDate())
        os << "@todo " << todo.getContent() << " @date " << todo.getDate();
    else
        os << "@todo " << todo.getContent();
    return os;
}








