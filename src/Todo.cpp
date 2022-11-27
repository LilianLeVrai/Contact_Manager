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
}

Todo::Todo(const std::string & content){
    this->id=NULL;
    this->content=content;
    this->date=nullptr;
}

Todo::Todo(const std::string & content, Date* const date){
    this->id=NULL;
    this->content=content;
    this->date=date;
}

Todo::Todo(const int id, const std::string & content, Date* const date){
    this->id=id;
    this->content=content;
    this->date=date;
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

void Todo::setId(const int val){
    this->id=val;
}
void Todo::setContent(const std::string & val){
    this->content=val;
}
void Todo::setDate(Date* const val){
    this->date=val;
}
//fin accesseurs basiques


std::string Todo::toString() const{
    std::string s;
    if(this->date!=nullptr)
        s = "@todo " + this->getContent() + " @date " + (*this->getDate()).toString();
    else
        s = "@todo " + this->getContent();
    return s;
}
