/**
 * @file Contact.cpp
 * @brief Fichier cpp de la classe Contact
 */

#include "Contact.h"

//debut constructeurs/destructeurs
Contact::Contact(){
    this->id=NULL;
    this->dateCreation=new Date;
    this->listInteraction=new ListInteraction;
}

Contact::Contact(const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
          const std::string & phone, const std::string & pathPicture){
    this->id=NULL;
    this->lastName=lastName;
    this->firstName=firstName;
    this->company=company;
    this->mail=mail;
    this->phone=phone;
    this->pathPicture=pathPicture;
    this->dateCreation=new Date;
    this->listInteraction=new ListInteraction;
}

Contact::Contact(const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
          const std::string & phone, const std::string & pathPicture, ListInteraction* const listInteraction){
    this->id=NULL;
    this->lastName=lastName;
    this->firstName=firstName;
    this->company=company;
    this->mail=mail;
    this->phone=phone;
    this->pathPicture=pathPicture;
    this->dateCreation=new Date;
    this->listInteraction=listInteraction;
}

Contact::Contact(const int & id, const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
          const std::string & phone, const std::string & pathPicture, ListInteraction* const listInteraction){
    this->id=id;
    this->lastName=lastName;
    this->firstName=firstName;
    this->company=company;
    this->mail=mail;
    this->phone=phone;
    this->pathPicture=pathPicture;
    this->dateCreation=new Date;
    this->listInteraction=listInteraction;
}

Contact::Contact(const int & id, const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
          const std::string & phone, const std::string & pathPicture, Date* const dateCreation){
    this->id=id;
    this->lastName=lastName;
    this->firstName=firstName;
    this->company=company;
    this->mail=mail;
    this->phone=phone;
    this->pathPicture=pathPicture;
    this->dateCreation=dateCreation;
    this->listInteraction=nullptr;
}

Contact::~Contact(){
    delete(this->dateCreation);
}
//fin constructeurs/destructeurs

//debut accesseurs basiques
int  Contact::getId() const{
    return this->id;
}
std::string Contact::getLastName() const{
    return this->lastName;
}
std::string Contact::getFirstName() const{
    return this->firstName;
}
std::string Contact::getCompany() const{
    return this->company;
}
std::string Contact::getMail() const{
    return this->mail;
}
std::string Contact::getPhone() const{
    return this->phone;
}
std::string Contact::getPathPicture() const{
    return this->pathPicture;
}
Date* Contact::getDateCreation() const{
    return this->dateCreation;
}
ListInteraction* Contact::getListInteraction() const{
    return this->listInteraction;
}

void Contact::setId(const int & val){
    this->id=val;
}
void Contact::setLastName(const std::string & val){
    this->lastName=val;
}
void Contact::setFirstName(const std::string & val){
    this->firstName=val;
}
void Contact::setCompany(const std::string & val){
    this->company=val;
}
void Contact::setMail(const std::string & val){
    this->mail=val;
}
void Contact::setPhone(const std::string & val){
    this->phone=val;
}
void Contact::setPathPicture(const std::string & val){
    this->pathPicture=val;
}
void Contact::setDateCreation(Date* const val){
    this->dateCreation=val;
}
void Contact::setListInteraction(ListInteraction* const val){
    this->listInteraction=val;
}
//fin accesseurs basiques


std::string Contact::toString() const{
    std::string s;
    s = "Nom : " + this->lastName + "\nPrénom : " + this->firstName + "\nEntreprise : " + this->company
            + "\nMail : " + this->mail + "\nTéléphone : " + this->phone + "\nCrée le : " + (*this->dateCreation).toString();
    return s;
}

