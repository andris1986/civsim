#ifndef CCREATURE_H
#define CCREATURE_H

#include <list>
#include <vector>

#include "CDrawable.h"
#include "CPoint.h"
#include "CResource.h"

class CTribe;

/** @brief Basic living creature. */

class CCreature : public CDrawable {
public:
	/** @brief Possible genders of the creature */
	typedef enum {
		GENDER_MALE, ///< Male
		GENDER_FEMALE, ///< Female
	} Gender;

	/** @brief Structure describe need of creature for certain resources */
	typedef struct {
		float curAmount; 					///< Current amount in the creature
		float minAmount; 					///< Minimum amount, if @ref curAmount < @ref minAmount, creature will die
		float maxAmount; 					///< Maximum amount that creature can have
		float needLimit; 					///< Creature will start looking for resources if @ref curAmount < @ref needLimit
		CResource::ResourceType resType;    ///< Type of the resource
		float needPerTime;					///< Amount of the reousrces that creature consumes every time unit
	} ResourceNeed;

	/** @brief Minimum health */
	static const float MIN_HEALTH = 0.0;

	/** @brief Maximum health */
	static const float MAX_HEALTH = 1.0;

	/** @brief Default radius of the creature */
	static const float DEFAULT_RADIUS = 0.05;

    /** @brief Constructor.
		@param gender Gender of the creature
		@param center Initial location
        @param tribe Tribe the creature belongs to.
        @param parent Parent of the creature.
        @todo Need to make sure paren't pointer can't be changed or deleted.
    */
    CCreature(Gender gender, const CPoint & center, CTribe * tribe, CCreature * parent);
    
    /** @brief Destructor.
        
        Destroy the creature and removes it from all lists where it is present.
    */
    virtual ~CCreature();

    /** @brief Attack other creature.
        @param other Creature to attack.
    */
    void attack(CCreature & other);
    
    /** @brief Try to breed with other creature.
        @param other Creature to breed with.
    */
    void breed(CCreature & other);

    /** @brief Painting function. Can be iplemented for custom look 
    */
    virtual void paint();

    /** @brief Live the life
        @param time Time to live.
    */        
    virtual void live(int time);
    
    /** @brief Move.
        @todo Find out how to use doxygen to tell it's reimplemented.
    */
    virtual void move(float direction, float distance);

	/** @brief Get vision of the creature
		@return Vision in tiles
	*/
	int vision() const;

	void setFollowedResource(CResource * res);
private:
	/** @brief Age of the creature */
	int m_age;
	
	/** @brief Health of the creature from @ref MIN_HEALTH to @ref MAX_HEALTH */
	float m_health;

	/** @brief Gender of the creature */
	Gender m_gender;

	/** @brief Indicates if creature is alive */
	bool m_alive;

	/** @brief Trieb where the creature belong, can be NULL */
	CTribe * m_tribe;

	/** @brief Parent of the creature */
	CCreature * m_parent;

	/** @brief Children of the creature */
	std::list<CCreature*> m_children;

	/** @brief Needs of the creature sorted by priority. Sorting is done internally */
	std::vector<ResourceNeed> m_needs;

	/** @brief Vision - how far a creature can see.

		This is a value from 0 (blind) to @ref CWorld::TILE_COUNT.
	*/
	int m_vision;

	CResource * m_followedResource;

    float m_stepSize;

    float m_randomDirection;

	/** @brief Get pregnant 
		@return true on success, false on failure
	*/
	bool getPregnant();

	/** @brief Die.

			   Creature should be deleted on next event loop 
	*/
	void die();

	/** @brief Add new child 
		@param c New child
	*/
	void addChild(CCreature & c);

	/** @brief Remove child 
		@param c Child to remove
	*/
	void removeChild(CCreature & c);

	/** @brief Check if all parameters needed to live are fine, die if something is wrong */
	void checkDeath();

	static inline bool compareNeeds(const ResourceNeed & n1, const ResourceNeed & n2);

};

#endif //CCREATURE_H
