#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    resize(1600, 800);

    //selection de filtre
    this->filtersCombobox = new QComboBox(this);
    this->filtersCombobox->setObjectName("filtersCombobox");
    this->filtersCombobox->addItem("Pas de filtre");
    this->filtersCombobox->addItem("Nom");
    this->filtersCombobox->addItem("Prénom");
    this->filtersCombobox->addItem("Mail");

    //barre de recherche
    this->searchLineEdit = new QLineEdit(this);
    this->searchLineEdit->setPlaceholderText("nom, prénom, mail, ...");
    this->searchLineEdit->setObjectName("searchLineEdit");
    //bouton de recherche
    this->searchButton = new QPushButton("Rechercher", this);
    this->searchButton->setObjectName("searchButton");

    //selection de tri
    this->sortCombobox=new QComboBox(this);
    this->sortCombobox->setObjectName("sortCombobox");
    this->sortCombobox->addItem("Trier par date de création");
    this->sortCombobox->addItem("Trier par ordre A->Z");
    this->sortCombobox->addItem("Trier par ordre Z->A");

    //tableau des contacts
    this->contactsTable = new QTableView(this);
    this->contactsTable->setObjectName("contactsTable");

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * searchLayout = new QHBoxLayout();
    QHBoxLayout * showContactsLayout = new QHBoxLayout();

    searchLayout->addWidget(this->filtersCombobox);
    searchLayout->addWidget(this->searchLineEdit);
    searchLayout->addWidget(this->searchButton);

    showContactsLayout->addWidget(this->sortCombobox);
    showContactsLayout->addWidget(this->contactsTable);

    mainLayout->addLayout(searchLayout);
    mainLayout->addLayout(showContactsLayout);


}





MainWindow::~MainWindow(){}
