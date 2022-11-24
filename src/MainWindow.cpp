/**
 * @file MainWindow.cpp
 * @brief Fichier cpp de la classe MainWindow
 */

#include <QMenu>
#include <QMenuBar>
#include <QDebug>

#include "MainWindow.h"


MainWindow::MainWindow(DatabaseManagement * databaseManagement, DatabaseCRUD * databaseCRUD, QWidget *parent)
    : QMainWindow(parent)
    {
        this->databaseManagement=databaseManagement;

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





