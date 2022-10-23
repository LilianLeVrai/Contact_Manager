#include <iostream>
#include <Date.h>
#include <Todo.h>
#include <ListTodo.h>
#include <QString>
#include <Interaction.h>

using namespace std;

int main()
{
    //tests Date
    Date dNow;
    Date d1(01,01,2001);
    cout << "La date d'aujourd'hui est : " << dNow.toString() << endl;
    cout << "On a la date : " << d1.toString() << endl;
    //d1.setYear(2003);
    cout << "J'ai modifié la dernière date : " << d1.toString();

    //test Todo
    Todo t1("rappel 1");
    Todo t2("rappel 2",&d1);
    cout << "\n\nJ'ai un todo sans date : \n" << t1.toString() << endl;
    cout << "et un todo avec date : \n" << t2.toString() << endl;

    t2.setContent("rappel modifié");
    (*t2.getDate()).setYear(2004);
    cout << "J'ai modifié le second todo : \n" << t2.toString() << endl;
    cout << "et la date utilisé pour le todo a elle aussi été modifié (étant un pointeur dans todo) : " << d1.toString() << endl;

    return 0;
}
