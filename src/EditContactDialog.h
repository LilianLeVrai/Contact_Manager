#ifndef EDITCONTACTDIALOG_H
#define EDITCONTACTDIALOG_H

/**
 * @file EditContactDialog.h
 * @brief Fichier header de la classe EditContactDialog
 */


#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QObject>

#include "Contact.h"
#include "MessageLabel.h"

/**
 * @class EditContactDialog
 * @brief classe représentant l'interface de la boîte de dialogue pour éditer un contact (création et modification)
 * @details La classe hérite de la classe QDialog.
 */
class EditContactDialog : public QDialog
{
    Q_OBJECT

    private:
        MessageLabel * errorMessage;/**< message d'erreur (champs non remplis, format de mail incorrect,...)  */
        QLineEdit * lastNameEdit;/**< champ pour rentrer le nom */
        QLineEdit * firstNameEdit;/**< champ pour rentrer le prénom */
        QLineEdit * companyEdit;/**< champ pour rentrer l'entreprise */
        QLineEdit * mailEdit;/**< champ pour rentrer le mail */
        QLineEdit * phoneEdit;/**< champ pour rentrer le téléphone */
        QPushButton * pictureButton;/**< bouton pour ouvrir une fenêtre de dialogue 'QFileDialog' */
        QLineEdit * pictureEdit;/**< champ pour rentrer le lien de l'image */
        QPushButton * cancelButton;/**< bouton pour annuler */
        QPushButton * validateButton;/**< bouton pour valider (création ou modification) */

        Contact * currentContact;/**< contact à modifier, pouvant être 'nullptr' si création d'un nouveau contact */

    public:
        /**
         * @brief Constructeur sans paramêtre (à utiliser pour la création d'un nouveau contact).
         * @details
         * Défini la boîte de dialogue en mode bloquante, puis appel les méthodes communes à la création et la modification 'initUI' et 'initConnect'.\n
         * De plus fais des actions propre à la fenêtre de création, comme le titre de la page, etc...
         */
        EditContactDialog(QWidget *parent = 0);
        /**
         * @brief Constructeur avec paramêtre (à utiliser pour la modification d'un contact existant).
         * @param pointeur vers objet Contact représentant le contact à modifier
         * @details
         * Défini la boîte de dialogue en mode bloquante, puis appel les méthodes communes à la création et la modification 'initUI' et 'initConnect'.\n
         * De plus fais des actions propre à la fenêtre de modification, comme remplir les champs avec les informations connus du contact, le titre de la page, etc...
         */
        EditContactDialog(Contact *, QWidget *parent = 0);
        ~EditContactDialog();

        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, bouton, et autres propriétés).
         */
        void initUI();
        /**
         * @brief Permet d'initialiser les connect.
         */
        void initConnect();

        /**
         * @brief Vérifie que les informations sont biens remplis.
         */
        bool checkData();

    public slots:
        /**
         * @brief slot ouvrant une fenêtre pour choisir une image, et mettant le lien dans la ligne d'édition correspondante.
         * @details
         * Ce slot est activé quand le bouton 'Photo' est clické.
         */
        void openFileDialog();
        /**
         * @brief slot emmetant le signal 'emitClose', avec en paramêtre le contact, et un booleen en fonction de la présence d'erreur.
         * @details
         * Ce slot est activé quand le bouton 'Valider' est clické.
         */
        void editContact();
        /**
         * @brief slot vérifiant que le lien d'image renseigné est bien valide, et affiche un message d'erreur si ce n'est pas le cas.
         * @details
         * Ce slot est activé quand le texte dans la ligne d'édition du lien d'image est changé.
         */
        void checkPathPicture();


    signals:
        /**
         * @brief signal.
         * @param pointeur vers objet Contact
         * @param booleen
         * @details
         * Permettra de récupérer le contact éditer par l'utilisateur,
         * si le contact ne possède pas d'identifiant alors il faut en créer un nouveau, si il en possède un alors il faudra modifier le contact.\n
         * Le booléen permet de savoir si il y a une erreur dans l'image et le renseigner sur la fenêtre principale.
         */
        void emitClose(Contact *, bool);

};

#endif // EDITCONTACTDIALOG_H
