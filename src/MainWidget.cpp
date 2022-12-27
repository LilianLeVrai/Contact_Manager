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
#include <QtGui>


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
    this->searchLineEdit->setObjectName("searchLineEdit");
    this->searchLineEdit->setPlaceholderText("nom, prénom, mail, ...");
    //bouton de recherche
    this->searchButton = new QPushButton("", this);
    this->searchButton->setObjectName("searchButton");
    QPixmap pixmapSearch(":/icon/icon/search.png");
    QIcon searchIcon(pixmapSearch);
    this->searchButton->setIcon(searchIcon);
    this->searchButton->setIconSize(pixmapSearch.rect().size());

    //selecteur de date
    QLabel * dateSelectorLabel1=new QLabel("Contacts crées entre le ",this);
    dateSelectorLabel1->setObjectName("whiteLabels");
    this->dateSelectorButton1 = new QPushButton(this);
    this->dateSelectorButton1->setContentsMargins(0,0,0,0);
    this->dateSelectorButton1->setObjectName("dateSelectorButton");
    this->dateSelectorButton1->setMinimumWidth(105);
    QLabel * dateSelectorLabel2=new QLabel("et le ",this);
    dateSelectorLabel2->setObjectName("whiteLabels");
    this->dateSelectorButton2 = new QPushButton(this);
    this->dateSelectorButton2->setContentsMargins(0,0,0,0);
    this->dateSelectorButton2->setObjectName("dateSelectorButton");
    this->dateSelectorButton2->setMinimumWidth(105);

    QPixmap pixmapDate(":/icon/icon/calendar.png");
    QIcon calendarIcon(pixmapDate);
    this->dateSelectorButton1->setIcon(calendarIcon);
    this->dateSelectorButton1->setIconSize(pixmapDate.rect().size());
    this->dateSelectorButton2->setIcon(calendarIcon);
    this->dateSelectorButton2->setIconSize(pixmapDate.rect().size());

    //bouton pour réinitialiser les filtres
    this->resetFiltersButton=new QPushButton("Réinitialiser les filtres",this);

    //label pour afficher les messages
    this->messageLabel=new MessageLabel;
    this->messageLabel->setProperty("",MessageLabel::NoStyle,true);

    //selection de tri
    this->sortCombobox=new QComboBox(this);
    this->sortCombobox->setObjectName("sortCombobox");
    this->sortCombobox->addItem("Trier par date de création");
    this->sortCombobox->addItem("Trier par ordre A->Z");
    this->sortCombobox->addItem("Trier par ordre Z->A");

    //Ajouter, details, supprimer contact
    QPixmap pixmapAdd(":/icon/icon/addContact.png");
    QIcon addIcon(pixmapAdd);
    this->addContactButton=new QPushButton;
    this->addContactButton->setIcon(addIcon);
    this->addContactButton->setStyleSheet("text-align: right;");
    this->addContactButton->setLayout(new QGridLayout);
    this->addContactLabel = new QLabel("Ajouter contact");
    this->addContactLabel->setAlignment(Qt::AlignCenter);
    this->addContactButton->layout()->setContentsMargins(0,0,0,0);
    this->addContactButton->layout()->addWidget(this->addContactLabel);

    QPixmap pixmapDetails(":/icon/icon/detailsContact.png");
    QIcon detailsIcon(pixmapDetails);
    this->detailsContactButton=new QPushButton;
    this->detailsContactButton->setIcon(detailsIcon);
    this->detailsContactButton->setStyleSheet("text-align: right;");
    this->detailsContactButton->setLayout(new QGridLayout);
    this->detailsContactLabel = new QLabel("Afficher details");
    this->detailsContactLabel->setAlignment(Qt::AlignCenter);
    this->detailsContactButton->layout()->setContentsMargins(0,0,0,0);
    this->detailsContactButton->layout()->addWidget(this->detailsContactLabel);

    QPixmap pixmapDelete(":/icon/icon/delete.png");
    QIcon deleteIcon(pixmapDelete);
    this->deleteContactButton=new QPushButton;
    this->deleteContactButton->setIcon(deleteIcon);
    this->deleteContactButton->setStyleSheet("text-align: right;");
    this->deleteContactButton->setLayout(new QGridLayout);
    this->deleteContactLabel = new QLabel("Supprimer contact");
    this->deleteContactLabel->setAlignment(Qt::AlignCenter);
    this->deleteContactButton->layout()->setContentsMargins(0,0,0,0);
    this->deleteContactButton->layout()->addWidget(this->deleteContactLabel);

    //tableau des contacts
    this->contactsTable = new QTableWidget(this);
    this->contactsTable->setObjectName("contactsTable");
    this->contactsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->contactsTable->setColumnCount(6);
    QStringList hlabels; hlabels <<"Nom"<<"Prénom"<<"Entreprise"<<"Mail"<<"Téléphone"<<"Date de création";
    this->contactsTable->setHorizontalHeaderLabels(hlabels);
    this->contactsTable->verticalHeader()->setVisible(false);
    this->contactsTable->horizontalHeader()->setSelectionMode(QAbstractItemView::NoSelection);
    this->contactsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->contactsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->contactsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QString myFontFamily = QFontDatabase::applicationFontFamilies(0).at(0);
    QFont myFont(myFontFamily);
    this->contactsTable->setFont(myFont);
    //label avec nombre de contacts
    this->nbContactsLabel=new QLabel(this);
    this->nbContactsLabel->setObjectName("nbContactLabel");
    this->nbContactsLabel->setFont(myFont);

    //Layout verticaux puis horizontaux
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * searchBarLayout = new QHBoxLayout();
    QHBoxLayout * dateAndResetLayout = new QHBoxLayout();
    QVBoxLayout * topLayout = new QVBoxLayout();
    QHBoxLayout * dateSelectorLayout = new QHBoxLayout();
    QHBoxLayout * resetFiltersButtonLayout = new QHBoxLayout();
    QHBoxLayout * leftButtonsShowContactLayout = new QHBoxLayout();
    QVBoxLayout * leftComboBoxLayout = new QVBoxLayout();
    QVBoxLayout * leftButtonsLayout = new QVBoxLayout();
    QVBoxLayout * showContactsLayout = new QVBoxLayout();

    //layout du top
    searchBarLayout->addWidget(this->filtersCombobox);
    searchBarLayout->addWidget(this->searchLineEdit);
    searchBarLayout->addWidget(this->searchButton);
    searchBarLayout->setSpacing(0);
    searchBarLayout->setContentsMargins(0,10,0,0);

    dateSelectorLayout->addWidget(dateSelectorLabel1);
    dateSelectorLayout->addWidget(this->dateSelectorButton1);
    dateSelectorLayout->addWidget(dateSelectorLabel2);
    dateSelectorLayout->addWidget(this->dateSelectorButton2);

    resetFiltersButtonLayout->addWidget(this->resetFiltersButton);

    dateAndResetLayout->addLayout(dateSelectorLayout);
    dateAndResetLayout->addLayout(resetFiltersButtonLayout);
    dateAndResetLayout->setContentsMargins(0,10,0,10);

    topLayout->addWidget(this->messageLabel);
    topLayout->addLayout(searchBarLayout);
    topLayout->addLayout(dateAndResetLayout);
    topLayout->setContentsMargins(100,20,100,10);

    QWidget * topWidget=new QWidget(this);
    topWidget->setObjectName("topWidgetMainWidget");
    topWidget->setLayout(topLayout);

    //layout du bas
    leftComboBoxLayout->addWidget(this->sortCombobox);
    leftComboBoxLayout->setContentsMargins(0, 0, 0, 32);
    leftButtonsLayout->addLayout(leftComboBoxLayout);
    leftButtonsLayout->addWidget(this->addContactButton);
    leftButtonsLayout->addWidget(this->detailsContactButton);
    leftButtonsLayout->addWidget(this->deleteContactButton);

    showContactsLayout->addWidget(this->contactsTable);
    showContactsLayout->addWidget(this->nbContactsLabel);
    showContactsLayout->setContentsMargins(15,0,0,0);

    leftButtonsShowContactLayout->addLayout(leftButtonsLayout);
    leftButtonsShowContactLayout->addLayout(showContactsLayout);
    leftButtonsShowContactLayout->setContentsMargins(100,40,100,20);

    //ajout des layout (attention à l'ordre)
    mainLayout->addWidget(topWidget);
    mainLayout->addLayout(leftButtonsShowContactLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    //propriétés d'alignement sur les layout et widget
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
    this->detailsContactLabel->setStyleSheet("color: #b5b7ba");
    this->deleteContactButton->setEnabled(false);
    this->deleteContactLabel->setStyleSheet("color: #b5b7ba");
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
        this->dateSelectorButton1->setIcon(QIcon());
        this->dateSelectorButton1->setText(this->filterFirstDate->toString().c_str());
        if(this->filterFirstDate!=nullptr && this->filterSecondDate!=nullptr)
            {
            if(!this->filterFirstDate->isLessThan(this->filterSecondDate))
                {
                this->messageLabel->setProperty("La date de départ est supérieur à la date de fin.", MessageLabel::Red, true);
                }
            else
                this->messageLabel->setProperty("",MessageLabel::NoStyle,true);
            }
        }
}

void MainWidget::closeSecondCalendarDialog(QDate * date){
    if(date!=nullptr)
        {
        this->filterSecondDate=new Date(date->day(), date->month(), date->year());
        this->dateSelectorButton2->setIcon(QIcon());
        this->dateSelectorButton2->setText(this->filterSecondDate->toString().c_str());
        if(this->filterFirstDate!=nullptr && this->filterSecondDate!=nullptr)
            {
            if(!this->filterFirstDate->isLessThan(this->filterSecondDate))
                {
                this->messageLabel->setProperty("La date de départ est supérieur à la date de fin.", MessageLabel::Red, true);
                }
            else
                this->messageLabel->setProperty("",MessageLabel::NoStyle,true);
            }
    }
}

void MainWidget::updateTable(){fillTable();}

void MainWidget::enableDeleteDetailsButton(){
    this->detailsContactButton->setEnabled(true);
    this->detailsContactLabel->setStyleSheet("color: #070323");
    this->deleteContactButton->setEnabled(true);
    this->deleteContactLabel->setStyleSheet("color: #070323");
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
    QPixmap pixmap(":/icon/icon/calendar.png");
    QIcon calendarIcon(pixmap);
    this->dateSelectorButton1->setIcon(calendarIcon);
    this->dateSelectorButton1->setIconSize(pixmap.rect().size());
    this->dateSelectorButton2->setIcon(calendarIcon);
    this->dateSelectorButton2->setIconSize(pixmap.rect().size());
    this->filterFirstDate=nullptr;
    this->filterSecondDate=nullptr;
    this->messageLabel->setProperty("",MessageLabel::NoStyle,true);
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
    this->detailsContactDialog=new DetailsContactDialog(this->databaseCRUD,this->listContact.getContactByIndex(this->contactsTable->selectionModel()->currentIndex().row()),this);
    QObject::connect(this->detailsContactDialog, SIGNAL(emitModifyContact(Contact*, bool)), this, SLOT(editContact(Contact*, bool)));
    this->detailsContactDialog->show();
}

