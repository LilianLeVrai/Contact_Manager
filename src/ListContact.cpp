
/**
 * @file ListContact.cpp
 * @brief Fichier cpp de la classe ListContact
 */

#include "ListContact.h"

#include <iostream>
#include <list>
#include <string>
#include <cctype>

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

Contact* ListContact::getContactByIndex(const int index) const{
    auto it=this->listContact.begin();
    for(int i=0; i<index; i++)
        it++;
    return *it;
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


//fonctions et méthodes pour les tris
/**
 * @brief fonction comparant 2 noms de contacts.
 * @param pointeur sur un objet Contact
 * @param pointeur sur un objet Contact
 * @return true si le nom du premier contact est alphabétiquement inférieur au second, \n sinon false.
 * @details comparateur utiliser dans la méthode 'sortByAlphabet()' de la classe ListContact.
 */
bool compareAlphabet(const Contact*  element1, const Contact*  element2)
    {
    unsigned int i=0;
    while (i < element1->getLastName().length() && i < element2->getLastName().length())
        {
        if (tolower(element1->getLastName()[i]) < tolower(element2->getLastName()[i])) return true;
        else if (tolower(element1->getLastName()[i]) > tolower(element2->getLastName()[i])) return false;
        ++i;
        }
    return(element1->getLastName().length() < element2->getLastName().length());
    }
void ListContact::sortByAlphabet(){this->listContact.sort(compareAlphabet);}
/**
 * @brief fonction comparant 2 noms de contacts.
 * @param pointeur sur un objet Contact
 * @param pointeur sur un objet Contact
 * @return true si le nom du premier contact est alphabétiquement supérieur au second, \n sinon false.
 * @details comparateur utiliser dans la méthode 'sortByReverseAlphabet()' de la classe ListContact.
 */
bool compareReverseAlphabet(const Contact*  element1, const Contact*  element2)
    {
    unsigned int i=0;
    while (i < element1->getLastName().length() && i < element2->getLastName().length())
        {
        if (tolower(element1->getLastName()[i]) > tolower(element2->getLastName()[i])) return true;
        else if (tolower(element1->getLastName()[i]) < tolower(element2->getLastName()[i])) return false;
        ++i;
        }
    return(element1->getLastName().length() > element2->getLastName().length());
    }
void ListContact::sortByReverseAlphabet(){listContact.sort(compareReverseAlphabet);}
/**
 * @brief fonction comparant 2 dates de création de contacts.
 * @param pointeur sur un objet Contact
 * @param pointeur sur un objet Contact
 * @return true si la première date est inférieur à la seconde, sinon false.
 * @details comparateur utiliser dans la méthode 'sortByCreateDate()' de la classe ListContact.
 */
bool compareDate(const Contact* element1, const Contact* element2){
    if (element1->getDateCreation()->getYear() < element2->getDateCreation()->getYear())
        {return true;}
    if (element1->getDateCreation()->getYear() == element2->getDateCreation()->getYear()
            && element1->getDateCreation()->getMonth() < element2->getDateCreation()->getMonth())
        {return true;}
    if (element1->getDateCreation()->getYear() == element2->getDateCreation()->getYear()
            && element1->getDateCreation()->getMonth() == element2->getDateCreation()->getMonth()
            && element1->getDateCreation()->getDay() < element2->getDateCreation()->getDay())
        {return true;}
    if (element1->getDateCreation()->getYear() == element2->getDateCreation()->getYear()
            && element1->getDateCreation()->getMonth() == element2->getDateCreation()->getMonth()
            && element1->getDateCreation()->getDay() == element2->getDateCreation()->getDay()
            && element1->getDateCreation()->getHour() < element2->getDateCreation()->getHour())
        {return true;}
    if (element1->getDateCreation()->getYear() == element2->getDateCreation()->getYear()
            && element1->getDateCreation()->getMonth() == element2->getDateCreation()->getMonth()
            && element1->getDateCreation()->getDay() == element2->getDateCreation()->getDay()
            && element1->getDateCreation()->getHour() == element2->getDateCreation()->getHour()
            && element1->getDateCreation()->getMinute() < element2->getDateCreation()->getMinute())
        {return true;}
    return false;
    }
void ListContact::sortByCreateDate(){this->listContact.sort(compareDate);}





std::string ListContact::toString() const{
    std::string s;
    auto it=this->listContact.begin();
    while ((it != this->listContact.end())) {
        s = s + (*it)->toString() +"\n";
        ++it;
    }
    return s;
}
