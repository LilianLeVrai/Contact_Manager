#ifndef INTERACTION_H
#define INTERACTION_H

/**
 * @file Interaction.h
 * @brief Fichier header de la classe Interaction
 */


#include "Date.h"
#include "ListTodo.h"


class Interaction
{  
    private:
        int id;
        std::string content;
        Date* date;
        ListTodo* listTodo;

    public:
        Interaction();
        Interaction(const std::string & content);
        Interaction(ListTodo* const listTodo);
        Interaction(const std::string & content, ListTodo* const listTodo);
        Interaction(const int id, const std::string & content, Date* const date, ListTodo* const listTodo);
        ~Interaction();

        int getId() const;
        std::string getContent() const;
        Date* getDate() const;
        ListTodo* getListTodo() const;
        void setId(const int);
        void setContent(const std::string &);
        void setDate(Date* const);
        void setListTodo(ListTodo* const);

        std::string toString() const;
};

#endif // INTERACTION_H
