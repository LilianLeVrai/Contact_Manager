#ifndef EDITCONTACTDIALOG_H
#define EDITCONTACTDIALOG_H

/**
 * @file EditContactDialog.h
 * @brief Fichier header de la classe EditContactDialog
 */


#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include "Contact.h"
#include "MessageLabel.h"

/**
 * @class EditContactDialog
 * @brief classe représentant l'interface de la boîte de dialogue pour éditer un contact (création et modification)
 * @details La classe hérite de la classe QDialog.
 */
class EditContactDialog : public QDialog
{

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

        EditContactDialog(QWidget *parent = 0);
        EditContactDialog(Contact *, QWidget *parent = 0);

        void initUI();
        void initConnect();
};

#endif // EDITCONTACTDIALOG_H
