/**
 * @file DatabaseManagement.cpp
 * @brief Fichier cpp de la classe DatabaseManagement
 */


#include "DatabaseManagement.h"
#include <QDebug>
#include <QSqlQuery>
#include <QFile>
#include <QString>

#include <QSqlError>

DatabaseManagement::DatabaseManagement()
{
    this->database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName("../data/database.sqlite");

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
          initFile.setFileName("../data/initContact.sql");
          initFile.open(QIODevice::ReadOnly);
          initInstructions =initFile.readAll();
          initFile.close();
          if(!query.exec(initInstructions))
            {qDebug() << "Impossible d'appliquer le fichier initContact.sql à la BDD :\n" << query.lastError();}
          else
            {qDebug() << "fichier initContact appliqué à la BDD";}

          //création de la table Interaction si inexistante
          initFile.setFileName("../data/initInteraction.sql");
          initFile.open(QIODevice::ReadOnly);
          initInstructions =initFile.readAll();
          initFile.close();
          if(!query.exec(initInstructions))
            {qDebug() << "Impossible d'appliquer le fichier initInteraction.sql à la BDD :\n" << query.lastError();}
          else
            {qDebug() << "fichier initInteraction appliqué à la BDD";}

          //création de la table Todo si inexistante
          initFile.setFileName("../data/initTodo.sql");
          initFile.open(QIODevice::ReadOnly);
          initInstructions =initFile.readAll();
          initFile.close();
          if(!query.exec(initInstructions))
            {qDebug() << "Impossible d'appliquer le fichier initTodo.sql à la BDD :\n" << query.lastError();}
          else
            {qDebug() << "fichier initTodo appliqué à la BDD";}

          //création de la table Modification si inexistante
          initFile.setFileName("../data/initModification.sql");
          initFile.open(QIODevice::ReadOnly);
          initInstructions =initFile.readAll();
          initFile.close();
          if(!query.exec(initInstructions))
            {qDebug() << "Impossible d'appliquer le fichier initModification.sql à la BDD :\n" << query.lastError();}
          else
            {qDebug() << "fichier initModification appliqué à la BDD";}

        }
}

void DatabaseManagement::initDataTest(){
    QFile initDataFile("../data/dataTest.sql");
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
    }
    else{qDebug() << "Le fichier dataTest.sql n'as pas pu être ouvert";}
}

QSqlDatabase * DatabaseManagement::getDatabase(){return &(this->database);}
