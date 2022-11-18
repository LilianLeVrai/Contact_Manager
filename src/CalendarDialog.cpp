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

CalendarDialog::~CalendarDialog(){};


//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------
void CalendarDialog::initUI(){
    setWindowTitle("Choisir une date");

    //calendrier
    this->calendar=new QCalendarWidget(this);
    QDate currentDate=currentDate.currentDate();
    this->calendar->setMaximumDate(currentDate);

    //boutons
    this->cancelButton=new QPushButton("Annuler");
    this->validateButton=new QPushButton("Valider");

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
