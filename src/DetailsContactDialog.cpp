/**
 * @file DetailsContactDialog.cpp
 * @brief Fichier cpp de la classe DetailsContactDialog
 */


#include "DetailsContactDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QPixmap>

#include <QDebug>


//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
DetailsContactDialog::DetailsContactDialog(Contact * contact,QWidget *parent)
    : QDialog(parent)
{
    this->contact=contact;

    initUI();
    initConnect();
    fillInfo();
}


DetailsContactDialog::~DetailsContactDialog(){};


//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------

void DetailsContactDialog::initUI(){

    setWindowTitle("Détails");

    //message pour erreur
    this->errorMessage=new MessageLabel("",MessageLabel::NoStyle, false);

    //label pour photo
    this->picture=new QLabel();
    this->picture->setFixedWidth(150);
    this->picture->setFixedHeight(150);
    //bouton modifier le contact
    this->modifyContactButton=new QPushButton("Modifier le contact");
    //info pour contact
    this->infoContactLabel=new QLabel();

    //inputs pour interaction
    this->interactionCombobox=new QComboBox;
    this->interactionCombobox->addItem("Ajouter interaction");
    this->removeInteractionButton=new QPushButton("Supprimer l'interaction");
    this->removeInteractionButton->setEnabled(false);
    this->editTagButton=new QPushButton("Éditer les tags");
    this->editTagButton->setEnabled(false);
    this->editInteraction=new QLineEdit;
    this->editInteraction->setPlaceholderText("contenu interaction");
    this->editInteractionButton=new QPushButton("Ajouter interaction");
    this->editInteractionButton->setEnabled(false);

    this->tagsLabel=new QLabel("@todo ejjejejejej\n@todo aahgahaha @date 12/12/12");


    //layout
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QHBoxLayout * pictureLayout=new QHBoxLayout;
    QVBoxLayout * infoLayout=new QVBoxLayout;
    QHBoxLayout * inputInteraction1Layout=new QHBoxLayout;
    QHBoxLayout * inputInteraction2Layout=new QHBoxLayout;
    pictureLayout->addWidget(this->picture);
    pictureLayout->addWidget(this->infoContactLabel);

    infoLayout->addWidget(this->errorMessage);
    infoLayout->addLayout(pictureLayout);
    infoLayout->addWidget(this->modifyContactButton);


    inputInteraction1Layout->addWidget(this->interactionCombobox);
    inputInteraction1Layout->addWidget(this->removeInteractionButton);
    inputInteraction1Layout->addWidget(this->editTagButton);
    inputInteraction2Layout->addWidget(this->editInteraction);
    inputInteraction2Layout->addWidget(this->editInteractionButton);


    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(inputInteraction1Layout);
    mainLayout->addLayout(inputInteraction2Layout);
    mainLayout->addWidget(tagsLabel);

    //propriétés d'alignement sur les layout et widget
    inputInteraction1Layout->setContentsMargins(0,40,0,0);
    infoLayout->setAlignment(Qt::AlignTop);
}





void DetailsContactDialog::initConnect(){
    QObject::connect(this->modifyContactButton, SIGNAL(clicked()), this, SLOT(openModifyContactDialog()));
    QObject::connect(this->editInteractionButton, SIGNAL(clicked()), this, SLOT(openCreateInteractionDialog()));
}


void DetailsContactDialog::fillInfo(){
    QImage image;
    if(image.load(this->contact->getPathPicture().c_str()))
        {
          image=image.scaledToWidth(this->picture->width(), Qt::SmoothTransformation);
          this->picture->setPixmap(QPixmap::fromImage(image));
          this->errorMessage->setProperty("",MessageLabel::NoStyle,false);
        }
    else
        {
        this->errorMessage->setProperty("Erreur pour charger l'image.",MessageLabel::Red,true);
        }

    this->infoContactLabel->setText(this->contact->toString().c_str());
}


//------------------------------------------------------------------------------------------------------------------------------
//slots
//------------------------------------------------------------------------------------------------------------------------------

void DetailsContactDialog::openModifyContactDialog(){
    this->modifyContactDialog=new EditContactDialog(this->contact);
    QObject::connect(this->modifyContactDialog, SIGNAL(emitClose(Contact*, bool)), this, SLOT(editContact(Contact*, bool)));
    this->modifyContactDialog->show();
}


void DetailsContactDialog::editContact(Contact * contact, bool error){
    this->contact->setLastName(contact->getLastName());
    this->contact->setFirstName(contact->getFirstName());
    this->contact->setCompany(contact->getCompany());
    this->contact->setMail(contact->getMail());
    this->contact->setPhone(contact->getPhone());
    this->contact->setPathPicture(contact->getPathPicture());
    this->fillInfo();
    emit emitModifyContact(contact, error);
}


void DetailsContactDialog::openCreateInteractionDialog(){
    this->editInteractionDialog=new EditInteractionDialog();
    //QObject::connect(this->modifyContactDialog, SIGNAL(emitClose(Contact*, bool)), this, SLOT(editContact(Contact*, bool)));
    this->editInteractionDialog->show();
}

