#ifndef CONTACT_H
#define CONTACT_H

/**
 * @file Contact.h
 * @brief Fichier header de la classe Contact
 */


#include <string>
#include "Date.h"
#include "ListInteraction.h"

/**
 * @class Contact
 * @brief classe représentant un contact
 */
class Contact
{
    private:
        int id; /**< identifiant */
        std::string lastName; /**< nom */
        std::string firstName; /**< prénom */
        std::string company; /**< entreprise */
        std::string mail; /**< mail */
        std::string phone; /**< numéro de téléphone */
        std::string pathPicture; /**< chemin vers la photo */
        Date* dateCreation; /**< date de création au format jj/mm/aaaa */
        ListInteraction* listInteraction; /**< liste d'intéraction */

    public:
        /**
         * @brief Constructeur sans paramètre.
         * @details
         * Initialise l'attribut 'id' à NULL \n
         * Initialise l'attribut 'dateCreation' avec le constructeur par défaut de l'objet Date \n
         * Initialise l'attribut 'listInteraction' à nullptr
         */
        Contact();
        /**
         * @brief Constructeur avec valeurs string en paramètres.
         * @details
         * Initialise l'attribut 'id' à NULL \n
         * Initialise l'attribut 'dateCreation' avec le constructeur par défaut de l'objet Date \n
         * Initialise l'attribut 'listInteraction' à nullptr
         */
        Contact(const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
               const std::string & phone, const std::string & pathPicture);
        /**
         * @brief Constructeur avec valeurs string et la liste d'interaction en paramètres.
         * @details
         * Initialise l'attribut 'id' à NULL \n
         * Initialise l'attribut 'dateCreation' avec le constructeur par défaut de l'objet Date \n
         */
        Contact(const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
               const std::string & phone, const std::string & pathPicture, ListInteraction* const listInteraction);
        /**
         * @brief Constructeur avec tous les attributs excepté la date en paramètres.
         * @details
         * Initialise l'attribut 'dateCreation' avec le constructeur par défaut de l'objet Date \n
         */
        Contact(const int & id, const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
               const std::string & phone, const std::string & pathPicture, ListInteraction* const listInteraction);
        /**
         * @brief Constructeur avec tous les attributs excepté la liste d'interactions en paramètres.
         * @details
         * Initialise l'attribut 'listInteraction' à nullptr
         */
        Contact(const int & id, const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
               const std::string & phone, const std::string & pathPicture, Date* const dateCreation);
        ~Contact();

        /**
         * @brief Permet d'obtenir le nombre représentant l'identifiant dans l'objet.
         * @return Entier
         */
        int getId()const;
        /**
         * @brief Permet d'obtenir le texte représentant le nom dans l'objet.
         * @return std::string
         */
        std::string getLastName() const;
        /**
         * @brief Permet d'obtenir le texte représentant le prénom dans l'objet.
         * @return std::string
         */
        std::string getFirstName() const;
        /**
         * @brief Permet d'obtenir le texte représentant l'entreprise dans l'objet.
         * @return std::string
         */
        std::string getCompany() const;
        /**
         * @brief Permet d'obtenir le texte représentant le mail dans l'objet.
         * @return std::string
         */
        std::string getMail() const;
        /**
         * @brief Permet d'obtenir le texte représentant le numéro de téléphone dans l'objet.
         * @return std::string
         */
        std::string getPhone() const;
        /**
         * @brief Permet d'obtenir le texte représentant le chemin vers la photo dans l'objet.
         * @return std::string
         */
        std::string getPathPicture() const;
        /**
         * @brief Permet d'obtenir la date de création de l'objet.
         * @return pointeur vers objet Date
         */
        Date* getDateCreation() const;
        /**
         * @brief Permet d'obtenir la liste d'interactions de l'objet.
         * @return pointeur vers objet ListInteraction
         */
        ListInteraction* getListInteraction() const;

        /**
         * @brief Permet de définir la valeur de l'attribut représentant l'identifiant.
         * @param Le paramètre doit être un entier
         */
        void setId(const int &);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant le nom.
         * @param Le paramètre doit être un string
         */
        void setLastName(const std::string &);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant le prénom.
         * @param Le paramètre doit être un string
         */
        void setFirstName(const std::string &);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant l'entreprise.
         * @param Le paramètre doit être un string
         */
        void setCompany(const std::string &);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant le mail.
         * @param Le paramètre doit être un string
         */
        void setMail(const std::string &);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant le numéro de téléphone.
         * @param Le paramètre doit être un string
         */
        void setPhone(const std::string &);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant le chemin vers la photo.
         * @param Le paramètre doit être un string
         */
        void setPathPicture(const std::string &);
        /**
         * @brief Permet de définir la valeur de l'attribut représentant la date de création.
         * @param Le paramètre doit être un pointeur vers un objet Date
         */
        void setDateCreation(Date* const);
        /**
         * @brief Permet de définir l'attribut de la liste d'interaction.
         * @param Le paramètre doit être un pointeur vers un objet ListInteraction
         */
        void setListInteraction(ListInteraction* const);

        /**
         * @brief Permet d'obtenir une chaine de caractères avec les informations de l'objet
         * @return std::string sous la forme 'nom|prenom|entreprise|mail|telephone|urlPhoto|dateCreation\\nlistInteraction.toString()'
         *
         * @warning sujet à changement
         */
        std::string toString() const;

};

#endif // CONTACT_H
