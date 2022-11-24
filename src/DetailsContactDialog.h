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

#include "MessageLabel.h"
#include "EditContactDialog.h"
#include "EditInteractionDialog.h"
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
        Contact * contact;/**< contact concerné par la fenêtre */
        ListInteraction * listInteraction;

        MessageLabel * errorMessage;/**< message d'erreur (utilisé pour un problème sur l'image) */
        QLabel * picture;/**< champ pour afficher l'image */
        QPushButton * modifyContactButton;/**< bouton pour modifier le contact */

        QLabel * infoContactLabel;/**< label pour afficher les informations du contact */
        QComboBox * interactionCombobox;/**< sélecteur d'interaction */
        QPushButton * addInteractionButton;/**< bouton pour ajouter une interaction */
        QPushButton * modifyInteractionButton;/**< bouton pour modifier l'interaction sélectionné */
        QPushButton * removeInteractionButton;/**< bouton pour supprimer l'interaction sélectionnée */

        EditContactDialog * modifyContactDialog;/**< boite de dialogue pour modifier le contact */
        EditInteractionDialog * editInteractionDialog;


    public:
        /**
         * @brief Constructeur.
         * @param pointeur vers objet Contact représentant le contact concerné par la fenêtre
         * @details
         * Défini la boîte de dialogue en mode bloquante, puis appel les méthodes 'initUI' et 'initConnect'.\n
         * De plus appel la méthode 'fillInfo' qui affiche l'image et les infos du contact.
         */
        DetailsContactDialog(Contact *,QWidget *parent = 0);
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
         * @brief slot ouvrant une fenêtre de dialogue pour créer l'interaction.
         */
        void openCreateInteractionDialog();

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
