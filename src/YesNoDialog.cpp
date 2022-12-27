/**
 * @file YesNoDialog.cpp
 * @brief Fichier cpp de la classe YesNoDialog
 */


#include "YesNoDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
YesNoDialog::YesNoDialog(QString title, QString question,QWidget *parent)
    : QDialog(parent)
{
    setModal(true);
    initUI(title, question);
    initConnect();
}

YesNoDialog::~YesNoDialog(){
    delete(this->yesButton);
    delete(this->noButton);
}

//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------
void YesNoDialog::initUI(QString title, QString question){

    this->setWindowIcon(QIcon(":/resources/resourceFiles/logo.png"));
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(title);

    //label
    QLabel * questionLabel=new QLabel(question);

    //boutons
    this->noButton=new QPushButton("Non",this);
    this->yesButton=new QPushButton("Oui",this);
    this->yesButton->setObjectName("yesButton");

    //layouts
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QHBoxLayout * buttonLayout=new QHBoxLayout();

    buttonLayout->addWidget(this->noButton);
    buttonLayout->addWidget(this->yesButton);
    buttonLayout->setContentsMargins(0,30,0,0);

    mainLayout->addWidget(questionLabel);
    mainLayout->addLayout(buttonLayout);

    layout()->setSizeConstraint(QLayout::SetFixedSize);
}


void YesNoDialog::initConnect(){
    QObject::connect(this->noButton, SIGNAL(clicked()), this, SLOT(noCloseDialog()));
    QObject::connect(this->yesButton, SIGNAL(clicked()), this, SLOT(yesCloseDialog()));
}


//------------------------------------------------------------------------------------------------------------------------------
//slots
//------------------------------------------------------------------------------------------------------------------------------
void YesNoDialog::noCloseDialog(){emit emitClose(false);this->close();}
void YesNoDialog::yesCloseDialog(){emit emitClose(true);this->close();}
