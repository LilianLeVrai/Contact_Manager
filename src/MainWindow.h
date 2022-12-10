#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file MainWindow.h
 * @brief Fichier header de la classe MainWindow
 */


#include <QMainWindow>
#include <QAction>
#include "MainWidget.h"
#include "DatabaseCRUD.h"
#include "DatabaseManagement.h"
#include "YesNoDialog.h"
#include "ModificationsWindow.h"

/**
 * @class MainWindow
 * @brief classe représentant la page principale
 * @details La classe hérite de la classe QMainWindow.
 */
class MainWindow : public QMainWindow
{
        Q_OBJECT

    private:
        DatabaseManagement * databaseManagement;/**< databaseManagement (utile pour les options de la barre d'outils) */
        DatabaseCRUD * databaseCRUD;/**< gestionnaire de la BDD */

        QAction * optionExportJson;/**< bouton de la toolbar permettant l'export des données en JSON */
        QAction * optionInitDataTest;/**< bouton de la toolbar permettant l'import dans la BDD de données tests */
        QAction * showAllModification;/**< bouton de la toolbar permettant d'afficher la liste des modifications */

        MainWidget * mainWidget;/**< widget principal de la page */

        YesNoDialog * yesNoDialogDataTest;/** boite de dialogue pour confirmer la volonté d'importer les données test */
        ModificationsWindow * modificationsWindow;/** Fenêtre des modifications */

    public:
        /**
         * @brief Constructeur.
         * @param pointeur vers un objet de type ContactCRUD
         * @param pointeur vers un objet de type InteractionCRUD
         * @param pointeur vers un objet de type TodoCRUD
         * @param pointeur vers un objet de type ModificationCRUD
         * @details
         * Rempli l'attribut 'mainWidget' avec un nouveau MainWidget auquel est transmis les objets de 'CRUD', \n
         * puis initialise la toolbar.
         */
        MainWindow(DatabaseCRUD *, QWidget *parent = 0);
        ~MainWindow();

    public slots:
        /**
         * @brief slot ouvrant une fenêtre de dialogue pour demander la confirmation d'importer les données tests.
         */
        void askInitDataTest();
        /**
         * @brief slot récupérant le choix de l'utilisateur concernant l'import des données test
         * @details Si le choix est oui, les données sont importés et emet un signal au main widget pour mettre à jour le tableau.
         */
        void closeYesNoDialogDataTest(bool);
        /**
         * @brief slot créant un fichier .JSON de la base de données.
         */
        void createJSON();
        /**
         * @brief slot ouvrant une fenêtre affichant les modifications.
         */
        void openModificationsWindow();

    signals:
        /**
         * @brief signal.
         * @details Permet d'informer le main widget que l'on veut mettre à jour le tableau.
         */
        void emitUpdateContact();

};

#endif // MAINWINDOW_H
