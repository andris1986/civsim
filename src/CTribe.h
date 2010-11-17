#ifndef CTRIBE_H
#define CTRIBE_H

/** @brief Tribe - group of similar creatures. */

class CTribe {
    /** @brief Constructor.
        @todo Implement.
        
        Create new tribe.        
    */
    CTribe();
    
    /** @brief Add creature to the tribe.
        @param c Creature to add.
        @todo Implement.
        
        If creature is already in the tribe, function does nothing.
    */
    void addCreature(CCreature * c);
    
    /** @brief Remove creature from the tribe.
        @param c Creature to remove.
        @todo Implement.
        
        If creature is not in the tribe, function does nothing.
    */
    void removeCreature(CCreature * c);
}

#endif //CTRIBE_H
