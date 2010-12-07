#ifndef CRESOURCE_H
#define CRESOURCE_H

#include <list>

#include "CDrawable.h"

class CCreature;

/** @brief Any resource that can bee needed by the creatures. */

class CResource : public CDrawable {
public:
	/** @brief type of the resource */
	typedef enum {
		RES_TYPE_FOOD,  ///< Food
		RES_TYPE_WATER, ///< Water
		RES_TYPE_COUNT  ///< Number of the resource types. This should always be the last
	}ResourceType;
    /** @brief Constructor. Create new resource at the given center.
		@param type Type fo the resource.
        @param center Center of the resource.
        @param amount Amount of the resources available
        @todo Implement.
    */
    CResource(ResourceType type, const CPoint & center, float amount);

	~CResource();

    /** @brief Get amount of resources available in the given object.
        @return Amount of the resources.
        @todo Implement.
    */
    float amount() const;

    /** @brief Take amount of resources.    
        @return amount of the resources that was taken. 
        This will also remove this amount from the resource.
        @todo Implement.
        
        If resource has less amount than requested it will return only as 
        much resources as it has.
        */
    float take(float amount);

    /** @brief Painting function of the resource. */
    virtual void paint();

	/** @brief Get type of the resource 
		@return Type of the resource
	*/
	ResourceType type();

	void follow(CCreature * c);
	void unfollow(CCreature * c);

private:
    /** @brief Default radius of the resource */
    static const float DEFAULT_RESOURCE_RADIUS = 0.02;
    
    /** @brief Amount of the resources available */
    float m_amount;

	/** @brief type of the resource */
	ResourceType m_type;

	std::list<CCreature *> m_followers;
};

#endif //CRESOURCE_H
