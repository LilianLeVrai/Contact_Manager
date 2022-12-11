#ifndef TODO_H
#define TODO_H

/**
 * @file Todo.h
 * @brief Fichier header de la classe Todo
 */


#include <string>
#include "Date.h"

/**
 * @class Todo
 * @brief classe représentant un tag 'todo'
 */
class Todo
{
    private:
        int id; /**< identifiant */
        std::string content; /**< contenu */
        Date* date; /**< date au format jj/mm/aaaa */

    public:
       /**
        * @brief Constructeur sans paramètre.
        * @details
        * Initialise l'attribut 'id' à NULL \n
        * Initialise l'attribut 'date' à nullptr \n
        */
        Todo();
        /**
         * @brief Constructeur avec le contenu en paramètre.
         * @details
         * Initialise l'attribut 'id' à NULL \n
         * Initialise l'attribut 'date' à nullptr \n
         */
        Todo(const std::string & content);
        /**
         * @brief Constructeur avec le contenu et la date en paramètres.
         * @details
         * Initialise l'attribut 'id' à NULL \n
         */
        Todo(const std::string & content, Date* const date);
        /**
         * @brief Constructeur avec tout les attributs en paramètres.
         */
        Todo(const int id, const std::string & content, Date* const date);
        ~Todo();

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
         * @brief Permet d'obtenir une chaine de caractères avec les informations de l'objet
         * @return std::string sous la forme '\@todo string', ou '\@todo string \@date date'
         */
        std::string toString() const;
};

#endif // TODO_H
