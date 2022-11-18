#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file MainWindow.h
 * @brief Fichier header de la classe MainWindow
 */


#include <QMainWindow>
#include <QAction>
#include "MainWidget.h"
#include "ContactCRUD.h"
#include "DatabaseManagement.h"

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

        QAction * optionExportJson;/**< bouton de la toolbar permettant l'export des données en JSON */
        QAction * optionInitDataTest;/**< bouton de la toolbar permettant l'import dans la BDD de données tests */

        MainWidget * mainWidget;/**< widget principal de la page */


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
        MainWindow(DatabaseManagement *, ContactCRUD *, QWidget *parent = 0);
        ~MainWindow();




};

#endif // MAINWINDOW_H
