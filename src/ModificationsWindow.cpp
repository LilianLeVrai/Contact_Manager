/**
 * @file ModificationsWindow.cpp
 * @brief Fichier cpp de la classe ModificationsWindow
 */

#include "ModificationsWindow.h"


ModificationsWindow::ModificationsWindow(DatabaseCRUD * databaseCRUD, QWidget *parent)
    : QDialog(parent)
{
    this->databaseCRUD=databaseCRUD;
    this->setWindowTitle("Liste des modifications");
    this->initUI();
    this->fillModificationsTable();

    QObject::connect(this->refreshButton, SIGNAL(clicked()), this, SLOT(refreshTable()));
}


ModificationsWindow::ModificationsWindow(Contact * contact, DatabaseCRUD * databaseCRUD, QWidget *parent)
    : QDialog(parent)
{
    this->databaseCRUD=databaseCRUD;
    QString s="Liste des modifications du contact : ";
    s=s+contact->getFirstName().c_str()+" "+contact->getLastName().c_str();
    this->setWindowTitle(s);
    this->initUI();
    this->contact=contact;
    this->fillModificationsTableByContact();

    QObject::connect(this->refreshButton, SIGNAL(clicked()), this, SLOT(refreshTableByContact()));
}

ModificationsWindow::~ModificationsWindow(){
    delete(this->modificationsTable);
    delete(this->refreshButton);
}

void ModificationsWindow::initUI(){

    this->setWindowIcon(QIcon(":/resources/resourceFiles/logo.png"));
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->resize(1200, 600);

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    this->refreshButton=new QPushButton("Rafraichir",this);
    mainLayout->addWidget(this->refreshButton);

    this->modificationsTable = new QTableWidget(this);
    this->modificationsTable->setObjectName("modificationsTable");
    this->modificationsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->modificationsTable->setColumnCount(2);
    QStringList hlabels; hlabels <<"Modification"<<"Date";
    this->modificationsTable->setHorizontalHeaderLabels(hlabels);
    this->modificationsTable->verticalHeader()->setVisible(false);
    this->modificationsTable->horizontalHeader()->setSelectionMode(QAbstractItemView::NoSelection);
    this->modificationsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->modificationsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->modificationsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(this->modificationsTable);
}

void ModificationsWindow::fillModificationsTable(){
    this->databaseCRUD->fillModificationsTable(this->modificationsTable);
}

void ModificationsWindow::fillModificationsTableByContact(){
    this->databaseCRUD->fillModificationsTableByContact(this->modificationsTable, this->contact);
}

void ModificationsWindow::refreshTable(){
    this->fillModificationsTable();
}

void ModificationsWindow::refreshTableByContact(){
    this->fillModificationsTableByContact();
}
