#ifndef CONTACTCRUD_H
#define CONTACTCRUD_H

/**
 * @file ContactCRUD.h
 * @brief Fichier header de la classe ContactCRUD
 */


#include "ListContact.h"

#include <QSqlDatabase>

/**
 * @class ContactCRUD
 * @brief classe représentant le gestionnaire de la table Contact de la BDD
 * @details
 * La classe permet de faire les requètes sur les contact à la BDD. \n
 * 'CRUD' pour Create, Read, Update, Delete.
 */
class ContactCRUD
{
    private:
        QSqlDatabase * database;/**< base de données */

    public:
        /**
         * @brief Constructeur.
         * @param Le paramètre doit être un pointeur vers un objet QSqlDatabase
         * @details Le paramêtre doit être la base de données ouverte par la classe DatabaseManagement
         */
        ContactCRUD(QSqlDatabase *);

        /**
         * @brief Permet de remplir une liste de contact avec tous les contacts contenus dans la BDD en attribut.
         * @param Le paramètre doit être un pointeur vers un objet ListContact
         * @details
         * Aucune liste n'est retourné, c'est la liste de contact passée en paramêtre qui est remplie. \n
         * La méthode fais une requête à la BDD.
         */
        void getAllContacts(ListContact *);

        void deleteContactBDD(const int & id);

};

#endif // CONTACTCRUD_H
