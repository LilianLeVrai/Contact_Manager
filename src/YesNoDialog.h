#ifndef YESNODIALOG_H
#define YESNODIALOG_H

/**
 * @file YesNoDialog.h
 * @brief Fichier header de la classe CalendarDialog
 */


#include <QDialog>
#include <QPushButton>
#include <QDate>
#include <QString>


/**
 * @class YesNoDialog
 * @brief classe représentant l'interface d'une boîte de dialogue à choix simple (oui ou non)
 * @details La classe hérite de la classe QDialog.
 */
class YesNoDialog : public QDialog
{
    Q_OBJECT

    private:
        QPushButton * noButton;/**< bouton 'non' */
        QPushButton * yesButton;/**< bouton'oui' */

        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, bouton, et autres propriétés).
         */
        void initUI(QString, QString);
        /**
         * @brief Permet d'initialiser les connect.
         */
        void initConnect();

    public:
        /**
         * @brief Constructeur.
         * @param QString qui définira le titre de la fenêtre
         * @param QString qui définira la question posée à l'utilisateur
         * @details
         * Défini la boîte de dialogue en mode bloquante, puis appel les méthodes 'initUI' et 'initConnect'.
         */
        YesNoDialog(QString, QString, QWidget *parent = 0);
        ~YesNoDialog();

    public slots:
        /**
         * @brief slot emmetant le signal 'emitClose', avec en paramêtre la booleen false.
         * @details
         * Ce signal est envoyé quand le bouton 'non' est clické.
         */
        void noCloseDialog();
        /**
         * @brief slot emmetant le signal 'emitClose', avec en paramêtre le booleen true.
         * @details
         * Ce signal est envoyé quand le bouton 'oui' est clické.
         */
        void yesCloseDialog();


    signals:
        /**
         * @brief signal.
         * @param booleen
         * @details Permettra de récupérer le choix fait par l'utilisateur, choix représenté par le booleen en paramêtre.
         */
        void emitClose(bool);
};

#endif // YESNODIALOG_H
