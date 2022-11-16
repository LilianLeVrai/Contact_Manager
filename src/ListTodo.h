#ifndef LISTTODO_H
#define LISTTODO_H

/**
 * @file ListTodo.h
 * @brief Fichier header de la classe ListTodo
 */


#include <list>
#include "Todo.h"

/**
 * @class ListTodo
 * @brief classe représentant une liste de pointeurs vers des objets 'Todo'
 */
class ListTodo
{
    private:
        std::list<Todo*> listTodo; /**< liste de pointeurs sur des objets 'Todo' */

    public:
        ListTodo();
        ~ListTodo();

        /**
         * @brief Permet de récupérer l'attribut de liste.
         * @return std::list<Todo*>
         */
        std::list<Todo*> getListTodo() const;
        /**
         * @brief Permet de définir l'attribut de liste.
         * @param Le paramètre doit être un std::list<Todo*>
         */
        void setListTodo(const std::list<Todo*> &);

        /**
         * @brief Permet d'ajouter un todo à la liste.
         * @param Le paramètre doit être un pointeur sur un objet Todo
         */
        void addTodo(Todo* const);
        /**
         * @brief Permet d'enlever un todo de la liste en fonction de son identifiant.
         * @param Le paramètre doit être un entier représentant l'identifiant
         */
        void removeTodoById(const int);
        /**
         * @brief Permet de récupérer un todo de la liste en fonction de son identifiant.
         * @param Le paramètre doit être un entier représentant l'identifiant
         * @return pointeur vers objet Todo
         */
        Todo* getTodoById(const int) const;
        /**
         * @brief Permet de récupérer la taille de la liste.
         * @return entier
         */
        int getSize() const;

        /**
         * @brief Permet d'obtenir une chaine de caractères avec les informations de l'objet
         * @return std::string sous la forme 'todo.toString\\ntodo.toString\\ntodo.toString'
         *
         * @warning sujet à changement
         */
        std::string toString() const;
};

#endif // LISTTODO_H
