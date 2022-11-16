#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file MainWindow.h
 * @brief Fichier header de la classe MainWindow
 */


#include <QWidget>

#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QLabel>

#include "ContactCRUD.h"
#include "ListContact.h"

/**
 * @class MainWindow
 * @brief classe représentant l'interface de la page principale
 * @details La classe hérite de la classe QWidget.
 */
class MainWindow : public QWidget
{
    Q_OBJECT

private:
    ListContact listContact;/**< liste de contact affichée dans la tableau */

    ContactCRUD * contactCRUD;/**< gestionnaire de la table Contact de la BDD */
    //InteractionCRUD * interactionCRUD;
    //TodoCRUD * TodoCRUD;
    //ModificationCRUD * ModificationCRUD;

    QComboBox * filtersCombobox;/**< selecteur du filtre */
    QPushButton * searchButton;/**< bouton de recherche */
    QLineEdit * searchLineEdit;/**< barre de recherche */
    QPushButton * dateSelectorButton1;/**< bouton pour sélectionner la date de départ du filtre */
    QPushButton * dateSelectorButton2;/**< bouton pour sélectionner la date de fin du filtre */
    QTableWidget * contactsTable;/**< tableau affichant les contacts */
    QComboBox * sortCombobox;/**< selecteur du tri */

    /**
     * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, items des selecteurs, nom, et autres propriétés).
     */
    void initUI();
    /**
     * @brief Permet d'afficher les contacts de l'attribut 'listContact' dans le tableau.
     */
    void fillTable();

public:
    /**
     * @brief Constructeur.
     * @param pointeur vers un objet de type ContactCRUD
     * @param pointeur vers un objet de type InteractionCRUD
     * @param pointeur vers un objet de type TodoCRUD
     * @param pointeur vers un objet de type ModificationCRUD
     * @details
     * Rempli l'attribut 'listContact' grâce au pointeur vers l'objet de type ContactCRUD, \n
     * puis appel les méthodes 'initUI' et 'fillTable'.
     */
    MainWindow(ContactCRUD *,QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
