#ifndef CONTACTCRUD_H
#define CONTACTCRUD_H

#include <DatabaseManagement.h>
#include <ListContact.h>

#include <QSqlDatabase>

class ContactCRUD
{
    private:
        QSqlDatabase * database;

public:
    ContactCRUD(QSqlDatabase *);

    void getAllContacts(ListContact *);

};

#endif // CONTACTCRUD_H
