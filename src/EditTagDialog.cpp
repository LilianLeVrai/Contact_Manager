/**
 * @file EditTagDialog.cpp
 * @brief Fichier cpp de la classe EditTagDialog
 */


#include "EditTagDialog.h"

#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>


//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
EditTagDialog::EditTagDialog(DatabaseCRUD * databaseCRUD, Interaction * interaction, QWidget *parent)//si on veut modifier une interaction
    : QDialog(parent)
{
    setModal(true);
    this->databaseCRUD=databaseCRUD;
    this->currentInteraction=interaction;
    this->date=nullptr;
    setWindowTitle("Éditer les tags");
    initUI();
    initConnect();
    fillTodo();
}


//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------
void EditTagDialog::initUI(){

    //selection todo
    this->todoCombobox=new QComboBox(this);
    this->todoCombobox->addItem("Ajouter tag");
    //suppression todo
    this->deleteTodoButton=new QPushButton("supprimer le tag");
    this->deleteTodoButton->setEnabled(false);

    //contenu de l'interaction
    this->contentEdit=new QLineEdit;
    this->contentEdit->setPlaceholderText("@todo (max 150 caractères)");
    this->dateButton=new QPushButton("@date");
    this->removeDateButton=new QPushButton("Effacer la date");
    this->removeDateButton->setEnabled(false);

    this->editTodoButton=new QPushButton("Ajouter tag");
    this->editTodoButton->setEnabled(false);

    this->listTagLabel=new QLabel;
    this->listTagLabel->setMinimumHeight(100);



    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QHBoxLayout * selectorLayout=new QHBoxLayout;
    QVBoxLayout * formLayout=new QVBoxLayout;
    QHBoxLayout * dateLayout=new QHBoxLayout;
    QVBoxLayout * topLayout=new QVBoxLayout;
    QHBoxLayout * labelLayout=new QHBoxLayout;

    selectorLayout->addWidget(this->todoCombobox);
    selectorLayout->addWidget(this->deleteTodoButton);

    dateLayout->addWidget(this->dateButton);
    dateLayout->addWidget(this->removeDateButton);

    formLayout->addWidget(this->contentEdit);
    formLayout->addLayout(dateLayout);

    topLayout->addLayout(selectorLayout);
    topLayout->addLayout(formLayout);
    topLayout->addWidget(this->editTodoButton);

    labelLayout->addWidget(this->listTagLabel);
    QGroupBox * group=new QGroupBox;
    group->setLayout(labelLayout);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(group);

    formLayout->setContentsMargins(0,20,0,20);
    this->listTagLabel->setAlignment(Qt::AlignTop);

    resize(800,250);
}

void EditTagDialog::initConnect(){
    QObject::connect(this->todoCombobox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateInputTodo()));
    QObject::connect(this->contentEdit, SIGNAL(textChanged(QString)), this, SLOT(updateEditTodoButton()));
    QObject::connect(this->deleteTodoButton, SIGNAL(clicked()), this, SLOT(deleteTodo()));
    QObject::connect(this->editTodoButton, SIGNAL(clicked()), this, SLOT(addModifyTodo()));
    QObject::connect(this->removeDateButton, SIGNAL(clicked()), this, SLOT(removeDate()));
    QObject::connect(this->dateButton, SIGNAL(clicked()), this, SLOT(openCalendarDialog()));
}


void EditTagDialog::fillTodo(){
    this->todoCombobox->clear();
    this->todoCombobox->addItem("Ajouter interaction");
    for(int i=0;i<this->currentInteraction->getListTodo()->getSize();i++)
        this->todoCombobox->addItem(this->currentInteraction->getListTodo()->getTodoByIndex(i)->getContent().c_str());
}


void EditTagDialog::checkUpdateInputTodo(){
    if(this->contentEdit->text().simplified().isEmpty())
        {this->editTodoButton->setEnabled(false);qDebug()<<"1";}
    else
        {qDebug()<<"2";
        if(this->todoCombobox->currentIndex()!=0 && this->contentEdit->text()==this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->getContent().c_str())
            {qDebug()<<"3";
            if(this->date==nullptr && this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->getDate()==nullptr)
                    {this->editTodoButton->setEnabled(false);qDebug()<<"4";}
            else
                {qDebug()<<"5";
                if(this->date!=nullptr && this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->getDate()!=nullptr && this->date->toString().compare(this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->getDate()->toString())==0 )
                   {this->editTodoButton->setEnabled(false);qDebug()<<"6";}
                else
                    {this->editTodoButton->setEnabled(true);qDebug()<<"7";}
                }
            }
        else
            {this->editTodoButton->setEnabled(true);qDebug()<<"8";}
        }

}

//------------------------------------------------------------------------------------------------------------------------------
//slots
//------------------------------------------------------------------------------------------------------------------------------
void EditTagDialog::updateInputTodo(){
    if(this->todoCombobox->currentIndex()!=-1)
        {
        if(this->todoCombobox->currentIndex()==0)
            {
            this->editTodoButton->setText("Ajouter tag");
            this->deleteTodoButton->setEnabled(false);
            this->editTodoButton->setEnabled(false);
            this->listTagLabel->setText(this->currentInteraction->toString().c_str());
            this->date=nullptr;
            this->dateButton->setText("@date");
            this->contentEdit->setText("");
            }
        else
            {
            this->editTodoButton->setText("Modifier tag");
            this->deleteTodoButton->setEnabled(true);
            this->editTodoButton->setEnabled(false);
            this->listTagLabel->setText(this->currentInteraction->toString().c_str());
            if(this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->getDate()==nullptr)
                {
                this->date=nullptr;
                this->dateButton->setText("@date");
                this->removeDateButton->setEnabled(false);
                }
            else
                {
                this->date=new Date(this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->getDate()->toString());
                this->dateButton->setText(this->date->toString().c_str());
                this->removeDateButton->setEnabled(true);
                }
            this->contentEdit->setText(this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->getContent().c_str());
            }
        }
}

void EditTagDialog::updateEditTodoButton(){
    this->checkUpdateInputTodo();
}

void EditTagDialog::deleteTodo(){
    this->databaseCRUD->deleteTagBDD(this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->getId());
    this->databaseCRUD->getTodoByInteraction(this->currentInteraction->getListTodo(),this->currentInteraction);
    this->fillTodo();
    emit emitUpdateTag();
}


void EditTagDialog::addModifyTodo(){
    if(this->todoCombobox->currentIndex()!=-1)
        {
        Todo * newTodo;
        if(this->todoCombobox->currentIndex()==0)
            {
            if (this->date==nullptr)
                newTodo=new Todo(this->contentEdit->text().toStdString(), nullptr);
            else
                newTodo=new Todo(this->contentEdit->text().toStdString(), this->date);
            this->databaseCRUD->addTagBDD(newTodo, this->currentInteraction);
            }
        else
            {
            if (this->date==nullptr)
                this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->setDate(nullptr);
            else
                this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->setDate(date);

            this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1)->setContent(this->contentEdit->text().toStdString());
            this->databaseCRUD->modifyTagBDD(this->currentInteraction->getListTodo()->getTodoByIndex(this->todoCombobox->currentIndex()-1));
            }
        this->databaseCRUD->getTodoByInteraction(this->currentInteraction->getListTodo(),this->currentInteraction);
        this->fillTodo();
        emit emitUpdateTag();
        this->dateButton->setText("@date");
        }
}


void EditTagDialog::openCalendarDialog(){
    this->calendarDialog=new CalendarDialog();
    QObject::connect(this->calendarDialog, SIGNAL(emitClose(QDate *)), this, SLOT(closeCalendarDialog(QDate *)));
    this->calendarDialog->show();
}



void EditTagDialog::closeCalendarDialog(QDate * date){
    if(date!=nullptr)
        {
        this->removeDateButton->setEnabled(true);
        this->date=new Date(date->day(), date->month(), date->year());
        this->dateButton->setText(this->date->toString().c_str());
        this->checkUpdateInputTodo();
        }
}

void EditTagDialog::removeDate(){
    this->removeDateButton->setEnabled(false);
    this->date=nullptr;
    this->dateButton->setText("@date");
    this->checkUpdateInputTodo();
}




