/**
 * @file DatabaseManagement.cpp
 * @brief Fichier cpp de la classe DatabaseManagement
 */


#include "DatabaseManagement.h"

#include <QDebug>
#include <QSqlQuery>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDir>

#include <QSqlError>

DatabaseManagement::DatabaseManagement()
{
    this->database = QSqlDatabase::addDatabase("QSQLITE");

    //Verifie si le dossier data existe, si n'existe pas le créé
    QDir dir("data");
    if (!dir.exists())
        dir.mkpath(".");

    database.setDatabaseName("data/database.sqlite");

      if(!database.open())
        {
        qDebug() << "La connection à la BDD à échoué";
        }
      else
          {
          qDebug() << "Connexion BDD ok";

          QFile initFile;
          QString initInstructions;
          QSqlQuery query;

          //création de la table Contact si inexistante
          initFile.setFileName(":/resources/resourceFiles/initContact.sql");
          initFile.open(QIODevice::ReadOnly);
          initInstructions =initFile.readAll();
          initFile.close();
          if(!query.exec(initInstructions))
            {qDebug() << "Impossible d'appliquer le fichier initContact.sql à la BDD :\n" << query.lastError();}
          else
            {qDebug() << "fichier initContact appliqué à la BDD";}

          //création de la table Interaction si inexistante
          initFile.setFileName(":/resources/resourceFiles/initInteraction.sql");
          initFile.open(QIODevice::ReadOnly);
          initInstructions =initFile.readAll();
          initFile.close();
          if(!query.exec(initInstructions))
            {qDebug() << "Impossible d'appliquer le fichier initInteraction.sql à la BDD :\n" << query.lastError();}
          else
            {qDebug() << "fichier initInteraction appliqué à la BDD";}

          //création de la table Todo si inexistante
          initFile.setFileName(":/resources/resourceFiles/initTodo.sql");
          initFile.open(QIODevice::ReadOnly);
          initInstructions =initFile.readAll();
          initFile.close();
          if(!query.exec(initInstructions))
            {qDebug() << "Impossible d'appliquer le fichier initTodo.sql à la BDD :\n" << query.lastError();}
          else
            {qDebug() << "fichier initTodo appliqué à la BDD";}

          //création de la table Modification si inexistante
          initFile.setFileName(":/resources/resourceFiles/initModification.sql");
          initFile.open(QIODevice::ReadOnly);
          initInstructions =initFile.readAll();
          initFile.close();
          if(!query.exec(initInstructions))
            {qDebug() << "Impossible d'appliquer le fichier initModification.sql à la BDD :\n" << query.lastError();}
          else
            {qDebug() << "fichier initModification appliqué à la BDD";}

          //active les clés étrangères (pour le 'ON DELETE CASCADE')
          if(!query.exec("PRAGMA foreign_keys=ON;"))
            {qDebug() << "Impossible d'activer les clés étrangères :\n" << query.lastError();}
          else
            {qDebug() << "clés étrangères activées";}

          qDebug() << "------------------------------------------------------------------";
        }
}

DatabaseManagement::~DatabaseManagement(){
    this->database.close();
}

void DatabaseManagement::initDataTest(){
    QFile initDataFile(":/resources/resourceFiles/dataTest.sql");
    QString initDataInstructions;

    if (initDataFile.open(QIODevice::ReadOnly))
    {
       QSqlQuery query;
       QTextStream in(&initDataFile);
       while (!in.atEnd())
       {
          initDataInstructions = in.readLine();
          if(!query.exec(initDataInstructions))
            {qDebug() << "Impossible d'insérer les données à la table :\n" << query.lastError();}
          else
            {qDebug() << "Données insérées dans la table :" << initDataInstructions;}
       }
       initDataFile.close();
       qDebug() << "------------------------------------------------------------------";
    }
    else{qDebug() << "Le fichier dataTest.sql n'as pas pu être ouvert";}
}

QSqlDatabase * DatabaseManagement::getDatabase(){return &(this->database);}

void DatabaseManagement::createJSONfile(DatabaseCRUD * databaseCRUD){
    ListContact listContact;
    databaseCRUD->getAllContacts(&listContact);

    QJsonObject mainObject;
    QJsonArray mainArray;

    for(int i=0;i<listContact.getSize();i++){
        QJsonArray arrayInteraction;
        QJsonObject objectContact;
        objectContact.insert("idContact",std::to_string(listContact.getContactByIndex(i)->getId()).c_str());
        objectContact.insert("lastName",listContact.getContactByIndex(i)->getLastName().c_str());
        objectContact.insert("firstName",listContact.getContactByIndex(i)->getFirstName().c_str());
        objectContact.insert("company",listContact.getContactByIndex(i)->getCompany().c_str());
        objectContact.insert("mail",listContact.getContactByIndex(i)->getMail().c_str());
        objectContact.insert("phone",listContact.getContactByIndex(i)->getPhone().c_str());
        objectContact.insert("picture",listContact.getContactByIndex(i)->getPathPicture().c_str());
        objectContact.insert("dateCreation",listContact.getContactByIndex(i)->getDateCreation()->toString().c_str());
        ListInteraction listInteraction;
        databaseCRUD->getInteractionByContact(&listInteraction, listContact.getContactByIndex(i));
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
                if(listTodo.getTodoByIndex(k)->getDate()!=nullptr){
                    objectTodo.insert("dateCreation", listTodo.getTodoByIndex(k)->getDate()->toString().c_str());
                }
                arrayTodo.push_back(objectTodo);
            }
            if(!arrayTodo.isEmpty())
                objectInteraction.insert("Todos", arrayTodo);
            arrayInteraction.push_back(objectInteraction);
        }
        if(!arrayInteraction.isEmpty())
            objectContact.insert("Interactions", arrayInteraction);
            QJsonObject contact;
            contact.insert("Contact", objectContact);
        mainArray.push_back(contact);
    }

    mainObject.insert("Contacts", mainArray);
    QJsonDocument jsonDoc;
    jsonDoc.setObject(mainObject);

    QFile fichierJSON("data/JSONdata.json");

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
