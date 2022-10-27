/**
 * @file ListInteraction.cpp
 * @brief Fichier cpp de la classe ListInteraction
 */

#include "ListInteraction.h"

//debut constructeurs/destructeurs
ListInteraction::ListInteraction(){
}

ListInteraction::~ListInteraction(){
    this->listInteraction.clear();
}
//fin constructeurs/destructeurs

//debut accesseurs basiques
std::list<Interaction*> ListInteraction::getListInteraction() const{
    return this->listInteraction;
}

void ListInteraction::setListInteraction(const std::list<Interaction*> & list){
    this->listInteraction=list;
}
//fin accesseurs basiques


void ListInteraction::addInteraction(Interaction* const interaction){
    this->listInteraction.push_back(interaction);
}

void ListInteraction::removeInteractionById(const int id){
    auto it=this->listInteraction.begin();
    bool found=false;
    while ((it != this->listInteraction.end()) && (found == false)) {
        if ((*it)->getId() == id)
            {
            found=true;
            it= this->listInteraction.erase(it);
            }
        else
            ++it;
    }
}

Interaction* ListInteraction::getInteractionById(const int id) const{
    auto it=this->listInteraction.begin();
    while ((it != this->listInteraction.end())) {
        if ((*it)->getId() == id)
            {
            return *it;
            }
        else
            ++it;
    }
    return nullptr;
}

int ListInteraction::getSize() const{
    return this->listInteraction.size();
}

std::string ListInteraction::toString() const{
    std::string s;
    auto it=this->listInteraction.begin();
    while ((it != this->listInteraction.end())) {
        s = s + (*it)->toString() +"\n";
        ++it;
    }
    return s;
}
