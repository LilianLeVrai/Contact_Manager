/**
 * @file main
 */



#include <iostream>
#include "Date.h"
#include "Todo.h"
#include "ListTodo.h"
#include <QString>
#include "Interaction.h"
#include "ListInteraction.h"
#include "Contact.h"
#include "ListContact.h"
#include <QApplication>
#include "MainWindow.h"
#include "DatabaseManagement.h"
#include "DatabaseCRUD.h"

#include <QFile>
#include <QString>
#include <QDebug>
#include <QMainWindow>

#include <QPushButton>

#include <QTranslator>

using namespace std;

int main(int argc, char *argv[])
{
    //déclaration de l'application
    QApplication app(argc, argv);


    //déclaration de la BDD
    DatabaseManagement database=DatabaseManagement();
    DatabaseCRUD databaseCRUD(database.getDatabase());

    //declaration du widget principal
    MainWindow mainWindow(&databaseCRUD);
    mainWindow.show();

    //déclaration du styleSheet
    QFile styleFile("../style/style.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleSheet = styleFile.readAll();
    app.setStyleSheet(styleSheet.arg("#F8F7FF").arg("#9381FF").arg("#B8B8FF"));//description des couleurs dans le fichier de style



    return app.exec();
}
