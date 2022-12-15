/**
 * @file main
 */



#include <iostream>
#include <QString>
#include <QApplication>
#include "MainWindow.h"
#include "DatabaseManagement.h"
#include "DatabaseCRUD.h"

#include <QFile>
#include <QString>
#include <QDebug>
#include <QMainWindow>

#include <QDir>

using namespace std;

int main(int argc, char *argv[])
{
    //déclaration de l'application
    QApplication app(argc, argv);

    // Création du dossier img s'il n'existe pas chez l'utilisateur
    QDir().mkdir("img");

    //déclaration de la BDD
    DatabaseManagement database=DatabaseManagement();
    DatabaseCRUD databaseCRUD(database.getDatabase());

    //declaration du widget principal
    MainWindow mainWindow(&databaseCRUD);
    mainWindow.show();

    //déclaration du styleSheet
    QFile styleFile(":/resources/resourceFiles/style.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleSheet = styleFile.readAll();
    app.setStyleSheet(styleSheet.arg("#F8F7FF"));//description des couleurs dans le fichier de style
    styleFile.close();


    return app.exec();
}
