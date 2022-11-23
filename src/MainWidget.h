#ifndef MAINWIDGET_H
#define MAINWIDGET_H

/**
 * @file MainWidget.h
 * @brief Fichier header de la classe MainWidget
 */

#include <QWidget>

#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QLabel>
#include <QObject>
#include <QDate>

#include "DatabaseCRUD.h"
#include "ListContact.h"
#include "CalendarDialog.h"
#include "MessageLabel.h"
#include "EditContactDialog.h"
#include "DetailsContactDialog.h"

/**
 * @class MainWidget
 * @brief classe représentant l'interface de la page principale
 * @details La classe hérite de la classe QWidget.
 */
class MainWidget : public QWidget
{
    Q_OBJECT

    private:
        ListContact listContact;/**< liste de contact affichée dans la tableau */

        DatabaseCRUD * contactCRUD;/**< gestionnaire de la table Contact de la BDD */
        //InteractionCRUD * interactionCRUD;
        //TodoCRUD * TodoCRUD;
        //ModificationCRUD * ModificationCRUD;

        QComboBox * filtersCombobox;/**< selecteur du filtre */
        QPushButton * searchButton;/**< bouton de recherche */
        QLineEdit * searchLineEdit;/**< barre de recherche */
        QPushButton * dateSelectorButton1;/**< bouton pour sélectionner la date de départ du filtre */
        QPushButton * dateSelectorButton2;/**< bouton pour sélectionner la date de fin du filtre */
        MessageLabel * messageLabel;/**< label pour afficher les messages*/
        QPushButton * resetFiltersButton;/**< bouton pour rénitialiser tous les filtres (barre de recherche, dates, ...) */
        QTableWidget * contactsTable;/**< tableau affichant les contacts */
        QComboBox * sortCombobox;/**< selecteur du tri */
        QPushButton * addContactButton; /**< bouton d'ajout d'un contact */
        QPushButton * detailsContactButton;/**< bouton pour afficher les details d'un contact */
        QPushButton * deleteContactButton;/**< bouton de suppression du contact selectionne */

        CalendarDialog * calendarDialogFirstDate;/**< boite de dialogue pour sélectionner la première date de filtre */
        CalendarDialog * calendarDialogSecondDate;/**< boite de dialogue pour sélectionner la seconde date de filtre */
        Date * filterFirstDate;/**< première date de filtre */
        Date * filterSecondDate;/**< seconde date de filtre */

        EditContactDialog * createContactDialog;/**< boite de dialogue pour créer un contact */
        DetailsContactDialog * detailsContactDialog;/**< boite de dialogue pour afficher les détails du contact sélectionné */


        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, items des selecteurs, nom, et autres propriétés).
         */
        void initUI();
        /**
         * @brief Permet d'initialiser les connect.
         */
        void initConnect();
        /**
         * @brief Permet d'afficher les contacts de l'attribut 'listContact' dans le tableau.
         */
        void fillTable();
        /**
         * @brief Permet de desactiver les boutons 'Afficher details' et 'Supprimer contact'.
         */
        void disableDeleteDetailsButton();


    public:
        /**
         * @brief Constructeur.
         * @param pointeur vers un objet de type ContactCRUD
         * @param pointeur vers un objet de type InteractionCRUD
         * @param pointeur vers un objet de type TodoCRUD
         * @param pointeur vers un objet de type ModificationCRUD
         * @details
         * Rempli l'attribut 'listContact' grâce au pointeur vers l'objet de type ContactCRUD, \n
         * puis appel les méthodes 'initUI' 'initConnect' et 'fillTable'.
         */
        MainWidget(DatabaseCRUD *,QWidget *parent = 0);
        ~MainWidget();


    public slots:
        /**
         * @brief slot ouvrant une fenêtre de dialogue pour demander la première date des filtres de recherche.
         */
        void openFirstCalendarDialog();
        /**
         * @brief slot ouvrant une fenêtre de dialogue pour demander la seconde date des filtres de recherche.
         */
        void openSecondCalendarDialog();
        /**
         * @brief slot pour recevoir la date choisi en tant que premiere date des filtres, et fermeture de la fenêtre de dialogue correspondante.
         * @param pointeur sur un objet QDate
         */
        void closeFirstCalendarDialog(QDate *);
        /**
         * @brief slot pour recevoir la date choisi en tant que seconde date des filtres, et fermeture de la fenêtre de dialogue correspondante.
         * @param pointeur sur un objet QDate
         */
        void closeSecondCalendarDialog(QDate *);
        /**
         * @brief slot appelant la méthode 'fillTable()' sur l'objet courant.
         */
        void updateTable();
        /**
         * @brief slot débloquant les boutons 'Afficher details' et 'Supprimer contact'.
         */
        void enableDeleteDetailsButton();
        /**
         * @brief slot appelant une méthode de 'ContactCRUD' pour supprimer le contact sélectionné.
         */
        void deleteContact();
        /**
         * @brief slot réinitialisant les filtres sélectionnés et rechargeant la liste de contact.
         */
        void resetFilters();
        /**
         * @brief slot appelant une méthode de 'ContactCRUD' pour récupérer les contacts en prenant en compte les filtres.
         */
        void searchContacts();
        /**
         * @brief slot ouvrant une fenêtre de dialogue pour créer un contact.
         */
        void openCreateContactDialog();
        /**
         * @brief slot ouvrant une fenêtre de dialogue pour afficher les détails du contact sélectionné.
         */
        void openDetailsContactDialog();
        /**
         * @brief slot appelant une méthode de 'ContactCRUD' pour ajouter ou modifier un contact.
         * @param pointeur vers sur un objet Contact
         * @param booleen permettant de savoir si il y a eu une erreur sur le lien d'image
         */
        void editContact(Contact *, bool);
};

#endif // MAINWIDGET_H
