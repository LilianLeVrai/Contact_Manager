#ifndef EDITINTERACTIONDIALOG_H
#define EDITINTERACTIONDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "Interaction.h"


class EditInteractionDialog : public QDialog
{
   Q_OBJECT

    private:

        QLineEdit * contentInteractionEdit;
        QComboBox * todoCombobox;
        QPushButton * deleteTodoButton;
        QPushButton * addTodoButton;
        QLineEdit * contentTodoEdit;
        QPushButton * dateTodoButton;

        QPushButton * cancelButton;
        QPushButton * validateButton;

        Interaction * currentInteraction;

    public:
        EditInteractionDialog(QWidget *parent = 0);
        EditInteractionDialog(Interaction *, QWidget *parent = 0);


        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, bouton, et autres propriétés).
         */
        void initUI();
        /**
         * @brief Permet d'initialiser les connect.
         */
        void initConnect();


};

#endif // EDITINTERACTIONDIALOG_H
