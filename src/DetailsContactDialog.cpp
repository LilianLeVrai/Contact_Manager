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
#include <QPainter>


//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
DetailsContactDialog::DetailsContactDialog(DatabaseCRUD * databaseCRUD,Contact * contact,QWidget *parent)
    : QDialog(parent)
{
    this->databaseCRUD=databaseCRUD;
    this->contact=contact;
    this->databaseCRUD->getInteractionByContact(&this->listInteraction, this->contact);

    initUI();
    initConnect();
    fillInfo();
    fillInteraction();
}


DetailsContactDialog::~DetailsContactDialog(){
    delete(this->errorMessage);
    delete(this->picture);
    delete(this->modifyContactButton);
    delete(this->infoContactLabel);

    delete(this->interactionCombobox);
    delete(this->removeInteractionButton);
    delete(this->editTagButton);
    delete(this->editInteraction);
    delete(this->editInteractionButton);
    delete(this->tagsLabel);
    delete(this->printModificationsButton);

    delete(this->modifyContactDialog);
    delete(this->editTagDialog);
    delete(this->modificationsWindow);
}


//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------

void DetailsContactDialog::initUI(){

    this->setWindowIcon(QIcon(":/resources/resourceFiles/logo.png"));
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Détails");

    //message pour erreur
    this->errorMessage=new MessageLabel("",MessageLabel::NoStyle, false);

    //label pour photo
    this->picture=new QLabel(this);
    this->picture->setObjectName("picture");
    this->picture->setFixedWidth(150);
    this->picture->setFixedHeight(150);
    //bouton modifier le contact
    this->modifyContactButton=new QPushButton("Modifier le contact",this);
    this->modifyContactButton->setObjectName("modifyContactButton");
    //bouton pour afficher les modifications du contact
    this->printModificationsButton=new QPushButton("Afficher les modifications",this);
    //info pour contact
    this->infoContactLabel=new QLabel(this);
    this->infoContactLabel->setObjectName("infoContactLabel");

    //inputs pour interaction
    this->interactionCombobox=new QComboBox(this);
    this->interactionCombobox->setObjectName("interactionCombobox");
    this->removeInteractionButton=new QPushButton("Supprimer l'interaction",this);
    this->removeInteractionButton->setObjectName("deleteInteractionButton");
    this->removeInteractionButton->setEnabled(false);
    this->editTagButton=new QPushButton("Éditer les tags",this);
    this->editTagButton->setObjectName("openEditTagButton");
    this->editTagButton->setEnabled(false);
    this->editInteraction=new QLineEdit(this);
    this->editInteraction->setObjectName("editInteractionLine");
    this->editInteraction->setStyleSheet("color: #a8aaac;");
    this->editInteraction->setPlaceholderText("contenu interaction (max 150 caractères)");
    this->editInteraction->setMaxLength(150);
    this->editInteractionButton=new QPushButton("Ajouter l'interaction",this);
    this->editInteractionButton->setObjectName("editInteractionButton");
    this->editInteractionButton->setEnabled(false);

    this->tagsLabel=new QLabel(this);
    this->tagsLabel->setMinimumHeight(100);
    this->tagsLabel->setAlignment(Qt::AlignTop);


    //layout
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QHBoxLayout * pictureLayout=new QHBoxLayout;
    QVBoxLayout * infoLayout=new QVBoxLayout;
    QHBoxLayout * inputInteraction1Layout=new QHBoxLayout;
    QHBoxLayout * inputInteraction2Layout=new QHBoxLayout;
    QVBoxLayout * interactionLayout=new QVBoxLayout;

    pictureLayout->addWidget(this->picture);
    pictureLayout->addWidget(this->infoContactLabel);
    pictureLayout->setContentsMargins(0,0,0,15);
    pictureLayout->setSpacing(20);

    infoLayout->addWidget(this->errorMessage);
    infoLayout->addLayout(pictureLayout);
    infoLayout->addWidget(this->modifyContactButton);
    infoLayout->addWidget(this->printModificationsButton);
    infoLayout->setContentsMargins(40,40,40,30);
    QWidget * topWidget=new QWidget();
    topWidget->setObjectName("topWidgetDetailsDialog");
    topWidget->setLayout(infoLayout);

    inputInteraction1Layout->addWidget(this->interactionCombobox);
    inputInteraction1Layout->addWidget(this->removeInteractionButton);
    inputInteraction1Layout->addWidget(this->editTagButton);
    inputInteraction1Layout->setSpacing(0);
    inputInteraction2Layout->addWidget(this->editInteraction);
    inputInteraction2Layout->addWidget(this->editInteractionButton);
    inputInteraction2Layout->setSpacing(0);

    interactionLayout->addLayout(inputInteraction1Layout);
    interactionLayout->addLayout(inputInteraction2Layout);
    interactionLayout->addWidget(tagsLabel);
    interactionLayout->setContentsMargins(40,30,40,40);
    interactionLayout->setSpacing(10);

    mainLayout->addWidget(topWidget);
    mainLayout->addLayout(interactionLayout);
    mainLayout->setContentsMargins(0,0,0,0);

    //propriétés d'alignement sur les layout et widget
    mainLayout->setAlignment(Qt::AlignTop);
    infoLayout->setAlignment(Qt::AlignTop);
}





void DetailsContactDialog::initConnect(){
    QObject::connect(this->modifyContactButton, SIGNAL(clicked()), this, SLOT(openModifyContactDialog()));
    QObject::connect(this->editTagButton, SIGNAL(clicked()), this, SLOT(openEditTagDialog()));
    QObject::connect(this->interactionCombobox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateInputInteraction()));
    QObject::connect(this->editInteraction, SIGNAL(textChanged(QString)), this, SLOT(updateEditInteractionButton()));
    QObject::connect(this->removeInteractionButton, SIGNAL(clicked()), this, SLOT(removeInteraction()));
    QObject::connect(this->editInteractionButton, SIGNAL(clicked()), this, SLOT(addModifyInteraction()));
    QObject::connect(this->printModificationsButton, SIGNAL(clicked()), this, SLOT(printModifications()));
}


void DetailsContactDialog::fillInfo(){
    QImage image;
    if(image.load(this->contact->getPathPicture().c_str()))
        {
        this->errorMessage->setProperty("",MessageLabel::NoStyle,false);
        image=image.scaledToWidth(this->picture->width(), Qt::SmoothTransformation);
        this->picture->setPixmap(QPixmap::fromImage(image));
        }
    else
        {
        this->errorMessage->setProperty("Erreur pour charger l'image.",MessageLabel::Red,true);
        }

    this->infoContactLabel->setText(this->contact->toString().c_str());
}

void DetailsContactDialog::fillInteraction(){
    this->interactionCombobox->clear();
    this->interactionCombobox->addItem("Ajouter interaction");
    for(int i=0;i<this->listInteraction.getSize();i++)
        this->interactionCombobox->addItem(this->listInteraction.getInteractionByIndex(i)->getContent().c_str());
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


void DetailsContactDialog::openEditTagDialog(){
    this->editTagDialog=new EditTagDialog(this->databaseCRUD, this->listInteraction.getInteractionByIndex(this->interactionCombobox->currentIndex()-1), this->contact);
    QObject::connect(this->editTagDialog, SIGNAL(emitUpdateTag()), this, SLOT(updateTag()));
    this->editTagDialog->show();
}

void DetailsContactDialog::updateInputInteraction(){
    if(this->interactionCombobox->currentIndex()!=-1)
        {
        if(this->interactionCombobox->currentIndex()==0)
            {
            this->editInteractionButton->setText("Ajouter interaction");
            this->removeInteractionButton->setEnabled(false);
            this->editTagButton->setEnabled(false);
            this->editInteraction->setText("");

            this->tagsLabel->setText("");
            }
        else
            {
            this->editInteractionButton->setText("Modifier l'interaction");
            this->removeInteractionButton->setEnabled(true);
            this->editTagButton->setEnabled(true);
            this->editInteraction->setText(this->listInteraction.getInteractionByIndex(this->interactionCombobox->currentIndex()-1)->getContent().c_str());

            this->tagsLabel->setText(this->listInteraction.getInteractionByIndex(((this->interactionCombobox->currentIndex())-1))->getListTodo()->toString().c_str());
            }
        }
}

void DetailsContactDialog::updateEditInteractionButton(){
    if(this->editInteraction->text().simplified().isEmpty() ||
            (this->interactionCombobox->currentIndex()!=0 && this->editInteraction->text()==this->listInteraction.getInteractionByIndex(this->interactionCombobox->currentIndex()-1)->getContent().c_str()))
        {
        this->editInteractionButton->setEnabled(false);
        this->editInteraction->setStyleSheet("border-color: #f0f2f5;");
        if(this->editInteraction->text().simplified().isEmpty())
            {this->editInteraction->setStyleSheet("color: #a8aaac;");}
        else
            {this->editInteraction->setStyleSheet("color: #373353;");}
        }
    else
        {
        this->editInteractionButton->setEnabled(true);
        this->editInteraction->setStyleSheet("border-color: #e5e7ea;");
        }
}

void DetailsContactDialog::removeInteraction(){
    this->databaseCRUD->deleteInteractionBDD(this->listInteraction.getInteractionByIndex(this->interactionCombobox->currentIndex()-1), this->contact);
    this->databaseCRUD->getInteractionByContact(&this->listInteraction,this->contact);
    this->fillInteraction();
}


void DetailsContactDialog::addModifyInteraction(){
    if(this->interactionCombobox->currentIndex()!=-1)
        {
        if(this->interactionCombobox->currentIndex()==0)
            {
            Interaction * newInteraction=new Interaction(this->editInteraction->text().simplified().toStdString());
            this->databaseCRUD->addInteractionBDD(newInteraction, this->contact);
            }
        else
            {
            this->listInteraction.getInteractionByIndex(this->interactionCombobox->currentIndex()-1)->setContent(this->editInteraction->text().simplified().toStdString());
            this->databaseCRUD->modifyInteractionBDD(this->listInteraction.getInteractionByIndex(this->interactionCombobox->currentIndex()-1), this->contact);
            }
        this->databaseCRUD->getInteractionByContact(&this->listInteraction,this->contact);
        this->fillInteraction();
        }
}


void DetailsContactDialog::updateTag(){
    this->tagsLabel->setText(this->listInteraction.getInteractionByIndex(((this->interactionCombobox->currentIndex())-1))->getListTodo()->toString().c_str());
}

void DetailsContactDialog::printModifications(){
    this->modificationsWindow=new ModificationsWindow(this->contact, this->databaseCRUD, this->parentWidget());
    this->modificationsWindow->show();
}

