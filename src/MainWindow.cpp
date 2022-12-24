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


MainWindow::MainWindow(DatabaseCRUD * databaseCRUD, QWidget *parent)
    : QMainWindow(parent)
    {
        this->databaseCRUD=databaseCRUD;

        this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
        this->setWindowIcon(QIcon(":/resources/resourceFiles/logo.png"));
        this->setWindowTitle("Gestionnaire de contact");
        this->resize(1600, 800);

        QMenu * optionsMenu=new QMenu("Options",this);
        this->optionExportJson=new QAction("Exporter les données en JSON",this);
        this->optionInitDataTest=new QAction("Initialiser les données de tests",this);
        this->showAllModification=new QAction("Afficher les modifications",this);
        optionsMenu->addAction(this->optionExportJson);
        optionsMenu->addAction(this->optionInitDataTest);
        this->menuBar()->addMenu(optionsMenu);
        this->menuBar()->addAction(this->showAllModification);


        this->mainWidget=new MainWidget(databaseCRUD,this);
        this->setCentralWidget(this->mainWidget);

        connect(this->optionExportJson, SIGNAL(triggered()), this, SLOT(createJSON()));
        connect(this->optionInitDataTest, SIGNAL(triggered()), this, SLOT(askInitDataTest()));
        connect(this, SIGNAL(emitUpdateContact()), this->mainWidget, SLOT(searchContacts()));
        connect(this->showAllModification, SIGNAL(triggered()), this, SLOT(openModificationsWindow()));
    }

MainWindow::~MainWindow(){
    delete(this->optionExportJson);
    delete(this->optionInitDataTest);
    delete(this->showAllModification);

    delete(this->mainWidget);

    delete(this->yesNoDialogDataTest);
    delete(this->modificationsWindow);
}

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
    this->databaseManagement->createJSONfile(this->databaseCRUD);
}

void MainWindow::openModificationsWindow(){
    this->modificationsWindow=new ModificationsWindow(this->databaseCRUD, this);
    this->modificationsWindow->show();
}




