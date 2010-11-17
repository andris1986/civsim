#ifndef CCREATURE_H
#define CCREATURE_H

/** @brief Basic living creature. */

class CCreature : public CDrawable {
public:
    /** @brief Constructor.
        @param tribe Tribe the creature belongs to.
        @param parent Parent of the creature.
        @todo Need to make sure paren't pointer can't be changed or deleted.
        @todo Implement.
    */
    CCreature(CTribe & tribe, const CCreature * parent);
    
    /** @brief Destructor.
        @todo Implement.
        
        Destroy the creature and removes it from all lists where it is present.
    */
    virtual ~CCreature();

    /** @brief Attack other creature.
        @param other Creature to attack.
        @todo Implement.
    */
    void attack(CCreature & other);
    
    /** @bried Try to breed with other creature.
        @param other Creature to breed with.
        @todo Implement.
    */
    void breed(CCreature & other);

    /** @brief Painting function. Can be iplemented for custom look 
        @todo Implement.
    */
    virtual void paint();

    /** @brief Live the life
        @param time Time to live.
        @todo Implement.
    */        
    virtual void live(int time);
    
    /** @brif Move.
        @todo Implement.
        @todo Find out how to use doxygen to tell it's reimplemented.
    */
    virtual void move(float direction, float distance);
}

#endif //CCREATURE_H
