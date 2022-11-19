/**
 * @file EditContactDialog.cpp
 * @brief Fichier cpp de la classe EditContactDialog
 */


#include "EditContactDialog.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>


//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
EditContactDialog::EditContactDialog(QWidget *parent)//si on veut créer un contact
    : QDialog(parent)
{
    setWindowTitle("Créer un contact");
    initUI();
    this->validateButton->setText("Créer");


}



EditContactDialog::EditContactDialog(Contact * contact, QWidget *parent)//si on veut modifier un contact
    : QDialog(parent)
{
    setWindowTitle("Modifier un contact");
    initUI();
    this->validateButton->setText("Modifier");



}




void EditContactDialog::initUI(){

    this->errorMessage=new MessageLabel("", MessageLabel::Red, false);

    QLabel * lastNameLabel=new QLabel("Nom :");
    this->lastNameEdit=new QLineEdit();
    QLabel * firstNameLabel=new QLabel("Prénom :");
    this->firstNameEdit=new QLineEdit();
    QLabel * companyLabel=new QLabel("Entreprise :");
    this->companyEdit=new QLineEdit();
    QLabel * mailLabel=new QLabel("Mail :");
    this->mailEdit=new QLineEdit();
    QLabel * phoneLabel=new QLabel("Téléphone :");
    this->phoneEdit=new QLineEdit();
    this->pictureButton=new QPushButton("Photo");
    this->pictureEdit=new QLineEdit();

    this->cancelButton=new QPushButton("Annuler");
    this->validateButton=new QPushButton();

    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QVBoxLayout * labelLayout=new QVBoxLayout;
    QVBoxLayout * textEditLayout=new QVBoxLayout;
    QHBoxLayout * formLayout=new QHBoxLayout;
    QHBoxLayout * buttonLayout=new QHBoxLayout;
    buttonLayout->setContentsMargins(0,20,0,0);

    labelLayout->addWidget(lastNameLabel);
    textEditLayout->addWidget(this->lastNameEdit);
    labelLayout->addWidget(firstNameLabel);
    textEditLayout->addWidget(this->firstNameEdit);
    labelLayout->addWidget(companyLabel);
    textEditLayout->addWidget(this->companyEdit);
    labelLayout->addWidget(mailLabel);
    textEditLayout->addWidget(this->mailEdit);
    labelLayout->addWidget(phoneLabel);
    textEditLayout->addWidget(this->phoneEdit);
    labelLayout->addWidget(this->pictureButton);
    textEditLayout->addWidget(this->pictureEdit);

    formLayout->addLayout(labelLayout);
    formLayout->addLayout(textEditLayout);

    buttonLayout->addWidget(this->cancelButton);
    buttonLayout->addWidget(this->validateButton);

    mainLayout->addWidget(this->errorMessage);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    resize(800,250);
}

void EditContactDialog::initConnect(){}
