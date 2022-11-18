/**
 * @file MainWindow.cpp
 * @brief Fichier cpp de la classe MainWindow
 */

#include <QMenu>
#include <QMenuBar>


#include "MainWindow.h"

MainWindow::MainWindow(DatabaseManagement * databaseManagement, ContactCRUD * contactCRUD, QWidget *parent)
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

        this->mainWidget=new MainWidget(contactCRUD);
        this->setCentralWidget(this->mainWidget);
    }

MainWindow::~MainWindow(){}
