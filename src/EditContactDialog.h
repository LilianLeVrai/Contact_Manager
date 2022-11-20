#ifndef EDITCONTACTDIALOG_H
#define EDITCONTACTDIALOG_H

#include <QObject>

/**
 * @file EditContactDialog.h
 * @brief Fichier header de la classe EditContactDialog
 */


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


        bool checkData();

    public slots:
        void openFileDialog();
        void editContact();
        void checkPathPicture();


    signals:
        void emitClose(Contact *, bool);

};

#endif // EDITCONTACTDIALOG_H
