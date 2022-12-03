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
        Contact * currentContact;/**< contact concernée par les changements de tags */

        CalendarDialog * calendarDialog;/**< boite de dialogue pour sélectionner la date du tag */
        Date * date;/**< date du tag sélectionné */

    public:
        /**
         * @brief Constructeur.
         * @param pointeur vers objet Interaction représentant l'interaction dont on veut modifier les tags
         * @details
         * Défini la boîte de dialogue en mode bloquante, puis appel les méthodes 'initUI' et 'initConnect'.\n
         */
        EditTagDialog(DatabaseCRUD *, Interaction *, Contact *, QWidget *parent = 0);


        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, bouton, et autres propriétés).
         */
        void initUI();
        /**
         * @brief Permet d'initialiser les connect.
         */
        void initConnect();
        /**
         * @brief Permet de remplir la QCombobox des tags.
         */
        void fillTodo();
        /**
         * @brief Permet de vérifier les données remplis pour rendre accessible ou non le bouton 'ajouter/modifier'.
         */
        void checkUpdateInputTodo();

    public slots:
        /**
         * @brief slot mettant à jour les informations du tag, cela quand l'index de la QCombobox change.
         */
        void updateInputTodo();
        /**
         * @brief slot appelant la méthode 'checkUpdateInputTodo' quand le texte de la ligne d'édition du \@todo change.
         */
        void updateEditTodoButton();
        /**
         * @brief slot qui supprime le tag sélectionné dans la BDD, et appelle la méthode fillTodo. Cela quand le bouton 'supprimer' est cliqué.
         */
        void deleteTodo();
        /**
         * @brief slot qui ajoute ou modifie un tag dans la BDD. Cela quand le bouton 'ajouter/modifier' est cliqué.
         */
        void addModifyTodo();
        /**
         * @brief slot qui ouvre la fenêtre de dialogue pour sélectionner une date.
         */
        void openCalendarDialog();
        /**
         * @brief slot pour recevoir la date choisi pour le tag \@date.
         * @param pointeur sur un objet QDate
         */
        void closeCalendarDialog(QDate * date);
        /**
         * @brief slot supprimant la date du tag.
         */
        void removeDate();


    signals:
        /**
         * @brief signal.
         * @details
         * Dans notre programme le signal est envoyé à la boite de dialogue de détails du contact pour lui demander d'actualiser ses informations sur les tags.
         */
        void emitUpdateTag();


};

#endif // EDITTAGDIALOG_H
