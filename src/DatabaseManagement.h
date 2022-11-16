#ifndef DATABASEMANAGEMENT_H
#define DATABASEMANAGEMENT_H

/**
 * @file DatabaseManagement.h
 * @brief Fichier header de la classe DatabaseManagement
 */


#include <QSqlDatabase>

/**
 * @class DatabaseManagement
 * @brief classe représentant le gestionnaire de la BDD
 * @details La classe permet de gérer la BDD (connexion, insertion de données tests, ...).
 */
class DatabaseManagement
{
    private:
        QSqlDatabase database;/**< base de données */

    public:
        /**
         * @brief Constructeur sans paramètre qui fait la connexion à la base de données, et l'initialise.
         */
        DatabaseManagement();

        /**
         * @brief Permet d'obtenir la base de données.
         * @return pointeur vers objet QSqlDatabase
         */
        QSqlDatabase * getDatabase();

        /**
         * @brief Permet d'initialiser la BDD avec des données de test.
         * @details Les requêtes SQL (INSERT ...) sont contenus dans le fichier 'dataTest.sql' du dossier 'data'
         */
        void initDataTest();

};

#endif // DATABASEMANAGEMENT_H
