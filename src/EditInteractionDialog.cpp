#include "EditInteractionDialog.h"

#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>




EditInteractionDialog::EditInteractionDialog(QWidget *parent)//si on veut créer une interaction
    : QDialog(parent)
{
    setModal(true);
    this->currentInteraction=nullptr;
    setWindowTitle("Créer une interaction");
    initUI();

    this->validateButton->setText("Ajouter");

}





EditInteractionDialog::EditInteractionDialog(Interaction * interaction, QWidget *parent)//si on veut modifier une interaction
    : QDialog(parent)
{
    setModal(true);
    this->currentInteraction=interaction;
    setWindowTitle("Modifier une interaction");
    initUI();
    this->validateButton->setText("Modifier");
}



void EditInteractionDialog::initUI(){

    //contenu de l'interaction
    QLabel* interactionLabel=new QLabel("Interaction");

    this->contentInteractionEdit=new QLineEdit;
    this->contentInteractionEdit->setPlaceholderText("contenu");

    //selection todo
    this->todoCombobox=new QComboBox(this);
    this->todoCombobox->addItem("Pas de tag");
    //suppression todo
    this->deleteTodoButton=new QPushButton("supprimer le tag");

    QGroupBox * groupTodo=new QGroupBox(this);
    groupTodo->setTitle("Ajouter un tag");

    this->contentTodoEdit=new QLineEdit(this);
    this->contentTodoEdit->setPlaceholderText("@todo");
    this->dateTodoButton=new QPushButton("@date");
    this->addTodoButton=new QPushButton("Ajouter tag");
    this->addTodoButton->setEnabled(false);

    //bouton annuler et valider
    this->cancelButton=new QPushButton("Annuler");
    this->validateButton=new QPushButton("");
    this->validateButton->setEnabled(false);


    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QHBoxLayout * topLayout=new QHBoxLayout;
    QHBoxLayout * selectorTodoLayout=new QHBoxLayout;
    QVBoxLayout * editTodoLayout=new QVBoxLayout;
    QVBoxLayout * midLayout=new QVBoxLayout;
    QHBoxLayout * bottomLayout=new QHBoxLayout;

    topLayout->addWidget(interactionLabel);
    topLayout->addWidget(this->contentInteractionEdit);

    selectorTodoLayout->addWidget(this->todoCombobox);
    selectorTodoLayout->addWidget(this->deleteTodoButton);

    editTodoLayout->addWidget(this->contentTodoEdit);
    editTodoLayout->addWidget(this->dateTodoButton);

    midLayout->addLayout(editTodoLayout);
    midLayout->addWidget(this->addTodoButton);

    bottomLayout->addWidget(this->cancelButton);
    bottomLayout->addWidget(this->validateButton);



    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(selectorTodoLayout);
    groupTodo->setLayout(midLayout);
    mainLayout->addWidget(groupTodo);
    mainLayout->addLayout(bottomLayout);


    editTodoLayout->setAlignment(Qt::AlignTop);
    selectorTodoLayout->setContentsMargins(0,40,0,0);
    editTodoLayout->setContentsMargins(0,0,0,20);
    bottomLayout->setContentsMargins(0,40,0,0);

    resize(800,250);
}

void EditInteractionDialog::initConnect(){}
