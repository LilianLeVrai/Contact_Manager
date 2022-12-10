#ifndef MODIFICATIONSWINDOW_H
#define MODIFICATIONSWINDOW_H

/**
 * @file ModificationsWindow.h
 * @brief Fichier header de la classe ModificationsWindow
 */

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDialog>
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QPushButton>
#include <Contact.h>
#include <DatabaseCRUD.h>

/**
 * @class ModificationWindow
 * @brief classe représentant l'affichage des modifications
 * @details La classe hérite de la classe QWidget.
 */
class ModificationsWindow : public QDialog
{
    Q_OBJECT

    private:
        DatabaseCRUD * databaseCRUD;/**< gestionnaire de la BDD */
        QTableWidget * modificationsTable;/**< tableau affichant les modifications */
        Contact * contact; /**< contact */
        QPushButton * refreshButton;/**< bouton 'non' */

    public:
        /**
         * @brief Constructeur.
         */
        ModificationsWindow(DatabaseCRUD *, QWidget *parent = 0);
        /**
         * @brief Constructeur avec un contact en parametre.
         */
        ModificationsWindow(Contact *, DatabaseCRUD *, QWidget *parent = 0);

        ~ModificationsWindow();

        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, et autres propriétés).
         */
        void initUI();

        /**
         * @brief Permet de remplir le tableau avec les modifications contenues dans la base de données.
         */
        void fillModificationsTable();

        /**
         * @brief Permet de remplir le tableau avec les modifications contenues dans la base de données du contact.
         */
        void fillModificationsTableByContact();

    public slots:
        /**
         * @brief slot emmetant le signal 'refreshTable'.
         * @details
         * Ce signal est envoyé quand le bouton 'rafraichir' est clické.
         */
        void refreshTable();

        /**
         * @brief slot emmetant le signal 'refreshTableByContact'.
         * @details
         * Ce signal est envoyé quand le bouton 'rafraichir' est clické.
         */
        void refreshTableByContact();

};

#endif // MODIFICATIONSWINDOW_H
