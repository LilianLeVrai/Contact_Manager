#ifndef LISTINTERACTION_H
#define LISTINTERACTION_H

/**
 * @file ListInteraction.h
 * @brief Fichier header de la classe ListInteraction
 */


#include "Interaction.h"

/**
 * @class ListInteraction
 * @brief classe représentant une liste de pointeurs vers des objets 'Interaction'
 */
class ListInteraction
{
    private:
        std::list<Interaction*> listInteraction; /**< liste de pointeurs sur des objets 'Interaction' */

    public:
        ListInteraction();
        ~ListInteraction();

        /**
         * @brief Permet de récupérer l'attribut de liste.
         * @return std::list<Interaction*>
         */
        std::list<Interaction*> getListInteraction() const;
        /**
         * @brief Permet de récupérer une interaction de la liste en fonction de son index dans celle-ci.
         * @param Le paramètre doit être un entier représentant l'index
         * @return pointeur vers objet Interaction
         */
        Interaction* getInteractionByIndex(const int) const;
        /**
         * @brief Permet de définir l'attribut de liste.
         * @param Le paramètre doit être un std::list<Interaction*>
         */
        void setListInteraction(const std::list<Interaction*> &);

        /**
         * @brief Permet d'ajouter une interaction à la liste.
         * @param Le paramètre doit être un pointeur sur un objet Interaction
         */
        void addInteraction(Interaction* const);
        /**
         * @brief Permet d'enlever une interaction de la liste en fonction de son identifiant.
         * @param Le paramètre doit être un entier représentant l'identifiant
         */
        void removeInteractionById(const int);
        /**
         * @brief Permet de vider toutes les interactions de la liste.
         */
        void removeAllInteractions();
        /**
         * @brief Permet de récupérer une interaction de la liste en fonction de son identifiant.
         * @param Le paramètre doit être un entier représentant l'identifiant
         * @return pointeur vers objet Interaction
         */
        Interaction* getInteractionById(const int) const;
        /**
         * @brief Permet de récupérer la taille de la liste.
         * @return entier
         */
        int getSize() const;

        /**
         * @brief Permet d'obtenir une chaine de caractères avec les informations de l'objet
         * @return std::string sous la forme 'interaction.toString\\n\\ninteraction.toString\\n\\ninteraction.toString'
         *
         * @warning sujet à changement
         */
        std::string toString() const;
};

#endif // LISTINTERACTION_H
