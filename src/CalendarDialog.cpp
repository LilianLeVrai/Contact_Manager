/**
 * @file CalendarDialog.cpp
 * @brief Fichier cpp de la classe CalendarDialog
 */


#include "CalendarDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>


//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
CalendarDialog::CalendarDialog(QWidget *parent)
    : QDialog(parent)
{
    setModal(true);
    initUI();
    initConnect();
}

CalendarDialog::~CalendarDialog(){
    delete(this->calendar);
    delete(this->cancelButton);
    delete(this->validateButton);
}


//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------
void CalendarDialog::initUI(){
    this->setWindowIcon(QIcon(":/resources/resourceFiles/logo.png"));
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Choisir une date");

    //calendrier
    this->calendar=new QCalendarWidget(this);

    //boutons
    this->cancelButton=new QPushButton("Annuler",this);
    this->validateButton=new QPushButton("Valider",this);

    //layouts
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QHBoxLayout * buttonLayout=new QHBoxLayout();

    buttonLayout->addWidget(this->cancelButton);
    buttonLayout->addWidget(this->validateButton);

    mainLayout->addWidget(this->calendar);
    mainLayout->addLayout(buttonLayout);
}

void CalendarDialog::initConnect(){
    QObject::connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(cancelCloseDialog()));
    QObject::connect(this->validateButton, SIGNAL(clicked()), this, SLOT(validateCloseDialog()));
}


QCalendarWidget * CalendarDialog::getCalendar(){
    return this->calendar;
}


//------------------------------------------------------------------------------------------------------------------------------
//slots
//------------------------------------------------------------------------------------------------------------------------------
void CalendarDialog::validateCloseDialog(){
    QDate * selectedDate=new QDate(this->calendar->selectedDate());
    emit emitClose(selectedDate);
    this->close();
}

void CalendarDialog::cancelCloseDialog(){
    emit emitClose(nullptr);
    this->close();
}
