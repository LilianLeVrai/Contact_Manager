/**
 * @file MainWindow.cpp
 * @brief Fichier cpp de la classe MainWindow
 */

#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>

#include "MainWindow.h"


MainWindow::MainWindow(DatabaseManagement * databaseManagement, DatabaseCRUD * databaseCRUD, QWidget *parent)
    : QMainWindow(parent)
    {
        this->databaseManagement=databaseManagement;
        this->databaseCRUD=databaseCRUD;
        //databaseCRUD->getAllContacts(&this->listContact);

        this->setWindowTitle("Gestionnaire de contact");
        this->resize(1600, 800);

        QMenu * optionsMenu=new QMenu("Options");
        this->optionExportJson=new QAction("Exporter les données en JSON");
        this->optionInitDataTest=new QAction("Initialiser les données de tests");
        optionsMenu->addAction(this->optionExportJson);
        optionsMenu->addAction(this->optionInitDataTest);
        this->menuBar()->addMenu(optionsMenu);

        this->mainWidget=new MainWidget(databaseCRUD);
        this->setCentralWidget(this->mainWidget);

        connect(this->optionExportJson, SIGNAL(triggered()), this, SLOT(createJSON()));
        connect(this->optionInitDataTest, SIGNAL(triggered()), this, SLOT(askInitDataTest()));
        connect(this, SIGNAL(emitUpdateContact()), this->mainWidget, SLOT(searchContacts()));

    }

MainWindow::~MainWindow(){}

void MainWindow::askInitDataTest(){
    this->yesNoDialogDataTest=new YesNoDialog("Attention", "Cela effacera toutes vos données pour les remplacer par les données tests.\n\nÊtes vous sûr ?");
    QObject::connect(this->yesNoDialogDataTest, SIGNAL(emitClose(bool)), this, SLOT(closeYesNoDialogDataTest(bool)));
    yesNoDialogDataTest->show();
}

void MainWindow::closeYesNoDialogDataTest(bool choice){
    if(choice)
        {
        this->databaseManagement->initDataTest();
        emit emitUpdateContact();
        }
}

void MainWindow::createJSON(){
    //databaseCRUD->getAllInteractions();
    //databaseCRUD->getAllTodos();

    databaseCRUD->getAllContacts(&this->listContact);

    QJsonArray mainArray;


    for(int i=0;i<this->listContact.getSize();i++){
        QJsonArray arrayInteraction;
        QJsonObject objectContact;
        objectContact.insert("idContact",std::to_string(this->listContact.getContactByIndex(i)->getId()).c_str());
        objectContact.insert("lastName",this->listContact.getContactByIndex(i)->getLastName().c_str());
        objectContact.insert("firstName",this->listContact.getContactByIndex(i)->getFirstName().c_str());
        objectContact.insert("company",this->listContact.getContactByIndex(i)->getCompany().c_str());
        objectContact.insert("mail",this->listContact.getContactByIndex(i)->getMail().c_str());
        objectContact.insert("phone",this->listContact.getContactByIndex(i)->getPhone().c_str());
        objectContact.insert("picture",this->listContact.getContactByIndex(i)->getPathPicture().c_str());
        objectContact.insert("dateCreation",this->listContact.getContactByIndex(i)->getDateCreation()->toString().c_str());
        ListInteraction listInteraction;
        databaseCRUD->getInteractionByContact(&listInteraction, this->listContact.getContactByIndex(i));
        for(int j=0;j<listInteraction.getSize();j++){
            QJsonArray arrayTodo;
            QJsonObject objectInteraction;
            objectInteraction.insert("idInteraction", std::to_string(listInteraction.getInteractionByIndex(j)->getId()).c_str());
            objectInteraction.insert("content", listInteraction.getInteractionByIndex(j)->getContent().c_str());
            objectInteraction.insert("dateCreation", listInteraction.getInteractionByIndex(j)->getDate()->toString().c_str());        
            ListTodo listTodo;
            databaseCRUD->getTodoByInteraction(&listTodo, listInteraction.getInteractionByIndex(j));
            for(int k=0;k<listTodo.getSize();k++){
                QJsonObject objectTodo;
                objectTodo.insert("idTodo", std::to_string(listTodo.getTodoByIndex(k)->getId()).c_str());
                objectTodo.insert("content", listTodo.getTodoByIndex(k)->getContent().c_str());
                objectTodo.insert("dateCreation", listTodo.getTodoByIndex(k)->getDate()->toString().c_str());
                arrayTodo.push_back(objectTodo);
            }
            if(!arrayTodo.isEmpty())
                objectInteraction.insert("Todos", arrayTodo);
            arrayInteraction.push_back(objectInteraction);
        }     
        if(!arrayInteraction.isEmpty())
            objectContact.insert("Interactions", arrayInteraction);
        mainArray.push_back(objectContact);
    }

    QJsonDocument jsonDoc;
    jsonDoc.setArray(mainArray);

    QFile fichierJSON("../data/JSONdata.json");

    if (fichierJSON.open(QFile::WriteOnly | QIODevice::Text))
    {
       fichierJSON.write(jsonDoc.toJson());
       fichierJSON.close();
    }
    else
    {
       qDebug() << "Erreur d'enregistrement";
    }
}





