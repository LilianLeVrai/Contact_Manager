#ifndef DATE_H
#define DATE_H

/**
 * @file Date.h
 * @brief Fichier header de la classe Date
 */


#include <iostream>
#include <time.h>
#include <string>

/**
 * @class Date
 * @brief classe représentant une date
 */
class Date
{

    public:
        enum DateType{WithoutHours = 0, WithHours};
        void setDateType(DateType dateTypeEnum){dateType=dateTypeEnum;}

    private:
        unsigned int minute; /**< minute */
        unsigned int hour; /**< heure */
        unsigned int day; /**< jour */
        unsigned int month; /**< mois */
        unsigned int year; /**< année */

        DateType dateType;


    public:
        /**
         * @brief Constructeur sans paramètre qui initialise les attributs avec la date et l'horaire actuelles lors de la création de l'objet.
         */
        Date();
        /**
         * @brief Constructeur avec la date en paramètre, mais pas l'horaire qui sera initialisé avec celle actuelle lors de la création de l'objet.
         * @details Notamment utile pour faire les dates des tag de date qui doivent être au format jj/mm/aaaa.
         */
        Date(unsigned int day, unsigned int month, unsigned int year);
        /**
         * @brief Constructeur avec tout les attributs en paramètres.
         * @details Notamment utile lorsque l'on aura besoin de définir des dates avec l'heure, comme pour horodater les modifications.
         */
        Date(unsigned int minute, unsigned int hour, unsigned int day, unsigned int month, unsigned int year);
        /**
         * @brief Constructeur avec une chaine de caractères sous la forme jj/mm/aaaa ou jj/mm/aaaa hh:mm.
         * @details Notamment utile lorsque que l'on créer une date en récupérant la chaine de caractère depuis la BDD.
         */
        Date(const std::string);
        ~Date();

        /**
         * @brief Permet d'obtenir le nombre représentant les minutes dans l'objet.
         * @return Entier
         */
        unsigned int getMinute() const;
        /**
         * @brief Permet d'obtenir le nombre représentant les heures dans l'objet.
         * @return Entier
         */
        unsigned int getHour() const;
        /**
         * @brief Permet d'obtenir le nombre représentant les jours dans l'objet.
         * @return Entier
         */
        unsigned int getDay() const;
        /**
         * @brief Permet d'obtenir le nombre représentant les mois dans l'objet.
         * @return Entier
         */
        unsigned int getMonth() const;
        /**
         * @brief Permet d'obtenir le nombre représentant les années dans l'objet.
         * @return Entier
         */
        unsigned int getYear() const;
        /**
         * @brief Permet de définir la valeur de l'attribut représentant les minutes.
         * @param Le paramètre doit être un entier
         */
        void setMinute(const unsigned int);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant les heures.
         * @param Le paramètre doit être un entier
         */
        void setHour(const unsigned int);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant les jours.
         * @param Le paramètre doit être un entier
         */
        void setDay(const unsigned int);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant les mois.
         * @param Le paramètre doit être un entier
         */
        void setMonth(const unsigned int);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant les années.
         * @param Le paramètre doit être un entier
         */
        void setYear(const unsigned int);

        /**
         * @brief Permet d'obtenir une chaine de caractères avec les informations de l'objet
         * @return std::string sous la forme 'jj/mm/aaaa'
         *
         * @warning sujet à changement
         */
        std::string toString() const;


        bool isLessThan(Date *);

};

#endif // DATE_H
