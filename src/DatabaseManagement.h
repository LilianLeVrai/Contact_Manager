#ifndef DATABASEMANAGEMENT_H
#define DATABASEMANAGEMENT_H


#include <QSqlDatabase>


class DatabaseManagement
{
    private:
        QSqlDatabase database;

    public:
        DatabaseManagement();

        QSqlDatabase * getDatabase();

        void initDataTest();

};

#endif // DATABASEMANAGEMENT_H
