#ifndef CTRIBE_H
#define CTRIBE_H

#include <list>

#include "CCreature.h"

/** @brief Tribe - group of similar creatures. */

class CTribe {
public:
    /** @brief Constructor.
        
        Create new tribe.        
    */
    CTribe();
    
    /** @brief Add creature to the tribe.
        @param c Creature to add.
        
        If creature is already in the tribe, function does nothing.
    */
    void addCreature(CCreature & c);
    
    /** @brief Remove creature from the tribe.
        @param c Creature to remove.
        
        If creature is not in the tribe, function does nothing.
    */
    void removeCreature(CCreature & c);

private:
	/** @brief Creatures of the tribe */
	std::list<CCreature*> m_creatures;
};

#endif //CTRIBE_H
