#include "ContactCRUD.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <Contact.h>


ContactCRUD::ContactCRUD(QSqlDatabase * database){
    this->database=database;
}


void ContactCRUD::getAllContacts(ListContact * listContact){
    qDebug() << "test\n";
    QSqlQuery query;
    if(!query.exec("select * from Contact;"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        listContact->removeAllContacts();
        while(query.next())
            {

            listContact->addContact(new Contact(query.value(2).toString().toStdString(),
                                                query.value(3).toString().toStdString(),
                                                query.value(4).toString().toStdString(),
                                                query.value(5).toString().toStdString(),
                                                query.value(6).toString().toStdString(),
                                                query.value(7).toString().toStdString()));
            }
        }
}
