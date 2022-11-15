/**
 * @file ListContact.cpp
 * @brief Fichier cpp de la classe ListContact
 */

#include "ListContact.h"

//debut constructeurs/destructeurs
ListContact::ListContact(){
}

ListContact::~ListContact(){
    this->listContact.clear();
}
//fin constructeurs/destructeurs

//debut accesseurs basiques
std::list<Contact*> ListContact::getListContact() const{
    return this->listContact;
}

void ListContact::setListContact(const std::list<Contact*> & list){
    this->listContact=list;
}
//fin accesseurs basiques


void ListContact::addContact(Contact* const interaction){
    this->listContact.push_back(interaction);
}

void ListContact::removeContactById(const int id){
    auto it=this->listContact.begin();
    bool found=false;
    while ((it != this->listContact.end()) && (found == false)) {
        if ((*it)->getId() == id)
            {
            found=true;
            it= this->listContact.erase(it);
            }
        else
            ++it;
    }
}

Contact* ListContact::getContactById(const int id) const{
    auto it=this->listContact.begin();
    while ((it != this->listContact.end())) {
        if ((*it)->getId() == id)
            {
            return *it;
            }
        else
            ++it;
    }
    return nullptr;
}

int ListContact::getSize() const{
    return this->listContact.size();
}

void ListContact::removeAllContacts(){
    auto it=this->listContact.begin();
    while ((it != this->listContact.end())){
            it= this->listContact.erase(it);
    }
}


std::string ListContact::toString() const{
    std::string s;
    auto it=this->listContact.begin();
    while ((it != this->listContact.end())) {
        s = s + (*it)->toString() +"\n";
        ++it;
    }
    return s;
}
