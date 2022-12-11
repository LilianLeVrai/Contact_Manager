#ifndef INTERACTION_H
#define INTERACTION_H

/**
 * @file Interaction.h
 * @brief Fichier header de la classe Interaction
 */


#include "Date.h"
#include "ListTodo.h"

/**
 * @class Interaction
 * @brief classe représentant une interaction
 */
class Interaction
{  
    private:
        int id; /**< identifiant */
        std::string content; /**< contenu */
        Date* date; /**< date au format à définir */
        ListTodo* listTodo; /**< liste de todo */

    public:
        /**
         * @brief Constructeur sans paramètre.
         * @details
         * Initialise l'attribut 'id' à NULL \n
         * Initialise l'attribut 'dateCreation' avec le constructeur par défaut de l'objet Date \n
         * Initialise l'attribut 'listTodo' à nullptr
         */
        Interaction();
        /**
         * @brief Constructeur avec le contenu en paramètre.
         * @details
         * Initialise l'attribut 'id' à NULL \n
         * Initialise l'attribut 'dateCreation' avec le constructeur par défaut de l'objet Date \n
         * Initialise l'attribut 'listTodo' à nullptr
         */
        Interaction(const std::string & content);
        /**
         * @brief Constructeur avec la liste de tag 'todo' en paramètre.
         * @details
         * Initialise l'attribut 'id' à NULL \n
         * Initialise l'attribut 'dateCreation' avec le constructeur par défaut de l'objet Date \n
         */
        Interaction(ListTodo* const listTodo);
        /**
         * @brief Constructeur avec le contenu et la liste de tag 'todo' en paramètre.
         * @details
         * Initialise l'attribut 'id' à NULL \n
         * Initialise l'attribut 'dateCreation' avec le constructeur par défaut de l'objet Date \n
         */
        Interaction(const std::string & content, ListTodo* const listTodo);
        /**
         * @brief Constructeur avec tous les attributs en paramètres.
         */
        Interaction(const int id, const std::string & content, Date* const date, ListTodo* const listTodo);
        ~Interaction();

        /**
         * @brief Permet d'obtenir le nombre représentant l'identifiant dans l'objet.
         * @return Entier
         */
        int getId() const;
        /**
         * @brief Permet d'obtenir le texte représentant le contenu dans l'objet.
         * @return std::string
         */
        std::string getContent() const;
        /**
         * @brief Permet d'obtenir la date représentant la date dans l'objet.
         * @return pointeur vers objet Date
         */
        Date* getDate() const;
        /**
         * @brief Permet d'obtenir la liste de tag 'todo' de l'objet.
         * @return pointeur vers objet ListTodo
         */
        ListTodo* getListTodo() const;
        /**
         * @brief Permet de définir la valeur de l'attribut représentant l'identifiant.
         * @param Le paramètre doit être un entier
         */
        void setId(const int);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant le contenu.
         * @param Le paramètre doit être un string
         */
        void setContent(const std::string &);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant la date.
         * @param Le paramètre doit être un pointeur vers un objet Date
         */
        void setDate(Date* const);
        /**
         * @brief Permet de définir l'attribut de la liste de tag 'todo'.
         * @param Le paramètre doit être un pointeur vers un objet ListTodo
         */
        void setListTodo(ListTodo* const);

        /**
         * @brief Permet d'obtenir une chaine de caractères avec les informations de l'objet
         * @return std::string sous la forme 'content\\nlistTodo.toSring()'
         */
        std::string toString() const;
};

#endif // INTERACTION_H
