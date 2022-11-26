/**
 * @file DatabaseCRUD.cpp
 * @brief Fichier cpp de la classe DatabaseCRUD
 */


#include "DatabaseCRUD.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "Contact.h"
#include "ListContact.h"


DatabaseCRUD::DatabaseCRUD(QSqlDatabase * database){
    this->database=database;
}


void DatabaseCRUD::getAllContacts(ListContact * listContact){
    QSqlQuery query;
    if(!query.exec("select * from Contact;"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        listContact->removeAllContacts();
        while(query.next())
            {
            listContact->addContact(new Contact(query.value(0).toInt(),
                                                query.value(1).toString().toStdString(),
                                                query.value(2).toString().toStdString(),
                                                query.value(3).toString().toStdString(),
                                                query.value(4).toString().toStdString(),
                                                query.value(5).toString().toStdString(),
                                                query.value(6).toString().toStdString(),
                                                new Date(query.value(7).toString().toStdString())));
            }
        }
}

void DatabaseCRUD::deleteContactBDD(const int & val){
    QSqlQuery query;
    if(!query.exec("delete from Contact where idContact="+QString::number(val)+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}



void DatabaseCRUD::searchByFilters(ListContact * listContact, QString searchBarContent,
                                  int indexFiltersCombobox, Date * filterFirstDate,Date * filterSecondDate){

//-------------------------
//préparation de la requête
//-------------------------
    searchBarContent=searchBarContent.simplified();
    QString s="select * from Contact where";

    if(indexFiltersCombobox==0)
        {
        s=s+" lastName LIKE '%"+searchBarContent+"%'"
            +" OR firstName LIKE '%"+searchBarContent+"%'"
            +" OR company LIKE '%"+searchBarContent+"%'"
            +" OR mail LIKE '%"+searchBarContent+"%'"
            +" OR phone LIKE '%"+searchBarContent+"%'"
            +" OR dateCreation LIKE '%"+searchBarContent+"%'";
        }
    if(indexFiltersCombobox==1)
        s=s+" lastName LIKE '%"+searchBarContent+"%'";
    if(indexFiltersCombobox==2)
        s=s+" firstName LIKE '%"+searchBarContent+"%'";
    if(indexFiltersCombobox==3)
        s=s+" company LIKE '%"+searchBarContent+"%'";
    if(indexFiltersCombobox==4)
        s=s+" mail LIKE '%"+searchBarContent+"%'";
    if(indexFiltersCombobox==5)
        s=s+" phone LIKE '%"+searchBarContent+"%';";


//-------------------------
//execution de la requête
//-------------------------
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        listContact->removeAllContacts();
        ListContact listContactTemp;
        while(query.next())
            {
            listContactTemp.addContact(new Contact(query.value(0).toInt(),
                                                query.value(1).toString().toStdString(),
                                                query.value(2).toString().toStdString(),
                                                query.value(3).toString().toStdString(),
                                                query.value(4).toString().toStdString(),
                                                query.value(5).toString().toStdString(),
                                                query.value(6).toString().toStdString(),
                                                new Date(query.value(7).toString().toStdString())));
            }

        //filtrage par les dates faits avec les méthodes de la classe Date
            for(int i=0;i<listContactTemp.getSize();i++)
                {
                if(filterFirstDate==nullptr && filterSecondDate==nullptr)
                    listContact->addContact(listContactTemp.getContactByIndex(i));
                if(filterFirstDate!=nullptr && filterSecondDate!=nullptr && listContactTemp.getContactByIndex(i)->getDateCreation()->isBetween(filterFirstDate,filterSecondDate))
                   listContact->addContact(listContactTemp.getContactByIndex(i));
                if(filterFirstDate!=nullptr && filterSecondDate==nullptr && filterFirstDate->isLessThan(listContactTemp.getContactByIndex(i)->getDateCreation()))
                   listContact->addContact(listContactTemp.getContactByIndex(i));
                if(filterFirstDate==nullptr && filterSecondDate!=nullptr && listContactTemp.getContactByIndex(i)->getDateCreation()->isLessThan(filterSecondDate))
                   listContact->addContact(listContactTemp.getContactByIndex(i));
                }
        }
}



void DatabaseCRUD::addContactBDD(Contact * contact){
    QString s="insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ";
    s=s+"('"+contact->getLastName().c_str()+"', '"+contact->getFirstName().c_str()+"', '"
            +contact->getCompany().c_str()+"', '"+contact->getMail().c_str()+"', '"
            +contact->getPhone().c_str()+"', '"+contact->getPathPicture().c_str()+"', '"
            +contact->getDateCreation()->toString().c_str()+"');";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}


void DatabaseCRUD::modifyContactBDD(Contact * contact){
    QString s="update Contact set ";
    s=s+"lastName='"+contact->getLastName().c_str()+"', firstName='"+contact->getFirstName().c_str()
            +"', company='"+contact->getCompany().c_str()+"', mail='"+contact->getMail().c_str()
            +"', phone='"+contact->getPhone().c_str()+"', picture='"+contact->getPathPicture().c_str()
            +"' where idContact="+QString::number(contact->getId())+";";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}

void DatabaseCRUD::getInteractionByContact(ListInteraction * listInteraction, Contact * contact){
    QSqlQuery query;
    if(!query.exec("select * from Interaction where idContact="+QString::number(contact->getId())+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        listInteraction->removeAllInteractions();
        while(query.next())
            {
            listInteraction->addInteraction(new Interaction(query.value(0).toInt(),
                                                query.value(1).toString().toStdString(),
                                                new Date(query.value(7).toString().toStdString()),
                                                new ListTodo()));
            }
        }
}

void DatabaseCRUD::getTodoByInteraction(ListTodo * listTodo, Interaction * interaction){
    QSqlQuery query;
    if(!query.exec("select * from Todo where idInteraction="+QString::number(interaction->getId())+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        listTodo->removeAllTodos();
        while(query.next())
            {
            listTodo->addTodo(new Todo(query.value(0).toInt(),
                                    query.value(1).toString().toStdString(),
                                    new Date(query.value(7).toString().toStdString()),
                                    true));
            }
        }
}



void DatabaseCRUD::deleteInteractionBDD(const int & id){
    QSqlQuery query;
    if(!query.exec("delete from Interaction where idInteraction="+QString::number(id)+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}

void DatabaseCRUD::addInteractionBDD(Interaction * interaction, Contact * contact){
    QString s="insert into Interaction(content, dateCreation, idContact) values ";
    s=s+"('"+interaction->getContent().c_str()+"', '"
            +interaction->getDate()->toString().c_str()+"', "
            +QString::number(contact->getId())+");";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}


void DatabaseCRUD::modifyInteractionBDD(Interaction * interaction){
    QString s="update Interaction set ";
    s=s+"content='"+interaction->getContent().c_str()
            +"' where idInteraction="+QString::number(interaction->getId())+";";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}


void DatabaseCRUD::deleteTagBDD(const int & id){
    QSqlQuery query;
    if(!query.exec("delete from Todo where idTodo="+QString::number(id)+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}

void DatabaseCRUD::addTagBDD(Todo * todo, Interaction * interaction){
    QString s="insert into Todo(content, dateTodo, idInteraction) values ";
    s=s+"('"+interaction->getContent().c_str()+"', '"
            +interaction->getDate()->toString().c_str()+"', "
            +QString::number(todo->getId())+");";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}


void DatabaseCRUD::modifyTagBDD(Todo * todo){
    QString s="update Todo set ";
    s=s+"content='"+todo->getContent().c_str()+"', date='"+todo->getDate()->toString().c_str()+"'"
            +"' where idTodo="+QString::number(todo->getId())+";";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}






















//Fonction de test : Le delete on cascade ne fonctionne pas
void DatabaseCRUD::getAllInteractions(){
    QSqlQuery query;
    if(!query.exec("select * from Interaction;"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        while(query.next())
            {
            qDebug() << QString::number(query.value(0).toInt());
            qDebug() << query.value(1).toString().toStdString().c_str();
            }
        }
}
void DatabaseCRUD::getAllTodos(){
    QSqlQuery query;
    if(!query.exec("select * from Todo;"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        while(query.next())
            {
            qDebug() << QString::number(query.value(0).toInt());
            qDebug() << query.value(1).toString().toStdString().c_str();
            }
        }
}


