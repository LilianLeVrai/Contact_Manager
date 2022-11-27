#ifndef DETAILSCONTACTDIALOG_H
#define DETAILSCONTACTDIALOG_H

/**
 * @file DetailsContactDialog.h
 * @brief Fichier header de la classe DetailsContactDialog
 */


#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

#include "DatabaseCRUD.h"
#include "MessageLabel.h"
#include "EditContactDialog.h"
#include "EditTagDialog.h"
#include "Contact.h"

/**
 * @class DetailsContactDialog
 * @brief classe représentant l'interface de la boîte de dialogue pour voir les détails d'un contact
 * @details La classe hérite de la classe QDialog.
 */
class DetailsContactDialog : public QDialog
{
    Q_OBJECT

    private:
        DatabaseCRUD * databaseCRUD;/**< gestionnaire de la BDD */
        Contact * contact;/**< contact concerné par la fenêtre */
        ListInteraction listInteraction;/** liste d'interaction du contact */

        MessageLabel * errorMessage;/**< message d'erreur (utilisé pour un problème sur l'image) */
        QLabel * picture;/**< champ pour afficher l'image */
        QPushButton * modifyContactButton;/**< bouton pour modifier le contact */
        QLabel * infoContactLabel;/**< label pour afficher les informations du contact */

        QComboBox * interactionCombobox;/**< sélecteur d'interaction */
        QPushButton * removeInteractionButton;/**< bouton pour supprimer l'interaction sélectionnée */
        QPushButton * editTagButton;/**< bouton pour gérer les tags */
        QLineEdit * editInteraction;/**< permet d'afficher et modifier le contenu de l'interaction */
        QPushButton * editInteractionButton;/**< bouton pour ajouter ou modifier interaction */
        QLabel * tagsLabel;/**< permet d'afficher les tags de l'interaction sélectionné  */


        EditContactDialog * modifyContactDialog;/**< boite de dialogue pour modifier le contact */
        EditTagDialog * editTagDialog;/**< boite de dialogue pour éditer les tags */


    public:
        /**
         * @brief Constructeur.
         * @param pointeur vers objet Contact représentant le contact concerné par la fenêtre
         * @details
         * Défini la boîte de dialogue en mode bloquante, puis appel les méthodes 'initUI' et 'initConnect'.\n
         * De plus appel la méthode 'fillInfo' qui affiche l'image et les infos du contact.
         */
        DetailsContactDialog(DatabaseCRUD *, Contact *,QWidget *parent = 0);
        ~DetailsContactDialog();

        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, bouton, et autres propriétés).
         */
        void initUI();
        /**
         * @brief Permet d'initialiser les connect.
         */
        void initConnect();
        /**
         * @brief Permet d'afficher l'image et les infos du contact.
         */
        void fillInfo();
        /**
         * @brief Permet de remplir la selection d'interaction.
         */
        void fillInteraction();


    public slots:
        /**
         * @brief slot ouvrant une fenêtre de dialogue pour modifier le contact.
         */
        void openModifyContactDialog();
        /**
         * @brief slot permettant le changement d'information dans la fenêtre courante et la fenêtre principal.
         * @details
         * Ce slot est activé quand le contact a été modifié par la fenêtre de dialogue d'édition de contact.
         * Ce slot attribut à l'attribut 'currentContact' les nouvelles informations, appelle la méthode 'fillInfo',
         * et emmet le signal 'emitModifyContact', avec en paramêtre le contact, et un booleen en fonction de la présence d'erreur.
         */
        void editContact(Contact*, bool);

        /**
         * @brief slot ouvrant une fenêtre de dialogue pour modifier les tags de l'interaction sélectionné.
         */
        void openEditTagDialog();
        /**
         * @brief slot qui rempli le champ et active ou desésactive les boutons en fonction de l'interaction sélectionnée.
         */
        void updateInputInteraction();
        /**
         * @brief slot qui active ou désactive le bouton d'ajout/modification en fonction de si le champ est rempli et a été modifié.
         */
        void updateEditInteractionButton();
        /**
         * @brief slot supprimant l'interaction sélectionné.
         * @details Fait une requète à la BDD grâce à l'attribut 'databaseCRUD'.
         */
        void removeInteraction();
        /**
         * @brief slot ajoutant ou modifiant l'interaction.
         * @details Fait une requète à la BDD grâce à l'attribut 'databaseCRUD'.
         */
        void addModifyInteraction();


        void updateTag();

    signals:
        /**
         * @brief signal.
         * @param pointeur vers objet Contact
         * @param booleen
         * @details
         * Permettra de récupérer le contact modifier par l'utilisateur dans le 'MainWidget',
         * c'est depuis celui-ci que les modifications sont inscrit dans la BDD.
         */
        void emitModifyContact(Contact*, bool);
};

#endif // DETAILSCONTACTDIALOG_H
