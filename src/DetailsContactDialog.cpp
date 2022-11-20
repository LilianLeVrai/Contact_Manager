#include "DetailsContactDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
DetailsContactDialog::DetailsContactDialog(Contact * contact,QWidget *parent)
    : QDialog(parent)
{
    this->contact=contact;

    initUI();
    initConnect();
}


DetailsContactDialog::~DetailsContactDialog(){};


//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------

void DetailsContactDialog::initUI(){
    this->picture=new QLabel();
    this->modifyButton=new QPushButton("Modifier le contact");

    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QHBoxLayout * pictureLayout=new QHBoxLayout;

    pictureLayout->addWidget(this->picture);
    pictureLayout->addWidget(this->modifyButton);

    mainLayout->addLayout(pictureLayout);
}





void DetailsContactDialog::initConnect(){}


void DetailsContactDialog::fillInfo(){}


//------------------------------------------------------------------------------------------------------------------------------
//slots
//------------------------------------------------------------------------------------------------------------------------------
