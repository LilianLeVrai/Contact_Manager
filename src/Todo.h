#ifndef TODO_H
#define TODO_H

#include <string>
#include <Date.h>

class Todo
{
    private:
        int id;
        std::string content;
        Date* date;
        bool boolTagDate;


    public:
        Todo();
        Todo(const std::string & content);
        Todo(const std::string & content, Date* const date);
        Todo(const int id, const std::string & content, Date* const date, const bool boolTagDate);
        ~Todo();

        int getId() const;
        std::string getContent() const;
        Date* getDate() const;
        bool getBoolTagDate() const;
        void setId(const int);
        void setContent(const std::string &);
        void setDate(Date* const);
        void setBoolTagDate(const bool);

        std::string toString() const;
};

#endif // TODO_H
