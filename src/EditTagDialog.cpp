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




EditTagDialog::EditTagDialog(QWidget *parent)//si on veut créer une interaction
    : QDialog(parent)
{
    setModal(true);
    this->currentInteraction=nullptr;
    setWindowTitle("Éditer les tags");
    initUI();

}





EditTagDialog::EditTagDialog(Interaction * interaction, QWidget *parent)//si on veut modifier une interaction
    : QDialog(parent)
{
    setModal(true);
    this->currentInteraction=interaction;
    setWindowTitle("Éditer les tags");
    initUI();
}



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

    this->listTagLabel=new QLabel("@todo egvage\n@todo ehuagaegjg @date 00/00/0000");
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

void EditTagDialog::initConnect(){}
