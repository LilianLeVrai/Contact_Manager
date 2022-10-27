/**
 * @file main
 */



#include <iostream>
#include <Date.h>
#include <Todo.h>
#include <ListTodo.h>
#include <QString>
#include <Interaction.h>
#include <ListInteraction.h>
#include <Contact.h>
#include <ListContact.h>

using namespace std;

int main()
{
    //tests Date
    Date dNow;
    Date d1(01,01,2001);
    cout << "La date d'aujourd'hui est : " << dNow.toString() << endl;
    cout << "On a la date : " << d1.toString() << endl;
    d1.setYear(2003);
    cout << "J'ai modifie la derniere date : " << d1.toString();

    cout << "\n-----------------------------------------------------------" << endl;

    //test Todo
    Todo t1("rappel 1");
    t1.setId(1);
    Todo t2("rappel 2",&d1);
    t2.setId(2);
    cout << "\n\nJ'ai un todo sans date : \n" << t1.toString() << endl;
    cout << "et un todo avec date : \n" << t2.toString() << endl;

    t2.setContent("rappel modifie");
    (*t2.getDate()).setYear(2004);
    cout << "J'ai modifie le second todo : \n" << t2.toString() << endl;
    cout << "et la date utilise pour le todo a elle aussi ete modifie (etant un pointeur dans todo) : " << d1.toString() << endl;

    cout << "\n-----------------------------------------------------------" << endl;

    //test ListTodo
    ListTodo lTodo;
    lTodo.addTodo(&t1);
    lTodo.addTodo(&t2);
    cout << "\nJ'ai cree une liste avec les 2 todo : \n" << lTodo.toString() << endl;
    Date d2(02,02,2002);
    (*lTodo.getTodoById(1)).setDate(&d2);
    cout << "\nJ'ai modifie le premier todo depuis la liste : \n" << lTodo.toString() << endl;

    cout << "\n-----------------------------------------------------------" << endl;

    //test Interaction
    Interaction i1("contenu de l'interaction 1", &lTodo);
    i1.setId(1);
    cout << "J'ai cree une interaction avec la precedente ListTodo :\n" << i1.toString() << endl;

    Interaction i2("contenu de l'interaction 2");
    i2.setId(2);
    (*i2.getListTodo()).addTodo(new Todo("blabla"));
    cout << "J'ai cree une interaction sans specifie une ListTodo, a laquelle j'ai ajoute un Todo :\n" << i2.toString() << endl;

    Interaction i3("contenu de l'interaction 3");

    cout << "\n-----------------------------------------------------------" << endl;

    //test ListInteraction
    ListInteraction lInteraction;
    lInteraction.addInteraction(&i1);
    lInteraction.addInteraction(&i2);
    lInteraction.addInteraction(&i3);
    cout << "\nJ'ai cree une ListInteraction avec les 2 precedentes et une 3eme autre :\n\n" << lInteraction.toString() << endl;

    cout << "\n-----------------------------------------------------------" << endl;

    //test Contact
    Contact c1("Manzano","Lilian","UB","lilian@mail.fr","0123456789","urlPhoto");
    cout << "\nJ'ai cree un contact :\n" << c1.toString() << endl;
    (*c1.getListInteraction()).addInteraction(new Interaction("rendez vous"));
    cout << "J'ai ajoute une interaction au contact :\n" << c1.toString() << endl;

    Contact c2("Brandon","Pere","UB","brandon@mail.fr","9876543210","urlPhotoBis",&lInteraction);
    cout << "J'ai cree un second contact avec la ListInteraction precedente :\n" << c2.toString() << endl;

    cout << "\n-----------------------------------------------------------" << endl;

    //test ListContact
    ListContact listContact;
    listContact.addContact(&c1);
    listContact.addContact(&c2);
    cout << "J'ai cree une ListContact avec les 2 Contact precedents :\n" << listContact.toString() << endl;



    return 0;

}
