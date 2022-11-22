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
    this->interactionCombobox->addItem("Pas d'interaction");
    this->addInteractionButton=new QPushButton("Ajouter une interaction");
    this->removeInteractionButton=new QPushButton("Supprimer l'interaction");
    this->removeInteractionButton->setEnabled(false);

    //layout
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QHBoxLayout * pictureLayout=new QHBoxLayout;
    QHBoxLayout * inputInteractionLayout=new QHBoxLayout;

    pictureLayout->addWidget(this->picture);
    pictureLayout->addWidget(this->modifyContactButton);

    inputInteractionLayout->addWidget(this->interactionCombobox);
    inputInteractionLayout->addWidget(this->addInteractionButton);
    inputInteractionLayout->addWidget(this->removeInteractionButton);

    mainLayout->addWidget(this->errorMessage);
    mainLayout->addLayout(pictureLayout);
    mainLayout->addWidget(this->infoContactLabel);
    mainLayout->addLayout(inputInteractionLayout);
}





void DetailsContactDialog::initConnect(){
    QObject::connect(this->modifyContactButton, SIGNAL(clicked()), this, SLOT(openModifyContactDialog()));

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
