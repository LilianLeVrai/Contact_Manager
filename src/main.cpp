/**
 * @file main
 */




#include "MainWindow.h"
#include "DatabaseManagement.h"
#include "DatabaseCRUD.h"

#include <iostream>
#include <QApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QMainWindow>
#include <QtGui>
#include <QDebug>
#include <QDir>

using namespace std;

int main(int argc, char *argv[])
{


    //déclaration de l'application
    QApplication app(argc, argv);

    //chargement des fonts
    QFontDatabase::addApplicationFont(":/font/font/Ubuntu-Light.ttf");
    QFontDatabase::addApplicationFont(":/font/font/Ubuntu-Regular.ttf");
    QFontDatabase::addApplicationFont(":/font/font/Ubuntu-Medium.ttf");
    QFontDatabase::addApplicationFont(":/font/font/Ubuntu-Bold.ttf");
    //application d'une font à toute l'application
    QString myFontFamily = QFontDatabase::applicationFontFamilies(2).at(0);
    QFont myFont(myFontFamily);
    app.setFont(myFont);

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
    app.setStyleSheet(styleSheet.arg("#fefffe").arg("#373353").arg("#ffd803").arg("#ffe823").arg("#fffffe").arg("#070323").arg("#f0f2f5").arg("#e5e7ea").arg("#b5b7ba"));//description des couleurs dans le fichier de style
    styleFile.close();


    return app.exec();
}
