/**
 * @file ListTodo.cpp
 * @brief Fichier cpp de la classe ListTodo
 */

#include "ListTodo.h"

//debut constructeurs/destructeurs
ListTodo::ListTodo(){
}

ListTodo::~ListTodo(){
    this->listTodo.clear();
}
//fin constructeurs/destructeurs

//debut accesseurs basiques
std::list<Todo*> ListTodo::getListTodo() const{
    return this->listTodo;
}

void ListTodo::setListTodo(const std::list<Todo*> & list){
    this->listTodo=list;
}
//fin accesseurs basiques


void ListTodo::addTodo(Todo* const todo){
    this->listTodo.push_back(todo);
}

void ListTodo::removeTodoById(const int id){
    auto it=this->listTodo.begin();
    bool found=false;
    while ((it != this->listTodo.end()) && (found == false)) {
        if ((*it)->getId() == id)
            {
            found=true;
            it= this->listTodo.erase(it);
            }
        else
            ++it;
    }
}

void ListTodo::removeAllTodos(){
    auto it=this->listTodo.begin();
    while ((it != this->listTodo.end())){
            it= this->listTodo.erase(it);
    }
}

Todo* ListTodo::getTodoById(const int id) const{
    auto it=this->listTodo.begin();
    while ((it != this->listTodo.end())) {
        if ((*it)->getId() == id)
            {
            return *it;
            }
        else
            ++it;
    }
    return nullptr;
}

int ListTodo::getSize() const{
    return this->listTodo.size();
}

std::string ListTodo::toString() const{
    std::string s;
    auto it=this->listTodo.begin();
    while ((it != this->listTodo.end())) {
        s = s + (*it)->toString() +"\n";
        ++it;
    }
    return s;
}

Todo* ListTodo::getTodoByIndex(const int index) const{
    auto it=this->listTodo.begin();
    for(int i=0; i<index; i++)
        it++;
    return *it;
}
