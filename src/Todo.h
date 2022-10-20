#ifndef TODO_H
#define TODO_H

#include <string>
#include <Date.h>

class Todo
{
    private:
        std::string content;
        Date date;
        bool boolTagDate;


    public:
        Todo();
        Todo(const std::string & content);
        Todo(const std::string & content,Date date);
        Todo(const std::string & content,Date date,bool boolTagDate);
        ~Todo();

        std::string getContent() const;
        Date getDate() const;
        bool getBoolTagDate() const;
        void setContent(const std::string &);
        void setDate(const Date);
        void setBoolTagDate(const bool);

        friend std::ostream& operator<<(std::ostream &, const Todo&);
};

#endif // TODO_H
