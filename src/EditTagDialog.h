#ifndef EDITTAGDIALOG_H
#define EDITTAGDIALOG_H

/**
 * @file EditTagDialog.h
 * @brief Fichier header de la classe EditTagDialog
 */


#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

#include "Interaction.h"
#include "DatabaseCRUD.h"
#include "CalendarDialog.h"

/**
 * @class EditTagDialog
 * @brief classe représentant l'interface de la boîte de dialogue pour éditer les tags
 * @details La classe hérite de la classe QDialog.
 */
class EditTagDialog : public QDialog
{
   Q_OBJECT

    private:
        QComboBox * todoCombobox;/**< selecteur de tag */
        QPushButton * deleteTodoButton;/**< bouton pour supprimer le tag sélectionné */
        QLineEdit * contentEdit;/**< champ pour rentrer le contenu du tag */
        QPushButton * dateButton;/**< bouton pour sélectionner une date */
        QPushButton * removeDateButton;/**< bouton pour supprimer le tag \@date */
        QPushButton * editTodoButton;/**< bouton pour ajouter ou modifier le tag */
        QLabel * listTagLabel;/**< champ pour afficher tous les tag de l'interaction */

        DatabaseCRUD * databaseCRUD;/**< gestionnaire de la BDD */
        Interaction * currentInteraction;/**< interaction concernée par les changements de tags */

        CalendarDialog * calendarDialog;/**< boite de dialogue pour sélectionner la date du tag*/
        Date * date;

    public:
        /**
         * @brief Constructeur.
         * @param pointeur vers objet Interaction représentant l'interaction dont on veut modifier les tags
         * @details
         * Défini la boîte de dialogue en mode bloquante, puis appel les méthodes 'initUI' et 'initConnect'.\n
         */
        EditTagDialog(DatabaseCRUD *, Interaction *, QWidget *parent = 0);


        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, bouton, et autres propriétés).
         */
        void initUI();
        /**
         * @brief Permet d'initialiser les connect.
         */
        void initConnect();

        void fillTodo();

        void checkUpdateInputTodo();

    public slots:
        void updateInputTodo();
        void updateEditTodoButton();
        void deleteTodo();
        void addModifyTodo();
        void openCalendarDialog();
        void closeCalendarDialog(QDate * date);
        void removeDate();


    signals:
        void emitUpdateTag();


};

#endif // EDITTAGDIALOG_H
