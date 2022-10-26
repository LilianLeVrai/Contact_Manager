#ifndef CONTACT_H
#define CONTACT_H

/**
 * @file Contact.h
 * @brief Fichier header de la classe Contact
 */


#include <string>
#include <Date.h>
#include <ListInteraction.h>

class Contact
{
    private:
        int id;
        std::string lastName;
        std::string firstName;
        std::string company;
        std::string mail;
        std::string phone;
        std::string pathPicture;
        Date* dateCreation;
        ListInteraction* listInteraction;

    public:
        Contact();
        Contact(const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
                const std::string & phone, const std::string & pathPicture);
        Contact(const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
                const std::string & phone, const std::string & pathPicture, ListInteraction* const listInteraction);
        Contact(const int & id, const std::string & lastName, const std::string & firstName, const std::string & company, const std::string & mail,
                const std::string & phone, const std::string & pathPicture, ListInteraction* const listInteraction);
        ~Contact();

        int getId()const;
        std::string getLastName() const;
        std::string getFirstName() const;
        std::string getCompany() const;
        std::string getMail() const;
        std::string getPhone() const;
        std::string getPathPicture() const;
        Date* getDateCreation() const;
        ListInteraction* getListInteraction() const;

        void setId(const int &);
        void setLastName(const std::string &);
        void setFirstName(const std::string &);
        void setCompany(const std::string &);
        void setMail(const std::string &);
        void setPhone(const std::string &);
        void setPathPicture(const std::string &);
        void setDateCreation(Date* const);
        void setListInteraction(ListInteraction* const);

        std::string toString() const;

};

#endif // CONTACT_H
