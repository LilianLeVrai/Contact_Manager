/**
 * @file MainWidget.cpp
 * @brief Fichier cpp de la classe MainWidget
 */


#include "MainWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStringList>
#include <QDebug>
#include <QAbstractItemView>
#include <QMenu>
#include <QAction>
#include <QToolBar>

//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
MainWidget::MainWidget(DatabaseCRUD * databaseCRUD, QWidget *parent)
    : QWidget(parent)
{
    this->databaseCRUD=databaseCRUD;
    databaseCRUD->getAllContacts(&this->listContact);

    this->filterFirstDate=nullptr;
    this->filterSecondDate=nullptr;

    initUI();
    initConnect();
    fillTable();
}

MainWidget::~MainWidget(){
    delete(this->filtersCombobox);
    delete(this->searchButton);
    delete(this->searchLineEdit);
    delete(this->dateSelectorButton1);
    delete(this->dateSelectorButton2);
    delete(this->messageLabel);
    delete(this->resetFiltersButton);
    delete(this->contactsTable);
    delete(this->nbContactsLabel);
    delete(this->sortCombobox);
    delete(this->addContactButton);
    delete(this->detailsContactButton);
    delete(this->deleteContactButton);

    delete(this->calendarDialogFirstDate);
    delete(this->calendarDialogSecondDate);
    delete(this->filterFirstDate);
    delete(this->filterSecondDate);

    delete(this->createContactDialog);
    delete(this->detailsContactDialog);
}



//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------
void MainWidget::initUI(){

    //selection de filtre
    this->filtersCombobox = new QComboBox(this);
    this->filtersCombobox->setObjectName("filtersCombobox");
    this->filtersCombobox->addItem("Pas de filtre");
    this->filtersCombobox->addItem("Nom");
    this->filtersCombobox->addItem("Prénom");
    this->filtersCombobox->addItem("Entreprise");
    this->filtersCombobox->addItem("Mail");
    this->filtersCombobox->addItem("Telephone");

    //barre de recherche
    this->searchLineEdit = new QLineEdit(this);
    this->searchLineEdit->setPlaceholderText("nom, prénom, mail, ...");
    this->searchLineEdit->setObjectName("searchLineEdit");
    //bouton de recherche
    this->searchButton = new QPushButton("Rechercher", this);
    this->searchButton->setObjectName("searchButton");

    //selecteur de date
    QLabel * dateSelectorLabel1=new QLabel("Contacts crées entre le ");
    this->dateSelectorButton1 = new QPushButton(this);
    this->dateSelectorButton1->setMinimumWidth(100);
    QLabel * dateSelectorLabel2=new QLabel("et le ");
    this->dateSelectorButton2 = new QPushButton(this);
    this->dateSelectorButton2->setMinimumWidth(100);

    //bouton pour réinitialiser les filtres
    this->resetFiltersButton=new QPushButton("Réinitialiser les filtres");

    //label pour afficher les messages
    this->messageLabel=new MessageLabel;

    //selection de tri
    this->sortCombobox=new QComboBox(this);
    this->sortCombobox->setObjectName("sortCombobox");
    this->sortCombobox->addItem("Trier par date de création");
    this->sortCombobox->addItem("Trier par ordre A->Z");
    this->sortCombobox->addItem("Trier par ordre Z->A");

    //Ajouter, details, supprimer contact
    this->addContactButton = new QPushButton("Ajouter contact");
    this->detailsContactButton = new QPushButton("Afficher details");
    detailsContactButton->setEnabled(false);
    this->deleteContactButton = new QPushButton("Supprimer contact");
    deleteContactButton->setEnabled(false);

    //tableau des contacts
    this->contactsTable = new QTableWidget(this);
    this->contactsTable->setObjectName("contactsTable");
    this->contactsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->contactsTable->setColumnCount(6);
    QStringList hlabels; hlabels <<"Nom"<<"Prénom"<<"Entreprise"<<"mail"<<"Téléphone"<<"Date de création";
    this->contactsTable->setHorizontalHeaderLabels(hlabels);
    this->contactsTable->verticalHeader()->setVisible(false);
    this->contactsTable->horizontalHeader()->setSelectionMode(QAbstractItemView::NoSelection);
    this->contactsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->contactsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->contactsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    //label avec nombre de contacts
    this->nbContactsLabel=new QLabel;

    //Layout verticaux puis horizontaux
    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    QHBoxLayout * searchBarLayout = new QHBoxLayout();
    QHBoxLayout * dateAndResetLayout = new QHBoxLayout();
    QHBoxLayout * dateSelectorLayout = new QHBoxLayout();   
    QHBoxLayout * resetFiltersButtonLayout = new QHBoxLayout();
    QHBoxLayout * leftButtonsShowContactLayout = new QHBoxLayout();
    QVBoxLayout * leftButtonsLayout = new QVBoxLayout();
    QVBoxLayout * showContactsLayout = new QVBoxLayout();

    //ajouts des widget dans chaque layout
    searchBarLayout->addWidget(this->filtersCombobox);
    searchBarLayout->addWidget(this->searchLineEdit);
    searchBarLayout->addWidget(this->searchButton);


    dateSelectorLayout->addWidget(dateSelectorLabel1);
    dateSelectorLayout->addWidget(this->dateSelectorButton1);
    dateSelectorLayout->addWidget(dateSelectorLabel2);
    dateSelectorLayout->addWidget(this->dateSelectorButton2);

    resetFiltersButtonLayout->addWidget(this->resetFiltersButton);

    dateAndResetLayout->addLayout(dateSelectorLayout);
    dateAndResetLayout->addLayout(resetFiltersButtonLayout);


    leftButtonsLayout->addWidget(this->sortCombobox);
    leftButtonsLayout->addWidget(this->addContactButton);
    leftButtonsLayout->addWidget(this->detailsContactButton);
    leftButtonsLayout->addWidget(this->deleteContactButton);

    showContactsLayout->addWidget(this->contactsTable);
    showContactsLayout->addWidget(this->nbContactsLabel);

    leftButtonsShowContactLayout->addLayout(leftButtonsLayout);
    leftButtonsShowContactLayout->addLayout(showContactsLayout);

    //ajout des layout (attention à l'ordre)
    mainLayout->addLayout(searchBarLayout);
    mainLayout->addLayout(dateAndResetLayout);
    mainLayout->addWidget(this->messageLabel);
    mainLayout->addLayout(leftButtonsShowContactLayout);

    //propriétés d'alignement sur les layout et widget
    leftButtonsShowContactLayout->setContentsMargins(0,20,0,0);
    dateAndResetLayout->setAlignment(dateSelectorLayout, Qt::AlignLeft);
    dateAndResetLayout->setAlignment(resetFiltersButtonLayout, Qt::AlignRight);
    leftButtonsLayout->setAlignment(Qt::AlignTop);
}

void MainWidget::initConnect(){
    QObject::connect(this->dateSelectorButton1, SIGNAL(clicked()), this, SLOT(openFirstCalendarDialog()));
    QObject::connect(this->dateSelectorButton2, SIGNAL(clicked()), this, SLOT(openSecondCalendarDialog()));
    QObject::connect(this->sortCombobox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable()));
    QObject::connect(this->contactsTable, SIGNAL(cellClicked(int,int)), this, SLOT(enableDeleteDetailsButton()));
    QObject::connect(this->deleteContactButton, SIGNAL(clicked()), this, SLOT(deleteContact()));
    QObject::connect(this->resetFiltersButton, SIGNAL(clicked()), this, SLOT(resetFilters()));
    QObject::connect(this->searchButton, SIGNAL(clicked()), this, SLOT(searchContacts()));
    QObject::connect(this->addContactButton, SIGNAL(clicked()), this, SLOT(openCreateContactDialog()));
    QObject::connect(this->detailsContactButton, SIGNAL(clicked()), this, SLOT(openDetailsContactDialog()));
}

void MainWidget::fillTable(){
    this->disableDeleteDetailsButton();
    if(this->sortCombobox->currentIndex()==0)
        this->listContact.sortByCreateDate();
    if(this->sortCombobox->currentIndex()==1)
        this->listContact.sortByAlphabet();
    if(this->sortCombobox->currentIndex()==2)
        this->listContact.sortByReverseAlphabet();

    this->contactsTable->setRowCount(0);

    for(int i=0; i<this->listContact.getSize(); i++)
        {
        this->contactsTable->insertRow(i);

        this->contactsTable->setItem(i,0,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getLastName().c_str()));
        this->contactsTable->setItem(i,1,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getFirstName().c_str()));
        this->contactsTable->setItem(i,2,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getCompany().c_str()));
        this->contactsTable->setItem(i,3,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getMail().c_str()));
        this->contactsTable->setItem(i,4,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getPhone().c_str()));
        this->contactsTable->setItem(i,5,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getDateCreation()->toString().c_str()));
        }
    this->nbContactsLabel->setText(QString::number(this->contactsTable->rowCount())+" contact(s)");
}


void MainWidget::disableDeleteDetailsButton(){
    this->detailsContactButton->setEnabled(false);
    this->deleteContactButton->setEnabled(false);
}


//------------------------------------------------------------------------------------------------------------------------------
//slots
//------------------------------------------------------------------------------------------------------------------------------
void MainWidget::openFirstCalendarDialog(){
    this->calendarDialogFirstDate=new CalendarDialog();
    QDate currentDate=currentDate.currentDate();
    this->calendarDialogFirstDate->getCalendar()->setMaximumDate(currentDate);
    QObject::connect(this->calendarDialogFirstDate, SIGNAL(emitClose(QDate *)), this, SLOT(closeFirstCalendarDialog(QDate *)));
    this->calendarDialogFirstDate->show();
}

void MainWidget::openSecondCalendarDialog(){
    this->calendarDialogSecondDate=new CalendarDialog();
    QDate currentDate=currentDate.currentDate();
    this->calendarDialogSecondDate->getCalendar()->setMaximumDate(currentDate);
    QObject::connect(this->calendarDialogSecondDate, SIGNAL(emitClose(QDate *)), this, SLOT(closeSecondCalendarDialog(QDate *)));
    this->calendarDialogSecondDate->show();
}

void MainWidget::closeFirstCalendarDialog(QDate * date){
    if(date!=nullptr)
        {
        this->filterFirstDate=new Date(date->day(), date->month(), date->year());
        this->dateSelectorButton1->setText(this->filterFirstDate->toString().c_str());
        if(this->filterFirstDate!=nullptr && this->filterSecondDate!=nullptr)
            {
            if(!this->filterFirstDate->isLessThan(this->filterSecondDate))
                {
                this->messageLabel->setProperty("La date de départ est supérieur à la date de fin.", MessageLabel::Red, true);
                }
            else
                this->messageLabel->setVisible(false);
            }
        }
}

void MainWidget::closeSecondCalendarDialog(QDate * date){
    if(date!=nullptr)
        {
        this->filterSecondDate=new Date(date->day(), date->month(), date->year());
        this->dateSelectorButton2->setText(this->filterSecondDate->toString().c_str());
        if(this->filterFirstDate!=nullptr && this->filterSecondDate!=nullptr)
            {
            if(!this->filterFirstDate->isLessThan(this->filterSecondDate))
                {
                this->messageLabel->setProperty("La date de départ est supérieur à la date de fin.", MessageLabel::Red, true);
                }
            else
                this->messageLabel->setVisible(false);
            }
    }
}

void MainWidget::updateTable(){fillTable();}

void MainWidget::enableDeleteDetailsButton(){
    this->detailsContactButton->setEnabled(true);
    this->deleteContactButton->setEnabled(true);
}


void MainWidget::deleteContact(){
    this->databaseCRUD->deleteContactBDD(this->listContact.getContactByIndex(this->contactsTable->selectionModel()->currentIndex().row()));
    this->databaseCRUD->searchByFilters(&this->listContact, this->searchLineEdit->text(),
                                       this->filtersCombobox->currentIndex(), this->filterFirstDate, this->filterSecondDate);
    this->fillTable();
}

void MainWidget::resetFilters(){
    this->filtersCombobox->setCurrentIndex(0);
    this->searchLineEdit->setText("");
    this->dateSelectorButton1->setText("");
    this->dateSelectorButton2->setText("");
    this->filterFirstDate=nullptr;
    this->filterSecondDate=nullptr;
    this->messageLabel->setVisible(false);
    this->databaseCRUD->getAllContacts(&this->listContact);
    this->fillTable();
}

void MainWidget::searchContacts(){
    this->databaseCRUD->searchByFilters(&this->listContact, this->searchLineEdit->text(),
                                       this->filtersCombobox->currentIndex(), this->filterFirstDate, this->filterSecondDate);
    this->fillTable();
}


void MainWidget::openCreateContactDialog(){
    this->createContactDialog=new EditContactDialog();
    QObject::connect(this->createContactDialog, SIGNAL(emitClose(Contact*, bool)), this, SLOT(editContact(Contact*, bool)));
    this->createContactDialog->show();
}


void MainWidget::editContact(Contact * contact, bool error){
    if(contact->getId()==-1)
        {
        this->databaseCRUD->addContactBDD(contact);

        if(error)
            this->messageLabel->setProperty("Le contact a été ajouté, l'image par défaut lui a été attribué.", MessageLabel::Red, true);
        else
            this->messageLabel->setProperty("Le contact a été ajouté sans erreur.", MessageLabel::Green, true);
        }
    else
        {
        this->databaseCRUD->modifyContactBDD(contact);

        if(error)
            this->messageLabel->setProperty("Le contact a été modifié, l'image par défaut lui a été attribué.", MessageLabel::Red, true);
        else
            this->messageLabel->setProperty("Le contact a été modifié sans erreur.", MessageLabel::Green, true);
        }

    this->databaseCRUD->searchByFilters(&this->listContact, this->searchLineEdit->text(),
                                       this->filtersCombobox->currentIndex(), this->filterFirstDate, this->filterSecondDate);
    this->fillTable();
}


void MainWidget::openDetailsContactDialog(){
    this->detailsContactDialog=new DetailsContactDialog(this->databaseCRUD,this->listContact.getContactByIndex(this->contactsTable->selectionModel()->currentIndex().row()));
    QObject::connect(this->detailsContactDialog, SIGNAL(emitModifyContact(Contact*, bool)), this, SLOT(editContact(Contact*, bool)));
    this->detailsContactDialog->show();
}

