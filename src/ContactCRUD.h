#ifndef CONTACTCRUD_H
#define CONTACTCRUD_H

/**
 * @file ContactCRUD.h
 * @brief Fichier header de la classe ContactCRUD
 */


#include "ListContact.h"

#include <QSqlDatabase>
#include <QString>

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
         * @param pointeur vers un objet QSqlDatabase
         * @details Le paramêtre doit être la base de données ouverte par la classe DatabaseManagement
         */
        ContactCRUD(QSqlDatabase *);

        /**
         * @brief Permet de remplir une liste de contact avec tous les contacts contenus dans la BDD en attribut.
         * @param pointeur vers un objet ListContact
         * @details
         * Aucune liste n'est retourné, c'est la liste de contact passée en paramêtre qui est remplie. \n
         * La méthode fait une requête à la BDD.
         */
        void getAllContacts(ListContact *);

        /**
         * @brief Permet de supprimer un contact de la BDD en fonction de son identifiant.
         * @param entier
         * @details La méthode fait une requête à la BDD.
         */
        void deleteContactBDD(const int & id);

        /**
         * @brief Permet d'ajouter un contact à la BDD.
         * @param QString représentant le nom
         * @param QString représentant le prénom
         * @param QString représentant l'entreprise
         * @param QString représentant le mail
         * @param QString représentant le téléphone
         * @param QString représentant le lien vers l'image
         * @details La méthode fait une requête à la BDD.
         */
        void addContactBDD(QString, QString, QString, QString, QString, QString);

        /**
         * @brief Permet de remplir une liste de contact avec les contacts contenus dans la BDD respectant les filtres de recherches.
         * @param pointeur vers un objet ListContact
         * @param QString, dans notre programme c'est le contenu de la barre de recherche qui est récupéré
         * @param entier, dans notre programme c'est l'index courant du sélecteur de filtres
         * @param pointeur vers un objet Date, dans notre programme c'est la date de début des filtres
         * @param pointeur vers un objet Date, dans notre programme c'est la date de fin des filtres
         * @details
         * Aucune liste n'est retourné, c'est la liste de contact passée en paramêtre qui est remplie. \n
         * Pour filtrer, la méthode fait une requête à la BDD, et applique des méthodes de la classe date.
         */
        void searchByFilters(ListContact *, QString, int, Date *, Date *);
};

#endif // CONTACTCRUD_H
