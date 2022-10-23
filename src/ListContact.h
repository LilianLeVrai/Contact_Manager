#ifndef LISTCONTACT_H
#define LISTCONTACT_H

#include <string.h>
#include <Contact.h>

class ListContact
{
    private:
        std::list<Contact*> listContact;

    public:
        ListContact();
        ~ListContact();

        std::list<Contact*> getListContact() const;
        void setListContact(const std::list<Contact*> &);

        void addContact(Contact* const);
        void removeContactById(const int);
        Contact* getContactById(const int) const;
        int getSize() const;

        std::string toString() const;
};

#endif // LISTCONTACT_H
