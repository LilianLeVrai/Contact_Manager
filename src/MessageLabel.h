#ifndef MESSAGELABEL_H
#define MESSAGELABEL_H

/**
 * @file MessageLabel.h
 * @brief Fichier header de la classe MessageLabel
 */

#include <QLabel>


/**
 * @class MessageLabel
 * @brief classe représentant un message d'information pour l'utilisateur (erreur, réussite de demande, etc...)
 * @details La classe hérite de la classe QLabel.
 */
class MessageLabel : public QLabel
{

    public:
        /**
         * @brief Style enum
         * @details Permet de définir le style du message en fonction de son renseignement (rouge=erreur, vert=réussite), etc..)
         */
        enum Style{Green = 0, Red};

        /**
         * @brief Constructeur sans paramètre qui initialise le message sans texte, avec le style vert (réussite) et invisible.
         */
        MessageLabel();
        /**
         * @brief Constructeur qui permet de définir toutes les caractéristiques du message
         * @param QString représentant le texte
         * @param un choix de l'enum 'Style': Green - Red
         * @param booleen représentant la visibilité
         */
        MessageLabel(QString, Style, bool);

        /**
         * @brief méthode qui permet de définir toutes les caractéristiques du message
         * @param QString représentant le texte
         * @param un choix de l'enum 'Style': Green - Red
         * @param booleen représentant la visibilité
         */
        void setProperty(QString, Style, bool);
};

#endif // MESSAGELABEL_H
