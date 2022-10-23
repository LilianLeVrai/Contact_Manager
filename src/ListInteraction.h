#ifndef LISTINTERACTION_H
#define LISTINTERACTION_H

#include <Interaction.h>

class ListInteraction
{
    private:
        std::list<Interaction*> listInteraction;

    public:
        ListInteraction();
        ~ListInteraction();

        std::list<Interaction*> getListInteraction() const;
        void setListInteraction(const std::list<Interaction*> &);

        void addInteraction(Interaction* const);
        void removeInteractionById(const int);
        Interaction* getInteractionById(const int) const;
        int getSize() const;

        std::string toString() const;
};

#endif // LISTINTERACTION_H
