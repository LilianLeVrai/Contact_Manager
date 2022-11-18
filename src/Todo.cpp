/**
 * @file Todo.cpp
 * @brief Fichier cpp de la classe Todo
 */

#include "Todo.h"

//debut constructeurs/destructeurs
Todo::Todo(){
    this->id=NULL;
    this->content="";
    this->date=nullptr;
    this->boolTagDate=false;
}

Todo::Todo(const std::string & content){
    this->id=NULL;
    this->content=content;
    this->date=nullptr;
    this->boolTagDate=false;
}

Todo::Todo(const std::string & content, Date* const date){
    this->id=NULL;
    this->content=content;
    this->date=date;
    this->boolTagDate=true;
}

Todo::Todo(const int id, const std::string & content, Date* const date, const bool boolTagDate){
    this->id=id;
    this->content=content;
    this->date=date;
    this->boolTagDate=boolTagDate;
}

Todo::~Todo(){
}
//fin constructeurs/destructeurs


//debut accesseurs basiques
int Todo::getId() const{
    return this->id;
}
std::string Todo::getContent() const{
    return this->content;
}
Date* Todo::getDate() const{
    return this->date;
}
bool Todo::getBoolTagDate() const{
    return this->boolTagDate;
}

void Todo::setId(const int val){
    this->id=val;
}
void Todo::setContent(const std::string & val){
    this->content=val;
}
void Todo::setDate(Date* const val){
    this->date=val;
    if(val==nullptr)
        this->boolTagDate=false;
    else
        this->boolTagDate=true;

}
void Todo::setBoolTagDate(bool val){
    this->boolTagDate=val;
}
//fin accesseurs basiques


std::string Todo::toString() const{
    std::string s;
    if(this->getBoolTagDate())
        s = "@todo " + this->getContent() + " @date " + (*this->getDate()).toString();
    else
        s = "@todo " + this->getContent();
    return s;
}
