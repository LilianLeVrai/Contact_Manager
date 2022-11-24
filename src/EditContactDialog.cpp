/**
 * @file EditContactDialog.cpp
 * @brief Fichier cpp de la classe EditContactDialog
 */


#include "EditContactDialog.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileInfo>


//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
EditContactDialog::EditContactDialog(QWidget *parent)//si on veut créer un contact
    : QDialog(parent)
{
    setModal(true);
    this->currentContact=nullptr;
    setWindowTitle("Créer un contact");
    initUI();
    this->validateButton->setText("Créer");
    initConnect();
}



EditContactDialog::EditContactDialog(Contact * contact, QWidget *parent)//si on veut modifier un contact
    : QDialog(parent)
{
    setModal(true);
    this->currentContact=contact;
    setWindowTitle("Modifier un contact");
    initUI();
    this->validateButton->setText("Modifier");

    this->lastNameEdit->setText(contact->getLastName().c_str());
    this->firstNameEdit->setText(contact->getFirstName().c_str());
    this->companyEdit->setText(contact->getCompany().c_str());
    this->mailEdit->setText(contact->getMail().c_str());
    this->phoneEdit->setText(contact->getPhone().c_str());
    this->pictureEdit->setText(contact->getPathPicture().c_str());


    initConnect();
}

EditContactDialog::~EditContactDialog(){}


//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------
void EditContactDialog::initUI(){

    this->errorMessage=new MessageLabel("", MessageLabel::NoStyle, true);

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
    this->pictureEdit->setPlaceholderText(".jpg ou .jpeg ou .png");

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

    formLayout->setAlignment(Qt::AlignTop);
    buttonLayout->setAlignment(Qt::AlignBottom);

    resize(800,250);
}

void EditContactDialog::initConnect(){
    QObject::connect(this->pictureButton, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    QObject::connect(this->validateButton, SIGNAL(clicked()), this, SLOT(editContact()));
    QObject::connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->pictureEdit, SIGNAL(textChanged(QString)), this, SLOT(checkPathPicture()));
}

bool EditContactDialog::checkData(){
    this->errorMessage->setProperty("",MessageLabel::NoStyle,true);
    bool validData=true;

    if(this->phoneEdit->text().simplified().isEmpty() || this->phoneEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le téléphone n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->phoneEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le numéro de téléphone est trop long",MessageLabel::Red,true);validData=false;}
    if(this->mailEdit->text().simplified().isEmpty() || this->mailEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le mail n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->mailEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le mail est trop long",MessageLabel::Red,true);validData=false;}
    if(this->companyEdit->text().simplified().isEmpty() || this->companyEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("L'entreprise n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->companyEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le nom de l'entreprise est trop long",MessageLabel::Red,true);validData=false;}
    if(this->firstNameEdit->text().simplified().isEmpty() || this->firstNameEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le prénom n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->firstNameEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le prénom est trop long",MessageLabel::Red,true);validData=false;}
    if(this->lastNameEdit->text().simplified().isEmpty() || this->lastNameEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le nom n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->lastNameEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le nom est trop long",MessageLabel::Red,true);validData=false;}

    //Entreprise, numéro et email peuvent être vide ? (Si oui, bdd à modifier)



    return validData;
}

//------------------------------------------------------------------------------------------------------------------------------
//slots
//------------------------------------------------------------------------------------------------------------------------------

void EditContactDialog::openFileDialog(){
    QString pathPicture;
    QFileDialog fileDialog;
    pathPicture=fileDialog.getOpenFileName(this, "Choisir une image (.png ou .jpg ou.jpeg)","","Images (*.png *.jpg *jpeg)");
    this->pictureEdit->setText(pathPicture);
}



void EditContactDialog::editContact(){
    if(this->checkData())
        {

        //verification du chemin d'image et mise à défaut si besoin
        bool errorImg=false;
        QString pathPicture=this->pictureEdit->text().simplified();
        QFileInfo ext(pathPicture);
        if(this->currentContact==nullptr || (this->currentContact!=nullptr && this->currentContact->getPathPicture().c_str()!=pathPicture))
            {
            if(QFile::exists(pathPicture) && (ext.suffix()=="jpg" || ext.suffix()=="jpeg" || ext.suffix()=="png" ))
                {
                QDir directory("../img");
                QString newPathPicture="../img/img_"+QString::number(directory.count())+"."+ext.suffix();
                QFile::copy(pathPicture, newPathPicture);
                pathPicture=newPathPicture;
                }
            else {pathPicture="../img/defaultImg.jpg";errorImg=true;}
            }


        if(this->currentContact!=nullptr)
            {
            this->currentContact->setLastName(this->lastNameEdit->text().toStdString());
            this->currentContact->setFirstName(this->firstNameEdit->text().toStdString());
            this->currentContact->setCompany(this->companyEdit->text().toStdString());
            this->currentContact->setMail(this->mailEdit->text().toStdString());
            this->currentContact->setPhone(this->phoneEdit->text().toStdString());
            this->currentContact->setPathPicture(pathPicture.toStdString());

            emit emitClose(this->currentContact, errorImg);
            }
        if(this->currentContact==nullptr)
            {
            this->currentContact=new Contact(this->lastNameEdit->text().toStdString(),
                                             this->firstNameEdit->text().toStdString(),
                                             this->companyEdit->text().toStdString(),
                                             this->mailEdit->text().toStdString(),
                                             this->phoneEdit->text().toStdString(),
                                             pathPicture.toStdString());
            this->currentContact->setId(-1);
            emit emitClose(this->currentContact, errorImg);
            }
        this->close();
        }
}

void EditContactDialog::checkPathPicture(){
    QString pathPicture=this->pictureEdit->text().simplified();
    QFileInfo ext(pathPicture);
    if(QFile::exists(pathPicture) && (ext.suffix()=="jpg" || ext.suffix()=="jpeg" || ext.suffix()=="png" ))
       this->errorMessage->setProperty("",MessageLabel::NoStyle,true);
    else
       this->errorMessage->setProperty("Le lien et/ou l'extension de l'image ne sont pas corrects",MessageLabel::Red,true);

}
