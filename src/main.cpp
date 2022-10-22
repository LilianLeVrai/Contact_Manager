#include <iostream>
#include <Date.h>
#include <Todo.h>
#include <ListTodo.h>
#include <QString>

using namespace std;

int main()
{
    Todo t1("contenuuuu");
    t1.setId(4);
    Todo t2("contenuaaaa");
    t2.setId(2);
    Todo t3("contenu");
    t3.setId(3);

    ListTodo l;
    l.addTodo(t1);
    l.addTodo(t2);
    l.addTodo(t3);



    cout << l.toString() << endl;


return 0;
}
