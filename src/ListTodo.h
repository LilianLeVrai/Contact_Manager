#ifndef LISTTODO_H
#define LISTTODO_H

#include <list>
#include <Todo.h>

class ListTodo
{
    private:
        std::list<Todo> listTodo;

    public:
        ListTodo();
        ~ListTodo();

        std::list<Todo> getListTodo() const;
        void setListTodo(const std::list<Todo> &);

        void addTodo(const Todo &);
        void removeTodoById(const int);
        Todo getTodoById(const int) const;
        int getSize() const;

        std::string toString() const;
};

#endif // LISTTODO_H
