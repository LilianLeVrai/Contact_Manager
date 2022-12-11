/**
 * @file Interaction.cpp
 * @brief Fichier cpp de la classe Interaction
 */

#include "Interaction.h"

//debut constructeurs/destructeurs
Interaction::Interaction(){
    this->id=NULL;
    this->content="";
    this->date=new Date;
    this->listTodo=new ListTodo;
}

Interaction::Interaction(const std::string & content){
    this->id=NULL;
    this->content=content;
    this->date=new Date;
    this->listTodo=new ListTodo;
}

Interaction::Interaction(ListTodo* const listTodo){
    this->id=NULL;
    this->content="";
    this->date=new Date;
    this->listTodo=listTodo;
}

Interaction::Interaction(const std::string & content,ListTodo* const listTodo){
    this->id=NULL;
    this->content=content;
    this->date=new Date;
    this->listTodo=listTodo;
}

Interaction::Interaction(const int id, const std::string & content, Date* const date, ListTodo* const listTodo){
    this->id=id;
    this->content=content;
    this->date=date;
    this->listTodo=listTodo;
}

Interaction::~Interaction(){
    delete(this->date);
}
//fin constructeurs/destructeurs


//debut accesseurs basiques
int Interaction::getId() const{
    return this->id;
}
std::string Interaction::getContent() const{
    return this->content;
}
Date* Interaction::getDate() const{
    return this->date;
}
ListTodo* Interaction::getListTodo() const{
    return this->listTodo;
}

void Interaction::setId(const int val){
    this->id=val;
}
void Interaction::setContent(const std::string & val){
    this->content=val;
}
void Interaction::setDate(Date* const val){
    this->date=val;
}
void Interaction::setListTodo(ListTodo* const val){
    this->listTodo=val;
}
//fin accesseurs basiques


std::string Interaction::toString() const{
    std::string s;
    s = this->getContent() + " \n" + (*this->getListTodo()).toString();
    return s;
}
