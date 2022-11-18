/**
 * @file ContactCRUD.cpp
 * @brief Fichier cpp de la classe ContactCRUD
 */


#include "ContactCRUD.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "Contact.h"
#include "ListContact.h"


ContactCRUD::ContactCRUD(QSqlDatabase * database){
    this->database=database;
}


void ContactCRUD::getAllContacts(ListContact * listContact){
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

void ContactCRUD::deleteContactBDD(const int & val){
    QSqlQuery query;
    if(!query.exec("delete from Contact where idContact="+QString::number(val)+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}



void ContactCRUD::searchByFilters(ListContact * listContact, QString searchBarContent,
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
